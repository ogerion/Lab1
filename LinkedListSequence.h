#pragma once
#include "Sequence.h"
#include "UnqPtr.h"
#include "ShrdPtr.h"
template<class T>
class Node
{
    private:
        T val;
        ShrdPtr<Node<T>> next;
        ShrdPtr<Node<T>> prev;
    public:
        Node(T & value)
        {
            val = value;
            next = ShrdPtr<Node<T>>();
            prev = ShrdPtr<Node<T>>();
        }
        
        Node(T& value, ShrdPtr<Node<T>> & n, ShrdPtr<Node<T>> & p)
        {
            val = value;
            next = n;
            prev = p;
        }
        
        T &getVal()
        {
            return val;
        }
        
        void setNext(ShrdPtr<Node<T>>& node)
        {
            next = node;
        }
        
        void setPrev(ShrdPtr<Node<T>>& node)
        {
            prev = node;
        }
        
        ShrdPtr<Node<T>>& getNext()
        {
            return next;
        }

        ShrdPtr<Node<T>>& getPrev()
        {
            return prev;
        }
};

template <class T>
class LinkedListSequence : public Sequence<T>
{
    protected:
        ShrdPtr<Node<T>> base;
    public:
        LinkedListSequence();

        LinkedListSequence<T> * Append(T &) override;
        LinkedListSequence<T> * Prepend(T &) override;
        LinkedListSequence<T> * InsertAt(T &, size_t) override;

        T & GetFirst() override;
        T & GetLast() override;
        T & Get(size_t index) override;

        LinkedListSequence<T> & GetSubSequence(size_t , size_t ) override;
  
        LinkedListSequence<T> & Concat(Sequence<T> & seq ) override;
};

template <class T>
LinkedListSequence<T>::LinkedListSequence()
{
    size = 0;
    base = ShrdPtr<Node<T>>();
}

template <class T>
LinkedListSequence<T> * LinkedListSequence<T>::Append(T & item)
{
    ShrdPtr<Node<T>> * newNode = new ShrdPtr<Node<T>>(new Node<T>(item));
    if (size == 0)
    {
        base = *newNode;
        base->setNext(base);
        base->setPrev(base);
    }
    else if (size == 1)
    {
        base->setNext(*newNode);
        base->setPrev(base->getNext());
        base->getNext()->setPrev(base);
        base->getNext()->setNext(base);
    }
    else
    {
        (*newNode)->setNext(base);
        (*newNode)->setPrev(base->getPrev());
        base->getPrev()->setNext(*newNode);
        base->setPrev(*newNode);
    }
    size += 1;
    return this;
}

template <class T>
LinkedListSequence<T>* LinkedListSequence<T>::Prepend(T & item)
{
    ShrdPtr<Node<T>>* newNode = new ShrdPtr<Node<T>>(new Node<T>(item));
    if (size == 0)
    {
        base = *newNode;
        base->setNext(base);
        base->setPrev(base);
    }
    else if (size == 1)
    {
        base->setNext(*newNode);
        base->setPrev(base->getNext());
        base->getNext()->setPrev(base);
        base->getNext()->setNext(base);
        base = *newNode;

    }
    else
    {
        base->getPrev()->setNext(*newNode);
        (*newNode)->setPrev(base->getPrev());
        base->setPrev(*newNode);
        (*newNode)->setNext(base);
        base = *newNode;

    }
    size += 1;
    return this;
}

template <class T>
LinkedListSequence<T>* LinkedListSequence<T>::InsertAt(T & item, size_t pos)
{
    ShrdPtr<Node<T>>* newNode = new ShrdPtr<Node<T>>(new Node<T>(item));
    if (size == 0)
    {
        base = *newNode;
        base->setNext(base);
        base->setPrev(base);
    }
    else
    {
        ShrdPtr<Node<T>> actual(std::move(base));
        for (int i = 0; i < pos - 1; i++)
        {
            actual = actual->getNext();
        }
        actual = std::move(actual->getNext());
        (*newNode)->setNext(actual);
        (*newNode)->setPrev(actual->getPrev());
        actual->getPrev()->setNext(*newNode);
        actual->setPrev(*newNode);
    }
    size += 1;
    return this;
}

template <class T>
T & LinkedListSequence<T>::GetFirst() 
{
    if(this->size != 0)
    {
        return base->getVal();
    }
    else
    {
        throw "There are no items in list!";
    }
}

template <class T>
T& LinkedListSequence<T>::GetLast()
{
    if(this->size != 0)
    {
        return base->getPrev()->getVal();
    }
    else
    {
        throw "Threre are no intems in list!";
    }
}

template <class T>
T& LinkedListSequence<T>::Get(size_t index)
{
    ShrdPtr<Node<T>> &actual(base);
    for (int i = 0; i < index; i++)
    {
        actual = actual->getNext();
    }
    T& res = actual->getVal();
    for (int i = 0; i < index; i++)
    {
        actual = actual->getPrev();
    }
    
    return res;
}

template<class T>
LinkedListSequence<T> & LinkedListSequence<T>::GetSubSequence(size_t startIndex, size_t endIndex)
{
    LinkedListSequence<T> * res = new LinkedListSequence<T>();
    for (int i = startIndex; i < endIndex; i++)
    {
        (*res).Append(this->Get(i));
    }
    
    return *res;
}

template <class T>
LinkedListSequence<T>& LinkedListSequence<T>::Concat(Sequence<T> & seq)
{
    LinkedListSequence<T>* res = new LinkedListSequence<T>();
    for (int i = 0; i < this->size; i++)
    {
        res->Append(this->Get(i));
    }
    for (int i = 0; i < seq.GetLenght(); i++)
    {
        res->Append(seq.Get(i));
    }
    return *res;
}