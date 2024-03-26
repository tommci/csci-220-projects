/*
 * hashtable.h
 *
 * A basic hashtable implementation.  This hashtable uses vectors,
 * rather than linked lists, to implement chaining.
 * 
 * Author: <your name here>
 */

#ifndef _HASHTABLE_PROJECT_H
#define _HASHTABLE_PROJECT_H

#include <functional>   // for std::hash
#include <algorithm>
#include <vector>

using namespace std;

template <class T, class H = std::hash<T>>
class hashtable {
public:
    // constructor
    hashtable();

    // basic hashset operations
    void insert(const T& key);
    void remove(const T& key);
    bool contains(const T& key);
    size_t size();

    // diagnostic functions
    double load_factor();

    // convenience method, invokes the "hash" template parameter
    // function object to get a hash code
    static size_t hash(const T &key) {
        H h;
        return h(key);
    }

private:

    vector<vector<T>> _table;
    size_t _size;

};

template <class T, class H>
hashtable<T, H>::hashtable()
{
    _table.resize(4);
    _size = 0;
}

template <class T, class H>
void hashtable<T, H>::insert(const T& key)
{
    if( contains(key) ) { return; }
    size_t idx;
    if( load_factor() >= 0.75 )
    {
        vector<vector<T>> tempTable;
        tempTable.resize(_table.size() * 2);
        T tempKey = T();
        // rehash existing keys into new table
        for( size_t i = 0; i < _table.size(); i++ )
        {
            for( size_t j = 0; j < _table.at(i).size(); j++ )
            {
                tempKey = _table.at(i).at(j);
                idx = hash(tempKey) % tempTable.size();
                tempTable.at(idx).push_back(tempKey);
            }
        }
        _table.swap(tempTable);
    }
    // append key to appropriate chain
    idx = hash(key) % _table.size();
    _table.at(idx).push_back(key);
    _size++;
}

template <class T, class H>
void hashtable<T,H>::remove(const T& key)
{
    if( !contains(key) ) { return; }
    size_t idx = hash(key) % _table.size();
    _table.at(idx).erase(find(_table.at(idx).begin(), _table.at(idx).end(), key));
    _size--;
}

template <class T, class H>
bool hashtable<T, H>::contains(const T& key)
{
    size_t idx = hash(key) % _table.size();
    for( size_t i = 0; i < _table.at(idx).size(); i++ )
    {
        if(_table.at(idx).at(i) == key ) { return true; }
    }
    return false;
}

template <class T, class H>
size_t hashtable<T, H>::size()
{
    return _size;
}

template <class T, class H>
double hashtable<T, H>::load_factor()
{
    return (double)_size / (double)_table.size();
}

#endif
