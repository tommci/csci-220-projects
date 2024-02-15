/**
 *  Test that the student is not over allocating stack space
**/

#ifndef TSTACK_DETECT_LARGE_BUFFER_H
#define TSTACK_DETECT_LARGE_BUFFER_H

/**
 *  A class for creating objects that are aware of the extent to which they
 *  have ever existed
 *      authors     Anastasia Sokol
 *  
 *  Using an object designed this way it is possible to ensure that the maximum
 *  number of objects never exceeded a certain limit
**/

#include <algorithm>
#include <cstdint>

class MaxMemoryObserver {
    private:
        static std::size_t observers;
        static std::size_t maximum;

    public:
        MaxMemoryObserver(){ maximum = std::max(maximum, ++observers); }
        MaxMemoryObserver(const MaxMemoryObserver&){ maximum = std::max(maximum, ++observers); }
        MaxMemoryObserver(const MaxMemoryObserver&&){ maximum = std::max(maximum, ++observers); }

        MaxMemoryObserver& operator =(const MaxMemoryObserver&){ return *this; };
        MaxMemoryObserver& operator =(const MaxMemoryObserver&&){ return *this; };

        ~MaxMemoryObserver(){ --observers; }

        static std::size_t global_observer_max(){
            return maximum;
        }
};

std::size_t MaxMemoryObserver::observers = 0;
std::size_t MaxMemoryObserver::maximum = 0;


TEST(Dynamic, DetectLargeBuffer) {
    // create stack with specialized type to trigger detection
    stack<MaxMemoryObserver> stack;

    // make sure that the code actually works (prevents specialization to no-op)
    for(std::size_t i = 0; i < 10; ++i){
        stack.push(MaxMemoryObserver());
    }

    // make sure that the code actually works (prevents specialization to no-op)
    for(std::size_t i = 0; i < 10; ++i){
        stack.pop();
    }

    // ensure that the code is within a reasonable maximum number of objects
    //      10 objects pushed implies a reasonable limit is probably 32, 64 just in case
    ASSERT_LE(MaxMemoryObserver::global_observer_max(), 64);
}

#endif
