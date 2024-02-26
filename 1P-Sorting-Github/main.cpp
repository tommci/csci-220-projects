/*
 * main.cpp
 *
 * Includes the main() function for the sorting project. 
 *
 * This code is included in the build target "run-main"
*/

#include <iostream>
#include <cstddef>
#include <vector>

#include "sorter.h"

using namespace std;

int main() {
    // You can use this main() to run your own analysis or testing code.
    vector<int> ok = { 89, -6, 1, 45, 4, 3, 78, 2, 999, 6, 3, 2, 1000};
    for( size_t i = 0; i < ok.size(); i++)
    {
        cout << ok.at(i) << " ";
    }
    cout << endl;

    sorter(ok, 5);

    for( size_t i = 0; i < ok.size(); i++)
    {
        cout << ok.at(i) << " ";
    }
    cout << endl;

    return 0;
}


