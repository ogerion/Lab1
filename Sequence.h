#pragma once

template <class T>
class Sequence
{
    protected:
        size_t size;
    public:
        virtual T & GetFirst() = 0;
        virtual T & GetLast() = 0;
        virtual T & Get(size_t index) = 0;

        virtual Sequence<T> * Append(T &) = 0;
        virtual Sequence<T> * Prepend(T &) = 0;
        virtual Sequence<T> * InsertAt(T &, size_t index) = 0;

        int GetLenght() const
        {
            return this->size;
        };
        
        T & operator[] (const size_t index)
        {
            return this->Get(index);
        }
        
        Sequence<T> * operator + (const Sequence<T> * seq2)
        {
            return this->Concat(seq2);
        }        

        Sequence<T> & operator += (const Sequence<T> * seq2)
        {
            Sequence * res = this->Concat(seq2);
            return *res;
        }

        virtual Sequence<T> & GetSubSequence(size_t,size_t) = 0;
        virtual Sequence<T> & Concat(Sequence<T> &) = 0;

};
