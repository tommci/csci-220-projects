/*
 * hash_functions.cpp
 *
 * Author: C. Painter-Wakefield and J. Lovato
 *
 * Some string hashing functions for use in the hashtable assignment.
 *
 * Last modified: 10/17/2022
 */

#ifndef _HASH_FUNCTIONS_H
#define _HASH_FUNCTIONS_H

#include <string>

using namespace std;

class hash0 : hash<string> {
public:
    size_t operator()(const string &);
};

class hash1 : hash<string> {
public:
    size_t operator()(const string &);
};

class hash2 : hash<string> {
public:
    size_t operator()(const string &);
};

class hash3 : hash<string> {
public:
    size_t operator()(const string &);
};

class hash4 : hash<string> {
public:
    size_t operator()(const string &);
};

#endif
