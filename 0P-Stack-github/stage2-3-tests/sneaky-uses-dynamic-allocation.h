/***
 * ensure dynamic allocation
 */

#ifndef TSTACK_USE_DYNAMIC_ALLOCATION_H
#define TSTACK_USE_DYNAMIC_ALLOCATION_H

TEST(ProjectRequirements, UsesDynamicAllocation) {
    stack<std::string> stk;
    if( sizeof(stk) >= 100 ) {
        std::cerr << "Your _empty_ stack<std::string> object is very large." << std::endl << 
                     "Are you using dynamically allocated (new[], new) memory (as the write-up says to do)" << std::endl <<
                     "or a statically allocated array (T array[SOME_REAL_BIG_NUMBER])?" << std::endl;
    }
    ASSERT_LT(sizeof(stk), 100);
}

#endif
