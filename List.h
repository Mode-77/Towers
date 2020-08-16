#pragma once

#include <vector>


template<typename T> class List {
public:
    void add(const T&);
    void remove(size_t index);
    void clear();

    T& front();
    T& back();
    T& at(size_t index);
    const T& at(size_t index) const;

    size_t length() const;
    bool isEmpty() const;

protected:
    std::vector<T> internalStruct;
};


template<typename T>
void List<T>::add(const T& t)
{
    internalStruct.push_back(t);
}


template<typename T>
void List<T>::remove(size_t index)
{
    internalStruct.erase(internalStruct.begin() + index);
}


template<typename T>
void List<T>::clear()
{
    internalStruct.clear();
}


template<typename T>
T& List<T>::at(size_t index)
{
    return internalStruct.at(index);
}


template<typename T>
const T& List<T>::at(size_t index) const
{
    return internalStruct.at(index);
}


template<typename T>
T& List<T>::front()
{
    return internalStruct.front();
}


template<typename T>
T& List<T>::back()
{
    return internalStruct.back();
}


template<typename T>
size_t List<T>::length() const
{
    return internalStruct.size();
}


template<typename T>
bool List<T>::isEmpty() const
{
    return internalStruct.empty();
}
