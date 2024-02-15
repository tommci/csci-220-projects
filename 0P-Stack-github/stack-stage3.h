/*
 * stack-stage3.h
 *
 * Implements a simple stack class using dynamic arrays.
 * This may be implemented in 3 stages:
 *   Stage 1: non-template stack class storing strings,
 *            unsafe copies/assignments
 *   Stage 2: template stack class, unsafe copies/assignments
 *   Stage 3: template stack class, safe copies/assignments
 *
 * Note: no underflow detection is performed.  Performing pop() or top()
 * on an empty stack results in undefined behavior (possibly crashing your
 * program)!
 *
 * Author: Your Name
 */

#ifndef _STACK_H
#define _STACK_H

#include <cstddef> // for size_t
#include <string>  // for stage 1
#include <iostream> // for debugging

using namespace std;

template <typename T>
class stack {
  public:
    T top();
    void push(const T &);
    void pop();
    size_t size();
    bool is_empty();

    stack();
    stack(const stack&);
    stack<T>& operator=(const stack<T>&);
    ~stack();

  private:
    T* _data;
    int _length;
    int _capacity;
};

// ----- METHODS -----

template <typename T>
stack<T>::stack()
{
    _data = new T[1];
    _capacity = 1;
    _length = 0;
}

template <typename T>
stack<T>::~stack()
{
    delete[] _data;
}

template <typename T>
stack<T>::stack(const stack& OLD)
{
    _capacity = OLD._capacity;
    _length = OLD._length;

    _data = new T[_capacity];
    for( int i = 0; i < _length; i++ )
    {
        _data[i] = OLD._data[i];
    }
}

template <typename T>
stack<T>& stack<T>::operator=(const stack<T>& RHS)
{
    if( this == &RHS ) { return *this; }
    delete[] _data;

    _capacity = RHS._capacity;
    _length = RHS._length;

    _data = new T[_capacity];
    for( int i = 0; i < _length; i++ )
    {
        _data[i] = RHS._data[i];
    }

    return *this;
}

template <typename T>
T stack<T>::top() 
{
    if( !this->is_empty() ) { return _data[_length - 1]; }
    else { return T(); }
}

template <typename T>
void stack<T>::push(const T& ITEM)
{
// DOUBLE CAPACITY METHOD
    // if( _length == _capacity )
    // {
    //     T* temp = new T[_capacity * 2];
    //     for(int i = 0; i < _length; i++)
    //     {
    //         temp[i] = _data[i];
    //     }
    //     delete[] _data;
    //     _data = temp;
    //     _capacity *= 2;
    // }

    // _data[_length] = ITEM;
    // _length++;

// NEW ARRAY EACH PUSH METHOD
    T* temp = new T[_length + 1];
    for(int i = 0; i < _length; i++)
    {
        temp[i] = _data[i];
    }
    delete[] _data;
    _data = temp;

    _data[_length] = ITEM;
    _length++;

}

template <typename T>
void stack<T>::pop()
{
    if( !this->is_empty() )
    {
        _length--; 
    }
}

template <typename T>
size_t stack<T>::size()
{
    return _length;
}

template <typename T>
bool stack<T>::is_empty()
{
    if( _length == 0 ) { return true; }
    else { return false; }
}

#endif
