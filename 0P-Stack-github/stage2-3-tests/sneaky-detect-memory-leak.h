/**
 *  Catch memory leaks by the student
**/

#ifndef TSTACK_DETECT_MEMORY_LEAK_H
#define TSTACK_DETECT_MEMORY_LEAK_H

#include <cstdint>

/**
 *  A class for creating objects that are aware of their collective state
 *      authors     Anastasia Sokol
 *  
 *  Using an object designed this way it is possible to ensure that every
 *  object created is destructed between a given region
 *  This reveals most memory errors made using new/delete and many made using
 *  std::allocator or malloc/free
**/

#include <cstdint>

class MemoryObserver {
    private:
        static std::size_t observers;

    public:
        MemoryObserver(){ ++observers; }
        MemoryObserver(const MemoryObserver&){ ++observers; }
        MemoryObserver(const MemoryObserver&&){ ++observers; }

        MemoryObserver& operator =(const MemoryObserver&){ return *this; };
        MemoryObserver& operator =(const MemoryObserver&&){ return *this; };

        ~MemoryObserver(){ --observers; }

        static std::size_t global_number_of_observers(){
            return observers;
        }
};

std::size_t MemoryObserver::observers = 0;

TEST(Dynamic, DetectMemoryLeak) {
    const std::size_t start = MemoryObserver::global_number_of_observers();
    
    {
        // create stack with specialized type to trigger detection
        stack<MemoryObserver> stack;

        // make sure that the code actually works (prevents specialization to no-op)
        for(std::size_t i = 0; i < 10; ++i){
            stack.push(MemoryObserver());
        }

        for(std::size_t i = 0; i < 8 /** avoid pop-ing every element just in case of not-quite-correct attempts to preventing memory leaks **/; ++i){
            stack.pop();
        }
    }

    const std::size_t end = MemoryObserver::global_number_of_observers();

    // ensure that the code block destructs every object it creates
    ASSERT_EQ(start, end);
}

#endif
