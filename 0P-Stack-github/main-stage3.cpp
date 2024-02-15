/*
 * main-stage3.cpp
 *
 * Includes the main() function for the stack project (stages 2 & 3).
 *
 * This code is included in the build target "run-stage3-main", and
 * in the convenience targets "stage2", and "stage3".
 */

#include <iostream>
#include <chrono>

#include "stack-stage3.h"

using namespace std;

double time_n_pushes(unsigned n);
double run_tests(unsigned int c, unsigned n);

int main() {

    unsigned val = 100000;

    cout << val << " pushes took an avg of " << run_tests(10, val) << " ms" << endl;

    cout << "Runtime finished" << endl;
    return 0;
}

// times how long it takes to push n items to a stack (the stack defined in stack-stage3.h)
double time_n_pushes(unsigned n) 
{
    stack<unsigned> s;
    // get starting clock value
    auto start_time = chrono::system_clock::now();
    // do the n pushes
    for (unsigned i = 0; i < n; i++) 
    {
        s.push(i);
    }
    // get ending clock value
    auto stop_time = chrono::system_clock::now();
    // compute elapsed time in seconds
    chrono::duration<double> elapsed = stop_time - start_time;
    return elapsed.count();
}

// runs n push tests c times and averages, returns that average
double run_tests(unsigned int c, unsigned n)
{
    double sum = 0;
    for( unsigned int i = 0; i < c; i++ )
    {
        sum += time_n_pushes(n);
    }

    // value returned is in milliseconds (ms)
    return (sum / c) * 1000.0;
}
