#pragma once
#include <utility>
template <class T>
class Ptr
{
protected:
    T* ptr;
public:
    virtual T* operator->() const = 0; // get ptr

    T& operator*() // get value
    {
        return *ptr;
    }

    const T& operator*() const // get const value
    {
        return *ptr;
    }

    virtual T* get() const = 0; // get pointer
    

    operator bool() const
    {
        if (ptr == nullptr)
        {
            return false;
        }
        return true;
    }

    bool operator!() const
    {
        if (ptr == nullptr)
        {
            return true;
        }
        return false;
    }
};