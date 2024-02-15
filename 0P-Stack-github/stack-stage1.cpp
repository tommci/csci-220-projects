/*
 * stack-stage1.cpp
 *
 * Method definitions for the stack implementation (stage 1).
 *
 * Author: Your Name
 */

#include "stack-stage1.h"

stack::stack()
{
    _data = new string[1];
    _capacity = 1;
    _length = 0;
}

string stack::top() 
{
    if( !this->is_empty() ) { return _data[_length - 1]; }
    else { return "0"; }
}

void stack::push(const string& STR)
{
    if( _length == _capacity )
    {
        string* temp = new string[_capacity * 2];
        for(int i = 0; i < _length; i++)
        {
            temp[i] = _data[i];
        }
        delete[] _data;
        _data = temp;
        _capacity *= 2;
    }

    _data[_length] = STR;
    _length++;
}

void stack::pop()
{
    if( !this->is_empty() )
    {
        _length--; 
    }
}

size_t stack::size()
{
    return _length;
}

bool stack::is_empty()
{
    if( _length == 0 ) { return true; }
    else { return false; }
}