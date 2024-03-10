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
#include <cmath>
#include <chrono>

#include "sorter.h"

using namespace std;

double run_test(int s, int k);

int main() {
    // You can use this main() to run your own analysis or testing code.
    srand(time(0));

    cout << "enter size of input (will be multiplied by 10,000) (range of 10 - 50):" << endl;
    int s;
    cin >> s;
    s = s * 10000;

    cout << "enter k value:" << endl;
    int k;
    cin >> k;
    cout << endl;

    cout << "sorting " << s << " items with k = " << k << " took " << run_test(s, k) << " s" << endl;
    cout << "!!! running complete !!!" << endl;

    return 0;
}

double run_test(int s, int k)
{
    vector<int> v;
    for( int i = 0; i < s; i++)
    {
        v.push_back(rand());
    }
    // get starting clock value
    auto start_time = chrono::system_clock::now();
    // do work
    sorter(v, k);
    // get ending clock value
    auto stop_time = chrono::system_clock::now();
    // compute elapsed time in seconds
    chrono::duration<double> elapsed = stop_time - start_time;

    // value returned is in seconds (s)
    return elapsed.count();
}