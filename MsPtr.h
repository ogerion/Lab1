#pragma once
#include "UnqPtr.h"
#include "ShrdPtr.h"
#include "WeakPtr.h"
template<class T>
class MsPtr
{
private:
    ShrdPtr<T> ptr;
    MsPtr<T>* next;
    MsPtr<T>* prev;
public:
    MsPtr();

    MsPtr(T*);

    UnqPtr<T>&& get(int);

    UnqPtr<T>&& get();

    WeakPtr<T>&& copy(int);

    WeakPtr<T>&& copy();

    MsPtr<T>* locate(int);

    void setPrev(MsPtr<T>*);

    void setNext(MsPtr<T>*);

    MsPtr<T>* getNext();

    MsPtr<T>* getPrev();

    ~MsPtr();
};

template<class T>
MsPtr<T>::MsPtr()
{
    this->ptr = ShrdPtr<T>();
    this->next = nullptr;
    this->prev = nullptr;
}

template<class T>
MsPtr<T>::MsPtr(T* ptr)
{
    this->ptr = ShrdPtr<T>(ptr);
    this->next = this;
    this->prev = this;
}

template<class T>
UnqPtr<T>&& MsPtr<T>::get(int pos)
{
    MsPtr<T>* actual = this->locate(pos);
    return(actual->get());

}

template<class T>
UnqPtr<T> && MsPtr<T>::get()
{
    if (this->getNext() == this)
    {
    }
    else if (this->getNext()->getNext() == this)
    {
        this->getNext()->setNext(this->getNext());
        this->getNext()->setPrev(this->getNext());
    }
    else
    {
        MsPtr<T>* temp = this->getPrev();
        this->getPrev()->setNext(this->getNext());
        this->getNext()->setPrev(temp);
    }
    T* temp = new T(*(ptr));
    ptr.reset();
    UnqPtr<T>* res = new UnqPtr<T>(temp);
    return std::move(*res);
}

template<class T>
WeakPtr<T>&& MsPtr<T>::copy(int pos)
{
    MsPtr<T>* actual = this->locate(pos);
    return actual->copy();
}

template<class T>
WeakPtr<T>&& MsPtr<T>::copy()
{
    WeakPtr<T> * res = new WeakPtr<T>(this->ptr);
    return std::move(*res);
}

template<class T>
MsPtr<T>* MsPtr<T>::locate(int pos)
{
    MsPtr<T>* actual = this;
    if (pos >= 0)
    {
        for (int i = 0; i < pos; i++)
        {
            actual = actual->getNext();
        }
        return actual;
    }
    for (int i = 0; i > pos; i--)
    {
        actual = actual->getPrev();
    }
    return actual;
}

template<class T>
void MsPtr<T>::setNext(MsPtr<T>* next)
{
    this->next = next;
}

template<class T>
void MsPtr<T>::setPrev(MsPtr<T>* prev)
{
    this->prev = prev;
}

template<class T>
MsPtr<T>* MsPtr<T>::getNext()
{
    return this->next;
}

template<class T>
MsPtr<T>* MsPtr<T>::getPrev()
{
    return this->prev;
}

template<class T>
MsPtr<T>::~MsPtr()
{
    if (!ptr)
    {

    }
    else if (this->getNext() == this)
    {
    }
    else if (this->getNext()->getNext() == this)
    {
        this->getNext()->setNext(this->getNext());
        this->getNext()->setPrev(this->getNext());
    }
    else
    {
        this->getPrev()->setNext(this->getNext());
        this->getNext()->setPrev(this->getPrev());
    }
}