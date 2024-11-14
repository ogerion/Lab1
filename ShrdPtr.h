#pragma once
#include "Ptr.h"

template<class T>
class WeakPtr;

template <class T>
class ShrdPtr : public Ptr<T> {
private:
    size_t* counterS;
    size_t* counterW;
    void release();

public:
    ShrdPtr();

    ShrdPtr(T*);

    template<class U>
    ShrdPtr(ShrdPtr<U>&&);

    template<class U>
    ShrdPtr(const ShrdPtr<U>&);

    template<class U>
    ShrdPtr(WeakPtr<U>&&);

    template<class U>
    explicit ShrdPtr(const WeakPtr<U>&);

    template<class U>
    ShrdPtr<T>& operator=(ShrdPtr<U>&&);

    template<class U>
    ShrdPtr<T>& operator=(const ShrdPtr<U>&);

    template<class U>
    ShrdPtr<T>& operator=(WeakPtr<U>&&);

    template<class U>
    ShrdPtr<T>& operator=(const WeakPtr<U>&);

    size_t countW();

    size_t countS();

    size_t* getWCounter() const
    {
        return this->counterW;
    }

    size_t* getSCounter() const
    {
        return this->counterS;
    }

    ~ShrdPtr();

    void reset();
};

template<class T>
ShrdPtr<T>::ShrdPtr()
{
    this->ptr = nullptr;
    this->counterS = new size_t(1);
    this->counterW = new size_t(0);
}

template<class T>
ShrdPtr<T>::ShrdPtr(T* ptr)
{
    this->ptr = ptr;
    this->counterS = new size_t(1);
    this->counterW = new size_t(0);
}

template<class T>
template<class U>
ShrdPtr<T>::ShrdPtr(ShrdPtr<U>&& other)
{
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterS = other.getSCounter();
        *(this->counterS) += 1;
        this->counterW = other.getWCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
ShrdPtr<T>::ShrdPtr(const ShrdPtr<U>& other)
{
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterS = other.getSCounter();
        *(this->counterS) += 1;
        this->counterW = other.getWCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
ShrdPtr<T>::ShrdPtr(WeakPtr<U>&& other)
{
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterS = other.getSCounter();
        *(this->counterS) += 1;
        this->counterW = other.getWCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
ShrdPtr<T>::ShrdPtr(const WeakPtr<U>& other)
{
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterS = other.getSCounter();
        *(this->counterS) += 1;
        this->counterW = other.getWCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
ShrdPtr<T>& ShrdPtr<T>::operator=(ShrdPtr<U>&& other)
{
    this->release();
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterS = other.getSCounter();
        *(this->counterS) += 1;
        this->counterW = other.getWCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
ShrdPtr<T>& ShrdPtr<T>::operator=(const ShrdPtr<U>& other)
{
    this->release();
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterS = other.getSCounter();
        *(this->counterS) += 1;
        this->counterW = other.getWCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}


template<class T>
template<class U>
ShrdPtr<T>& ShrdPtr<T>::operator=(WeakPtr<U>&& other)
{
    this->release();
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterS = other.getSCounter();
        *(this->counterS) += 1;
        this->counterW = other.getWCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
ShrdPtr<T>& ShrdPtr<T>::operator=(const WeakPtr<U>& other)
{
    this->release();
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterS = other.getSCounter();
        *(this->counterS) += 1;
        this->counterW = other.getWCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
ShrdPtr<T>::~ShrdPtr()
{
    this->release();
    this->counterS = nullptr;
    this->counterW = nullptr;
    this->ptr = nullptr;
}

template <class T>
size_t ShrdPtr<T>::countW()
{
    if (this->counterW != nullptr)
    {
        return *(this->counterW);
    }
    return size_t(0);
}

template <class T>
size_t ShrdPtr<T>::countS()
{
    if (this->counterS != nullptr)
    {
        return *(this->counterS);
    }
    return size_t(0);
}

template <class T>
void ShrdPtr<T>::release()
{
    if (this->ptr == nullptr)
    {

    }
    else if ((this->counterS != nullptr) && (*(this->counterS) - 1 == 0))
    {
        delete this->counterS;
        delete this->counterW;
        delete this->ptr;
    }
    else if (this->ptr != nullptr)
    {
        *(this->counterS) -= 1;
    }

}

template<class T>
void ShrdPtr<T>::reset()
{
    this->release();
    this->counterS = nullptr;
    this->counterW = nullptr;
    this->ptr = nullptr;
}
