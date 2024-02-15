/*
 * Authors: Joey Lovato & C. Painter Wakefield
 *
 * Tests for the stack lab (stages 2 and 3).
 * These are the stage 1 tests, but now expecting a template class.
 */

#include <string>
#include "gtest/gtest.h"
#include "stack-stage3.h"

using namespace std;

// Basic tests - should work with a stack 
// using a fixed-size array of size at least 3.
TEST(Basic, DefaultConstructor) {
    stack<string> stk;
    ASSERT_TRUE(stk.is_empty());
    ASSERT_EQ(stk.size(), 0);
}

TEST(Basic, OneElementSize) {
    stack<string> stk;
    stk.push("a");
    ASSERT_EQ(stk.size(), 1);
}

TEST(Basic, OneElementNotEmpty) {
    stack<string> stk;
    stk.push("a");
    ASSERT_FALSE(stk.is_empty());
}

TEST(Basic, OneElementTop) {
    stack<string> stk;
    stk.push("a");
    ASSERT_EQ(stk.top(), "a");
}

TEST(Basic, OneElementPop) {
    stack<string> stk;
    stk.push("a");
    stk.pop();
    ASSERT_TRUE(stk.is_empty());
    ASSERT_EQ(stk.size(), 0);
}

TEST(Basic, ThreeElementsTop) {
    stack<string> stk;
    stk.push("a");
    ASSERT_EQ(stk.top(), "a");
    stk.push("b");
    ASSERT_EQ(stk.top(), "b");
    stk.push("c");
    ASSERT_EQ(stk.top(), "c");
}

TEST(Basic, ThreeElementsSizeNotEmpty) {
    stack<string> stk;
    stk.push("a");
    stk.push("b");
    stk.push("c");
    ASSERT_EQ(stk.size(), 3);
    ASSERT_FALSE(stk.is_empty());
}

TEST(Basic, ThreeElementsTopPopAll) {
    stack<string> stk;
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
    stack<string> stk;
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
    stack<string> stk;
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

#include "stage2-3-tests/sneaky-prevent-std-containers.h" // dissuade students from using standard containers

TEST(Dynamic, FourElements) {
    stack<string> stk;
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
    stack<string> stk;
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
    stack<string> stk;
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
    stack<string> stk;
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
    stack<string> stk;
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
    stack<string> stk;
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
    stack<string> stk;
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


