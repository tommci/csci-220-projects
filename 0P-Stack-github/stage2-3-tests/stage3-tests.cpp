/*
 * Authors: Joey Lovato & C. Painter Wakefield
 *
 * Tests for the stack lab (stage 3)
 * This set of tests checks for correct operation of
 * the copy constructor and assignment operator and that dynamic
 * allocation is being used.
 */

#include <string>
#include "gtest/gtest.h"
#include "stack-stage3.h"

using namespace std;

#include "stage2-3-tests/sneaky-detect-large-buffer.h"     // ensure super large buffers are not being used
														   
#include "stage2-3-tests/sneaky-uses-dynamic-allocation.h" // ensure dynamic allocation
														   
#include "stage2-3-tests/sneaky-use-newdelete-ops.h"       // assure new[] and delete[] are being used
													   
// Copy constructor
TEST(CopyConstructor, EmptyStack) {
    stack<string> stk1;
    stack<string> stk2 = stk1;
    ASSERT_TRUE(stk1.is_empty());
    ASSERT_TRUE(stk2.is_empty());
    ASSERT_EQ(stk1.size(), stk2.size());
    ASSERT_EQ(stk2.size(), 0);
}

TEST(CopyConstructor, PushOne) {
    stack<string> stk1;
    stk1.push("apple");
    stack<string> stk2 = stk1;
    ASSERT_EQ(stk1.top(), "apple");
    ASSERT_EQ(stk2.top(), "apple");
    ASSERT_EQ(stk2.size(), stk1.size());
    ASSERT_EQ(stk2.size(), 1);
}

TEST(CopyConstructor, PushFive) {
    stack<string> stk1;
    vector<string> strings = {"alpha", "beta", "gamma", "delta", "epsilon"};
    for(string s: strings) {
        stk1.push(s);
    }
    stack<string> stk2 = stk1;
    ASSERT_EQ(stk1.top(), "epsilon");
    ASSERT_EQ(stk2.top(), "epsilon");
    ASSERT_EQ(stk2.size(), stk1.size());
    ASSERT_EQ(stk2.size(), 5);
}

TEST(CopyConstructor, PushPopTopOne) {
    stack<string> stk1;
    stk1.push("apple");
    stack<string> stk2 = stk1;
    stk1.pop();
    stk1.push("banana");
    ASSERT_EQ(stk1.top(), "banana");
    ASSERT_EQ(stk2.top(), "apple");
}

TEST(CopyConstructor, PushPopTopOneReverse) {
    stack<string> stk1;
    stk1.push("apple");
    stack<string> stk2 = stk1;
    stk2.pop();
    stk2.push("banana");
    ASSERT_EQ(stk2.top(), "banana");
    ASSERT_EQ(stk1.top(), "apple");
}

TEST(CopyConstructor, PushFiveTopPopAll) {
    stack<string> stk1;
    vector<string> strings = {"alpha", "beta", "gamma", "delta", "epsilon"};
    for (string s: strings) {
        stk1.push(s);
    }
    stack<string> stk2 = stk1;

    for (int i = strings.size() - 1; i >= 0; i--) {
        ASSERT_EQ(stk1.top(), strings[i]);
        ASSERT_EQ(stk2.top(), strings[i]);
        stk1.pop();
        stk2.pop();
    }
}

TEST(CopyConstructor, Multiple) {
    stack<string> stk1;
    stk1.push("apple");
    stack<string> stk2 = stk1;

    stk1.push("banana");
    stk1.push("cherry");
    stk1.push("durian");
    stk1.push("elderberry");

    stk2.push("fig");
    stk2.push("gooseberry");
    stk2.push("honeydew");

    ASSERT_EQ(stk1.top(), "elderberry");
    stk1.pop();
    ASSERT_EQ(stk1.top(), "durian");
    stk1.pop();
    ASSERT_EQ(stk1.top(), "cherry");
    stk1.pop();
    ASSERT_EQ(stk1.top(), "banana");
    stk1.pop();
    ASSERT_EQ(stk1.top(), "apple");
    stk1.pop();
    ASSERT_TRUE(stk1.is_empty());

    ASSERT_EQ(stk2.top(), "honeydew");
    stk2.pop();
    ASSERT_EQ(stk2.top(), "gooseberry");
    stk2.pop();
    ASSERT_EQ(stk2.top(), "fig");
    stk2.pop();
    ASSERT_EQ(stk2.top(), "apple");
    stk2.pop();
    ASSERT_TRUE(stk2.is_empty());
}

TEST(AssignmentOperator, EmptyStack) {
    stack<string> stk1;
    stack<string> stk2;
    stk2 = stk1;
    ASSERT_TRUE(stk1.is_empty());
    ASSERT_TRUE(stk2.is_empty());
    ASSERT_EQ(stk1.size(), stk2.size());
}

TEST(AssignmentOperator, PushOne) {
    stack<string> stk1;
    stk1.push("apple");
    stack<string> stk2;
    stk2.push("banana");
    stk2 = stk1;
    ASSERT_EQ(stk1.top(), "apple");
    ASSERT_EQ(stk2.top(), "apple");
    ASSERT_EQ(stk2.size(), stk1.size());
    ASSERT_EQ(stk2.size(), 1);}

TEST(AssignmentOperator, PushFive) {
    stack<string> stk1;
    vector<string> strings1 = {"alpha", "beta", "gamma", "delta", "epsilon"};
    for(string s: strings1) {
        stk1.push(s);
    }
    stack<string> stk2;
    vector<string> strings2 = {"apple", "banana", "cherry"};
    for (string s: strings2) {
        stk2.push(s);
    }
    stk2 = stk1;
    ASSERT_EQ(stk1.top(), "epsilon");
    ASSERT_EQ(stk2.top(), "epsilon");
    ASSERT_EQ(stk2.size(), stk1.size());
    ASSERT_EQ(stk2.size(), 5);
}

TEST(AssignmentOperator, PushPopTopOne) {
    stack<string> stk1;
    stk1.push("apple");
    stack<string> stk2;
    stk2.push("banana");
    stk2 = stk1;

    stk1.pop();
    stk1.push("cherry");
    ASSERT_EQ(stk1.top(), "cherry");
    ASSERT_EQ(stk2.top(), "apple");
}

TEST(AssignmentOperator, PushPopTopOneReverse) {
    stack<string> stk1;
    stk1.push("apple");
    stack<string> stk2;
    stk2.push("banana");
    stk2 = stk1;

    stk2.pop();
    stk2.push("cherry");
    ASSERT_EQ(stk2.top(), "cherry");
    ASSERT_EQ(stk1.top(), "apple");
}

TEST(AssignmentOperator, PushFiveTopPopAll) {
    stack<string> stk1;
    vector<string> strings = {"alpha", "beta", "gamma", "delta", "epsilon"};
    for (string s: strings) {
        stk1.push(s);
    }
    stack<string> stk2;
    vector<string> strings2 = {"apple", "banana", "cherry"};
    for (string s: strings2) {
        stk2.push(s);
    }
    stk2 = stk1;

    for (int i = strings.size() - 1; i >= 0; i--) {
        ASSERT_EQ(stk1.top(), strings[i]);
        ASSERT_EQ(stk2.top(), strings[i]);
        stk1.pop();
        stk2.pop();
    }
}

TEST(AssignmentOperator, Multiple) {
    stack<string> stk1;
    stk1.push("apple");

    stack<string> stk2;
    vector<string> strings2 = {"apple", "banana", "cherry"};
    for (string s: strings2) {
        stk2.push(s);
    }
    stk2 = stk1;

    stk1.push("banana");
    stk1.push("cherry");
    stk1.push("durian");
    stk1.push("elderberry");

    stk2.push("fig");
    stk2.push("gooseberry");
    stk2.push("honeydew");

    ASSERT_EQ(stk1.top(), "elderberry");
    stk1.pop();
    ASSERT_EQ(stk1.top(), "durian");
    stk1.pop();
    ASSERT_EQ(stk1.top(), "cherry");
    stk1.pop();
    ASSERT_EQ(stk1.top(), "banana");
    stk1.pop();
    ASSERT_EQ(stk1.top(), "apple");
    stk1.pop();
    ASSERT_TRUE(stk1.is_empty());

    ASSERT_EQ(stk2.top(), "honeydew");
    stk2.pop();
    ASSERT_EQ(stk2.top(), "gooseberry");
    stk2.pop();
    ASSERT_EQ(stk2.top(), "fig");
    stk2.pop();
    ASSERT_EQ(stk2.top(), "apple");
    stk2.pop();
    ASSERT_TRUE(stk2.is_empty());
}

TEST(AssignmentOperator, SelfAssignment) {
    stack<string> stk1;
    stk1.push("apple");
    stk1.push("banana");
    stk1.push("cherry");

    stk1 = stk1;    // this may result in a warning on Mac OS with clang

    ASSERT_EQ(stk1.top(), "cherry");
    stk1.pop();
    ASSERT_EQ(stk1.top(), "banana");
    stk1.pop();
    ASSERT_EQ(stk1.top(), "apple");
    stk1.pop();
}

TEST(AssignmentOperator, Chaining) {
    stack<string> stk1;
    stk1.push("apple");

    stack<string> stk2;
    stk2.push("banana");

    stack<string> stk3;
    stk3.push("cherry");

    stk1 = stk2 = stk3;

    ASSERT_EQ(stk1.top(), "cherry");
    ASSERT_EQ(stk1.size(), 1);
}

#include "stage2-3-tests/sneaky-detect-memory-leak.h"      // memory leaks?

