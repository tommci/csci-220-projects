/*
 * Authors: Joey Lovato & C. Painter Wakefield
 *
 * Tests for the stack lab (stage 1).
 * This set of tests assumes a non-template stack class
 * storing strings only.
 */

#include <string>
#include "gtest/gtest.h"
#include "stack-stage1.h"

using namespace std;

// Basic tests - should work with a stack 
// using a fixed-size array of size at least 3.
TEST(Basic, DefaultConstructor) {
    stack stk;
    ASSERT_TRUE(stk.is_empty());    // stack should start out empty
    ASSERT_EQ(stk.size(), 0);       // stack should start out size zero
}

TEST(Basic, OneElementSize) {
    stack stk;
    stk.push("a");
    ASSERT_EQ(stk.size(), 1);   // stack size should be 1 after pushing 1 element
}

TEST(Basic, OneElementNotEmpty) {
    stack stk;
    stk.push("a");
    ASSERT_FALSE(stk.is_empty());   // stack should be non-empty after pushing 1 element
}

TEST(Basic, OneElementTop) {
    stack stk;
    stk.push("a");
    ASSERT_EQ(stk.top(), "a");  // top element should match pushed element
}

TEST(Basic, OneElementPop) {
    stack stk;
    stk.push("a");
    stk.pop();
    ASSERT_TRUE(stk.is_empty());    // stack is restored to empty after 1 push, 1 pop
    ASSERT_EQ(stk.size(), 0);       // stack is restored to zero size after 1 push, 1 pop
}

TEST(Basic, ThreeElementsTop) {
    stack stk;
    stk.push("a");
    ASSERT_EQ(stk.top(), "a");
    stk.push("b");
    ASSERT_EQ(stk.top(), "b");
    stk.push("c");
    ASSERT_EQ(stk.top(), "c");
}

TEST(Basic, ThreeElementsSizeNotEmpty) {
    stack stk;
    stk.push("a");
    stk.push("b");
    stk.push("c");
    ASSERT_EQ(stk.size(), 3);
    ASSERT_FALSE(stk.is_empty());
}

TEST(Basic, ThreeElementsTopPopAll) {
    stack stk;
    stk.push("a");
    stk.push("b");
    stk.push("c");
    ASSERT_EQ(stk.top(), "c");
    stk.pop();
    ASSERT_EQ(stk.top(), "b");
    stk.pop();
    ASSERT_EQ(stk.top(), "a");
}

TEST(Basic, ThreeElementsSizePopAll) {
    stack stk;
    stk.push("a");
    stk.push("b");
    stk.push("c");
    ASSERT_EQ(stk.size(), 3);
    ASSERT_FALSE(stk.is_empty());
    stk.pop();
    ASSERT_EQ(stk.size(), 2);
    ASSERT_FALSE(stk.is_empty());
    stk.pop();
    ASSERT_EQ(stk.size(), 1);
    ASSERT_FALSE(stk.is_empty());
    stk.pop();
    ASSERT_EQ(stk.size(), 0);
    ASSERT_TRUE(stk.is_empty());
}

TEST(Basic, MixedOperations) {
    stack stk;
    stk.push("a");
    stk.push("b");
    ASSERT_EQ(stk.top(), "b");
    ASSERT_EQ(stk.size(), 2);
    stk.pop();
    ASSERT_EQ(stk.top(), "a");
    ASSERT_EQ(stk.size(), 1);
    stk.push("c");
    ASSERT_EQ(stk.top(), "c");
    ASSERT_EQ(stk.size(), 2);
    stk.push("d");
    ASSERT_EQ(stk.top(), "d");
    ASSERT_EQ(stk.size(), 3);
    stk.pop();
    ASSERT_EQ(stk.top(), "c");
    ASSERT_EQ(stk.size(), 2);
    stk.push("e");
    ASSERT_EQ(stk.top(), "e");
    ASSERT_EQ(stk.size(), 3);
    stk.pop();
    stk.pop();
    ASSERT_EQ(stk.top(), "a");
    ASSERT_EQ(stk.size(), 1);
    stk.pop();
    ASSERT_EQ(stk.size(), 0);
    ASSERT_TRUE(stk.is_empty());
}

// Dynamic tests - these are intended to test a stack
// using a dynamically allocated array with resizing
TEST(Dynamic, FourElements) {
    stack stk;
    vector<string> strings = {"alpha", "beta", "gamma", "delta"};
    ASSERT_TRUE(stk.is_empty());
    for(size_t i = 0; i < strings.size(); i++) {
        stk.push(strings[i]);
        ASSERT_EQ(stk.size(), i + 1);
        ASSERT_EQ(stk.top(), strings[i]);
        ASSERT_FALSE(stk.is_empty());
    }
    for (int i = strings.size() - 1; i >= 0; i--) {
        ASSERT_EQ(stk.size(), i + 1);
        ASSERT_EQ(stk.top(), strings[i]);
        ASSERT_FALSE(stk.is_empty());        
        stk.pop();
    }
    ASSERT_EQ(stk.size(), 0);
    ASSERT_TRUE(stk.is_empty());
}

TEST(Dynamic, FiveElements) {
    stack stk;
    vector<string> strings = {"alpha", "beta", "gamma", "delta", "epsilon"};
    ASSERT_TRUE(stk.is_empty());
    for(size_t i = 0; i < strings.size(); i++) {
        stk.push(strings[i]);
        ASSERT_EQ(stk.size(), i + 1);
        ASSERT_EQ(stk.top(), strings[i]);
        ASSERT_FALSE(stk.is_empty());
    }
    for (int i = strings.size() - 1; i >= 0; i--) {
        ASSERT_EQ(stk.size(), i + 1);
        ASSERT_EQ(stk.top(), strings[i]);
        ASSERT_FALSE(stk.is_empty());        
        stk.pop();
    }
    ASSERT_EQ(stk.size(), 0);
    ASSERT_TRUE(stk.is_empty());
}

TEST(Dynamic, EightElements) {
    stack stk;
    vector<string> strings = {"alpha", "beta", "gamma", "delta", "epsilon", "zeta", "eta", "theta"};
    ASSERT_TRUE(stk.is_empty());
    for(size_t i = 0; i < strings.size(); i++) {
        stk.push(strings[i]);
        ASSERT_EQ(stk.size(), i + 1);
        ASSERT_EQ(stk.top(), strings[i]);
        ASSERT_FALSE(stk.is_empty());
    }
    for (int i = strings.size() - 1; i >= 0; i--) {
        ASSERT_EQ(stk.size(), i + 1);
        ASSERT_EQ(stk.top(), strings[i]);
        ASSERT_FALSE(stk.is_empty());        
        stk.pop();
    }
    ASSERT_EQ(stk.size(), 0);
    ASSERT_TRUE(stk.is_empty());
}

TEST(Dynamic, ThirteenElements) {
    stack stk;
    vector<string> strings = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m"};
    ASSERT_TRUE(stk.is_empty());
    for(size_t i = 0; i < strings.size(); i++) {
        stk.push(strings[i]);
        ASSERT_EQ(stk.size(), i + 1);
        ASSERT_EQ(stk.top(), strings[i]);
        ASSERT_FALSE(stk.is_empty());
    }
    for (size_t i = strings.size() - 1; i > 0; i--) {
        ASSERT_EQ(stk.size(), i + 1);
        ASSERT_EQ(stk.top(), strings[i]);
        ASSERT_FALSE(stk.is_empty());        
        stk.pop();
    }
    stk.pop();
    ASSERT_EQ(stk.size(), 0);
    ASSERT_TRUE(stk.is_empty());
}

TEST(Dynamic, MixedOperations) {
    stack stk;
    stk.push("alpha");
    stk.push("beta");
    stk.push("gamma");
    ASSERT_EQ(stk.top(), "gamma");
    ASSERT_EQ(stk.size(), 3);
    stk.pop();
    ASSERT_EQ(stk.top(), "beta");
    ASSERT_EQ(stk.size(), 2);
    stk.push("delta");
    ASSERT_EQ(stk.top(), "delta");
    ASSERT_EQ(stk.size(), 3);
    stk.push("epsilon");
    ASSERT_EQ(stk.top(), "epsilon");
    ASSERT_EQ(stk.size(), 4);
    stk.pop();
    stk.push("zeta");
    ASSERT_EQ(stk.top(), "zeta");
    ASSERT_EQ(stk.size(), 4);
    stk.push("eta");
    ASSERT_EQ(stk.top(), "eta");
    ASSERT_EQ(stk.size(), 5);
    stk.push("theta");
    ASSERT_EQ(stk.top(), "theta");
    ASSERT_EQ(stk.size(), 6);
    stk.push("iota");
    ASSERT_EQ(stk.top(), "iota");
    ASSERT_EQ(stk.size(), 7);
    stk.push("kappa");
    ASSERT_EQ(stk.top(), "kappa");
    ASSERT_EQ(stk.size(), 8);
    stk.pop();
    stk.pop();
    stk.pop();
    ASSERT_EQ(stk.top(), "eta");
    ASSERT_EQ(stk.size(), 5);
    stk.pop();
    stk.pop();
    stk.pop();
    ASSERT_EQ(stk.top(), "beta");
    ASSERT_EQ(stk.size(), 2);
    stk.pop();
    stk.pop();
    ASSERT_EQ(stk.size(), 0);
    ASSERT_TRUE(stk.is_empty());
}

TEST(Dynamic, LargeMixed) {
    stack stk;
    for(size_t i = 0; i < 1000; i++) {
        stk.push(to_string(i));
        ASSERT_EQ(stk.size(), i + 1);
        ASSERT_EQ(stk.top(), to_string(i));
    }
    for(size_t i = 999; i >= 500; i--) {
        ASSERT_EQ(stk.size(), i + 1);
        ASSERT_EQ(stk.top(), to_string(i));
        stk.pop();
    }
    for(size_t i = 500; i < 1000; i++) {
        stk.push(to_string(i));
        ASSERT_EQ(stk.size(), i + 1);
        ASSERT_EQ(stk.top(), to_string(i));
    }
    for(size_t i = 999; i > 0; i--) {
        ASSERT_EQ(stk.size(), i + 1);
        ASSERT_EQ(stk.top(), to_string(i));
        stk.pop();
    }
    stk.pop();
    ASSERT_EQ(stk.size(), 0);
    ASSERT_TRUE(stk.is_empty());
}

TEST(Dynamic, ExtremelyLarge) {
    stack stk;
    for(size_t i = 0; i < 100000; i++) {
        stk.push(to_string(i));
        ASSERT_EQ(stk.size(), i + 1);
        ASSERT_EQ(stk.top(), to_string(i));
    }
    for(size_t i = 99999; i > 0; i--) {
        ASSERT_EQ(stk.size(), i + 1);
        ASSERT_EQ(stk.top(), to_string(i));
        stk.pop();
    }
    stk.pop();
    ASSERT_EQ(stk.size(), 0);
    ASSERT_TRUE(stk.is_empty());
}

#include "../stage1-tests/sneaky-uses-dynamic-allocation.h"  // ensure dynamic allocation

