#pragma once
template <class T>
class Ptr
{
protected:
    T* ptr;
public:
    T* operator->() //get ptr
    {
        return ptr;
    }
    const T* operator->() const // get const ptr
    {
        return ptr;
    }

    T& operator*() // get value
    {
        return *ptr;
    }

    const T& operator*() const // get const value
    {
        return *ptr;
    }

    T* get() // get pointer
    {
        return ptr;
    }

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