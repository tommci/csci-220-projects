/***
 * ensure dynamic allocation
 */

#ifndef STACK_USE_DYNAMIC_ALLOCATION_H
#define STACK_USE_DYNAMIC_ALLOCATION_H

TEST(ProjectRequirements, UsesDynamicAllocation) {
    /***
     * Students:  if you are caught by this test, it seems you are not using
     * new[] in your stack object (as the project write-up says to do).  Instead
     * you might be doing T _data[SOME_LARGE_NUMBER].  You need to use new[].
     */
    stack stk;
    ASSERT_LT(sizeof(stk), 100);
}

#endif
