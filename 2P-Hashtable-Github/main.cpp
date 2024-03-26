/*
 * main.cpp
 *
 * Includes the main() function for the hashtable project.
 *
 * This code is included in the default build target.  It
 * produces the program run-main.
*/

#include <iostream>
#include <string>

#include "hashtable.h"
#include "hash_functions.h"

using namespace std;

int main() {
    // You can use this main() to run your own analysis or testing code.
    cout << "If you are seeing this, you have successfully run main!" << endl;

    // ==================================================================
    // The code below this point is relevant for the analysis part of the
    // hashtable project.  You do not need it for the programming part.
    // ==================================================================

    // The code below illustrates how to use the provided hash function 
    // "functional" objects, and lets you see the different hash values 
    // produced by each.
    hash0 h0;
    hash1 h1;
    hash2 h2;
    hash3 h3;
    hash4 h4;

    string s("Hello");
    cout << h0(s) << endl;
    cout << h1(s) << endl;
    cout << h2(s) << endl;
    cout << h3(s) << endl;
    cout << h4(s) << endl;

    // Here's how you create a hashtable to use a particular hash function:
    hashtable<string, hash1> ht;
    ht.insert(s);
}

