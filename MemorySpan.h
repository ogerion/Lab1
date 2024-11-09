#pragma once

#include "MsPtr.h"

template<class T>
class MemorySpan
{
private:
    MsPtr<T>* base;
    size_t size;
public:
    MemorySpan();

    MemorySpan(T*);

    size_t getLenght() const
    {
        return size;
    }

    void append(T*);

    void prepend(T*);

    void insertAt(T*, size_t);

    UnqPtr<T>&& getFirst();

    UnqPtr<T>&& getLast();

    UnqPtr<T>&& getByIndex(size_t);

    WeakPtr<T>&& copyFirst();

    WeakPtr<T>&& copyLast();

    WeakPtr<T>&& copyByIndex(size_t);

    void concat(MemorySpan<T>&);

    void concat(MemorySpan<T>&&);

    void destroy();

    ~MemorySpan();
};

template <class T>
MemorySpan<T>::MemorySpan()
{
    base = nullptr;
    size = 0;
}

template <class T>
MemorySpan<T>::MemorySpan(T* ptr)
{
    base = new MsPtr<T>(ptr);
    base->setNext(base);
    base->setPrev(base);
    size = 1;
}

template<class T>
void MemorySpan<T>::append(T* ptr)
{
    MsPtr<T>* item = new MsPtr<T>(ptr);
    if (this->size == 0)
    {
        base = item;
        base->setNext(item);
        base->setPrev(item);
    }
    else if (this->size == 1)
    {
        base->setNext(item);
        base->setPrev(item);
        item->setNext(base);
        item->setPrev(base);
    }
    else if (this->size == 2)
    {
        base->setPrev(item);
        base->getNext()->setNext(item);
        item->setPrev(base->getNext());
        item->setNext(base);
    }
    else
    {
        base->getPrev()->setNext(item);
        item->setPrev(base->getPrev());
        item->setNext(base);
        base->setPrev(item);
    }
    size += 1;
}

template<class T>
void MemorySpan<T>::prepend(T* ptr)
{
    MsPtr<T>* item = new MsPtr<T>(ptr);
    if (this->size == 0)
    {
        base = item;
        base->setNext(item);
        base->setPrev(item);
    }
    else if (this->size == 1)
    {
        base->setNext(item);
        base->setPrev(item);
        item->setNext(base);
        item->setPrev(base);
        base = item;
    }
    else if (this->size == 2)
    {
        base->setPrev(item);
        base->getNext()->setNext(item);
        item->setPrev(base->getNext());
        item->setNext(base);
        base = item;
    }
    else
    {
        base->getPrev()->setNext(item);
        item->setPrev(base->getPrev());
        item->setNext(base);
        base->setPrev(item);
        base = item;
    }
    size += 1;
}

template <class T>
void MemorySpan<T>::insertAt(T* ptr, size_t pos)
{
    MsPtr<T>* actual = base;
    MsPtr<T>* item = new MsPtr<T>(ptr);
    if ((pos > 0 && pos % size == 0) || (pos == 0))
    {
        MsPtr<T>* item = new MsPtr<T>(ptr);
        item->setNext(base);
        item->setPrev(base->setPrev());
        base->getPrev()->setNext(item);
        base->setPrev(item);
        base = item;
    }
    else if ((pos < 0 && (-1 * pos) % size == 0))
    {
        MsPtr<T>* item = new MsPtr<T>(ptr);
        item->setNext(base);
        item->setPrev(base->setPrev());
        base->getPrev()->setNext(item);
        base->setPrev(item);
        base = item;
    }
    else if (pos >= 0)
    {
        for (int i = 0; i < pos; i++)
        {
            actual = actual->getNext();
        }
        actual->getNext()->setNext(item);
        item->setPrev(actual->getPrev());
        actual->setPrev(item);
        item->setNext(actual);
    }
    else
    {
        for (int i = 0; i > pos; i--)
        {
            actual = actual->getPrev();
        }
        actual->getPrev()->setNext(item);
        item->setPrev(actual->getPrev());
        actual->setPrev(item);
        item->setNext(actual);
    }
    size += 1;
}

template<class T>
UnqPtr<T>&& MemorySpan<T>::getFirst()
{
    size -= 1;
    base = base->getNext();
    MsPtr<T>* tempMsPtr = base->getPrev();
    UnqPtr<T>&& temp = tempMsPtr->get();
    if (size != 0)
    {
        delete tempMsPtr;
    }
    else
    {
        delete base;
        base = nullptr;
    }
    return std::move(temp);
}

template<class T>
UnqPtr<T>&& MemorySpan<T>::getLast()
{
    size -= 1;
    MsPtr<T>* tempMsPtr = base->getPrev();
    UnqPtr<T>&& temp = tempMsPtr->get();
    if (size != 0)
    {
        delete tempMsPtr;
    }
    else
    {
        delete base;
        base = nullptr;
    }
    return std::move(temp);
}

template<class T>
UnqPtr<T>&& MemorySpan<T>::getByIndex(size_t pos)
{
    size -= 1;
    if (this->size != 0)
    {
        return base->get(pos);
    }
    else
    {
        return base->get();
    }

}

template<class T>
WeakPtr<T>&& MemorySpan<T>::copyFirst()
{
    return base->copy();
}

template <class T>
WeakPtr<T>&& MemorySpan<T>::copyLast()
{
    return base->getPrev()->copy();
}

template <class T>
WeakPtr<T>&& MemorySpan<T>::copyByIndex(size_t pos)
{
    return base->copy(pos);
}

template <class T>
void MemorySpan<T>::concat(MemorySpan<T>& other)
{
    size_t s = other.getLenght();
    for (int i = 0; i < s; i++)
    {
        UnqPtr<T>&& temp = other.getFirst();
        this->append(temp.release());
        delete& temp;
    }
}

template <class T>
void MemorySpan<T>::concat(MemorySpan<T>&& other)
{
    size_t s = other.getLenght();
    for (int i = 0; i < s; i++)
    {
        UnqPtr<T>&& temp = other.getFirst();
        this->append(temp.release());
        delete& temp;
    }
}

template <class T>
void MemorySpan<T>::destroy()
{
    if (base!=nullptr && size!=0)
    {
        while (base->getPrev() != base)
        {
            delete base->getPrev();
        }
        delete base;
        size = 0;
    }
}

template <class T>
MemorySpan<T>::~MemorySpan()
{
    this->destroy();
}