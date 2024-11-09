#pragma once
#include <functional>
#include <cstddef>
#include "Ptr.h"

template<class T>
class ShrdPtr;

template <class T>
class WeakPtr : public Ptr<T> {
private:
    size_t* counterS;
    size_t* counterW;
    void release();

public:
    template<class U>
    WeakPtr(WeakPtr<U>&);

    WeakPtr(WeakPtr<T>&&);

    template<class U>
    WeakPtr(const WeakPtr<U>&);

    template<class U>
    WeakPtr(ShrdPtr<U>&);

    template<class U>
    WeakPtr(ShrdPtr<U>&&);

    template<class U>
    WeakPtr(const ShrdPtr<U>&);

    template<class U>
    WeakPtr(const ShrdPtr<U>&&);

    template<class U>
    WeakPtr<T>& operator=(WeakPtr<U>&);

    template<class U>
    WeakPtr<T>& operator=(WeakPtr<U>&&) noexcept;

    template<class U>
    WeakPtr<T>& operator=(const WeakPtr<U>&);

    template<class U>
    WeakPtr<T>& operator=(const WeakPtr<U>&&) noexcept;

    template<class U>
    WeakPtr<T>& operator=(ShrdPtr<U>&);

    template<class U>
    WeakPtr<T>& operator=(ShrdPtr<U>&&);

    template<class U>
    WeakPtr<T>& operator=(const ShrdPtr<U>&);

    template<class U>
    WeakPtr<T>& operator=(const ShrdPtr<U>&&);

    size_t countW();

    size_t countS();

    size_t* getWCounter()
    {
        return this->counterW;
    }

    size_t* getSCounter()
    {
        return this->counterS;
    }

    ~WeakPtr();

    void reset();
};

template<class T>
template<class U>
WeakPtr<T>::WeakPtr(WeakPtr<U>& other)
{
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterW = other.getWCounter();
        *(this->counterW) += 1;
        this->counterS = other.getSCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
WeakPtr<T>::WeakPtr(WeakPtr<T>&& other)
{
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterW = other.getWCounter();
        *(this->counterW) += 1;
        this->counterS = other.getSCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
WeakPtr<T>::WeakPtr(const WeakPtr<U>& other)
{
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterW = other.getWCounter();
        *(this->counterW) += 1;
        this->counterS = other.getSCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
WeakPtr<T>::WeakPtr(ShrdPtr<U>& other)
{
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterW = other.getWCounter();
        *(this->counterW) += 1;
        this->counterS = other.getSCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
WeakPtr<T>::WeakPtr(ShrdPtr<U>&& other)
{
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterW = other.getWCounter();
        *(this->counterW) += 1;
        this->counterS = other.getSCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
WeakPtr<T>::WeakPtr(const ShrdPtr<U>& other)
{
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterW = other.getWCounter();
        *(this->counterW) += 1;
        this->counterS = other.getSCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
WeakPtr<T>::WeakPtr(const ShrdPtr<U>&& other)
{
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterW = other.getWCounter();
        *(this->counterW) += 1;
        this->counterS = other.getSCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
WeakPtr<T>& WeakPtr<T>::operator=(WeakPtr<U>& other)
{
    this->release();
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterW = other.getWCounter();
        *(this->counterW) += 1;
        this->counterS = other.getSCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
WeakPtr<T>& WeakPtr<T>::operator=(WeakPtr<U>&& other) noexcept
{
    this->release();
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.ptr);
        this->counterW = std::move(other.counterW);
        *(this->counterW) += 1;
        this->counterS = std::move(other.counterS);
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr<U>& other)
{
    this->release();
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.ptr);
        this->counterW = other.getWCounter();
        *(this->counterW) += 1;
        this->counterS = other.getSCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr<U>&& other) noexcept
{
    this->release();
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.ptr);
        this->counterW = std::move(other.counterW);
        *(this->counterW) += 1;
        this->counterS = std::move(other.counterS);
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
WeakPtr<T>& WeakPtr<T>::operator=(ShrdPtr<U>& other)
{
    this->release();
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterW = other.getWCounter();
        *(this->counterW) += 1;
        this->counterS = other.getSCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
WeakPtr<T>& WeakPtr<T>::operator=(ShrdPtr<U>&& other)
{
    this->release();
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterW = other.getWCounter();
        *(this->counterW) += 1;
        this->counterS = other.getSCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
WeakPtr<T>& WeakPtr<T>::operator=(const ShrdPtr<U>& other)
{
    this->release();
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterW = other.getWCounter();
        *(this->counterW) += 1;
        this->counterS = other.getSCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
template<class U>
WeakPtr<T>& WeakPtr<T>::operator=(const ShrdPtr<U>&& other)
{
    this->release();
    if (std::is_base_of<T, U>() || typeid(T) == typeid(U))
    {
        this->ptr = static_cast<T*>(other.get());
        this->counterW = other.getWCounter();
        *(this->counterW) += 1;
        this->counterS = other.getSCounter();
    }
    else
    {
        throw "Input type is not allowed!";
    }
}

template<class T>
WeakPtr<T>::~WeakPtr()
{
    this->release();
    this->counterS = nullptr;
    this->counterW = nullptr;
    this->ptr = nullptr;
}

template <class T>
size_t WeakPtr<T>::countW()
{
    if (this->counterW != nullptr)
    {
        return *(this->counterW);
    }
    return size_t(0);
}

template <class T>
size_t WeakPtr<T>::countS()
{
    if (this->counterS != nullptr)
    {
        return *(this->counterS);
    }
    return size_t(0);
}

template <class T>
void WeakPtr<T>::release()
{
    if ((this->ptr != nullptr) && (*(this->counterS) == 0))
    {
        delete this->counterS;
        delete this->counterW;
    }
    else if (this->ptr != nullptr)
    {
        *(this->counterW) -= 1;
    }

}

template<class T>
void WeakPtr<T>::reset()
{
    this->release();
    this->counterS = nullptr;
    this->counterW = nullptr;
    this->ptr = nullptr;
}