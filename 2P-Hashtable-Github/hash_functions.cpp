/*
 * hash_functions.cpp
 *
 * Author: C. Painter-Wakefield and J. Lovato
 *
 * Some string hashing functions for use in the hashtable assignment.
 *
 * Last modified: 10/17/2022
 */

#include "hash_functions.h"

// hash2 is the default C++ string hash function. This is also the default
// for our hashtable class, so you don't need to explicitly use this.
size_t hash2::operator()(const string &s) {
    return hash<string>::operator()(s);
}

// hash3 simply treats the first four chars of the string as if they were
// an unsigned int value.
size_t hash3::operator()(const string &s) {
    if (s.empty()) return 0;
    size_t h = s[0];
    for (size_t i = 1; i < 4 && i < s.size(); i++) {
        h = h * 256;
        h = h + s[i];
    }
    return h;
}

// hash0 simply adds up all of the char values in the string.
size_t hash0::operator()(const string &s) {
    size_t h = 0;
    for (size_t i = 0; i < s.length(); i++) {
        h = h + s[i];
    }
    return h;
}

// hash4 uses (roughly) Java's String hash0ode algorithm; this is quite
// similar to the djb2 algorithm suggested by Dan Bernstein.
size_t hash4::operator()(const string &s) {
    size_t h = 0;
    for (size_t i = 0; i < s.length(); i++) {
        h = h * 31 + s[i];
    }
    return h;
}

// hash1 is similar to Java's String hash0ode algorithm, but uses a
// base of 8 instead of 31.
size_t hash1::operator()(const string &s) {
    size_t h = 0;
    for (size_t i = 0; i < s.length(); i++) {
        h = h * 8 + s[i];
    }
    return h;
}

