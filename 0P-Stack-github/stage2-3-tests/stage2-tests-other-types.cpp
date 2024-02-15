/*
 * Authors: Joey Lovato & C. Painter Wakefield
 *
 * Tests for the stack lab (stages 2 and 3).
 * This set of tests validates the behavior of the stack
 * template class using types other than string.
 */

#include "gtest/gtest.h"
#include "stack-stage3.h"

using namespace std;

// a user-defined class to use with our stack template
class foo {
public:
    foo() = default;
    foo(int v) { _x = v; }
    bool operator==(const foo& f) const { return _x == f._x; }
private:
    int _x = 0;
friend ostream& operator<<(ostream& out, const foo& f);
};

ostream& operator<<(ostream& out, const foo& f) {
    out << "foo(" << f._x << ")";
    return out;
}

// integers
TEST(IntegerStack, FiveElementsTopPopAll) {
    stack<int> stk;
    vector<int> vals = {1, 2, 3, 4, 5};
    for(int x: vals) {
        stk.push(x);
    }
    ASSERT_EQ(stk.top(), 5);
    stk.pop();
    ASSERT_EQ(stk.top(), 4);
    stk.pop();
    ASSERT_EQ(stk.top(), 3);
    stk.pop();
    ASSERT_EQ(stk.top(), 2);
    stk.pop();
    ASSERT_EQ(stk.top(), 1);
}

// foos
TEST(FooStack, FiveElementsTopPopAll) {
    stack<foo> stk;
    vector<int> vals = {1, 2, 3, 4, 5};
    for(int x: vals) {
        stk.push(foo(x));
    }
    ASSERT_EQ(stk.top(), foo(5));
    stk.pop();
    ASSERT_EQ(stk.top(), foo(4));
    stk.pop();
    ASSERT_EQ(stk.top(), foo(3));
    stk.pop();
    ASSERT_EQ(stk.top(), foo(2));
    stk.pop();
    ASSERT_EQ(stk.top(), foo(1));
}

