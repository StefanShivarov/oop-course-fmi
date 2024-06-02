#pragma once
#include <iostream>

// using the pair template class from lectures

template <class T1, class T2>
class Pair 
{
public:
    Pair() = default;
    Pair(const T1& first, const T2& second);

    const T1& getFirst() const;
    const T2& getSecond() const;

    void setFirst(const T1& obj);
    void setFirst(T1&& obj);
    void setSecond(const T2& obj);
    void setSecond(T2&& obj);
private:
    T1 first;
    T2 second;
};

template<class T1, class T2>
Pair<T1, T2>::Pair(const T1& first, const T2& second) : first(first), second(second) {}

template<class T1, class T2>
const T1& Pair<T1, T2>::getFirst() const
{
    return first;
}

template<class T1, class T2>
const T2& Pair<T1, T2>::getSecond() const
{
    return second;
}

template<class T1, class T2>
void Pair<T1, T2>::setFirst(const T1& obj)
{
    first = obj;
}

template<class T1, class T2>
void Pair<T1, T2>::setFirst(T1&& obj)
{
    first = std::move(obj);
}

template<class T1, class T2>
void Pair<T1, T2>::setSecond(const T2& obj)
{
    second = obj;
}

template<class T1, class T2>
void Pair<T1, T2>::setSecond(T2&& obj)
{
    second = std::move(obj);
}
