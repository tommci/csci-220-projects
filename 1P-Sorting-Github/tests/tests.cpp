/*
 * Author: C. Painter Wakefield & Tolga Can
 *
 * Tests for the sorting project.
 */

#include <cstdlib>   // for rand()
#include <algorithm> // for sort(), is_sorted()
#include <vector>
#include <iostream>  // for operator<< 

#include "gtest/gtest.h"
#include "sorter.h"

#define LARGE_SET_SIZE  100000
#define VERY_LARGE_SET_SIZE  1000000

using namespace std;

// Template tests
string randomString(int n) {
    string s = "";
    for (int i=0; i<n; i++)
    {
        s+=(rand()%26+'a');
    }
    return s;
}

class foo {
public:
    foo() { _x = 0; _y = 0; }
    foo(int x, int y) { _x = x; _y = y; }

    bool operator<(const foo& b) const {
        if (_x == b._x) return _y < b._y;
        else return _x < b._x;
    }
    bool operator>(const foo& b) const { return b < *this; }
    bool operator!=(const foo& b) const { return *this < b || b < *this; }
    bool operator==(const foo& b) const { return ((*this)._x == b._x &&  (*this)._y == b._y); }
    bool operator<=(const foo& b) const { return !(b < *this); }
    bool operator>=(const foo& b) const { return !(*this < b); }

private:
    int _x, _y;

friend ostream& operator<<(ostream&, const foo&);

};

ostream& operator<<(ostream& out, const foo& f) {
    out << "foo(" << f._x << ", " << f._y << ")";
    return out;
}

TEST(SorterTest, IntBaseCase0K2) {
    vector<int> a;
    sorter(a, 2);
    ASSERT_TRUE(a.empty());
}

TEST(SorterTest, IntBaseCase0K3) {
    vector<int> a;
    sorter(a, 3);
    ASSERT_TRUE(a.empty());
}

TEST(SorterTest, IntBaseCase1K2) {
    vector<int> a = { 42 };
    sorter(a, 2);
    ASSERT_TRUE(a.size() == 1);
    ASSERT_EQ(a[0], 42);
}

TEST(SorterTest, IntBaseCase1K3) {
    vector<int> a = { 17 };
    sorter(a, 3);
    ASSERT_TRUE(a.size() == 1);
    ASSERT_EQ(a[0], 17);
}

TEST(SorterTest, StringBaseCase1K2) {
    vector<string> a = { "hello" };
    sorter(a, 2);
    ASSERT_TRUE(a.size() == 1);
    ASSERT_EQ(a[0], string("hello"));
}

TEST(SorterTest, IntTwoElementsK2) {
    vector<int> a = {1, 2};
    vector<int> b = a;
    sorter(a, 2);
    ASSERT_EQ(a, b);
    a = {2, 1};
    sorter(a, 2);
    ASSERT_EQ(a, b);
}

TEST(SorterTest, IntVerySmallRandom) {
    vector<int> a = {10, 12, 2, 17, -4, 0, -9, 31, 6, 11};
    vector<int> a_copy = a;
    vector<int> b = {-9, -4, 0, 2, 6, 10, 11, 12, 17, 31};
    vector<int> kvals = {2, 3, 5, 10, 17};

    for (int k: kvals) {
        a = a_copy;
        sorter(a, k);
        ASSERT_EQ(a, b);
    }
}

TEST(SorterTest, IntVerySmallSorted) {
    vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> b = a;
    vector<int> kvals = {2, 3, 5, 10, 17};

    for (int k: kvals) {
        sorter(a, k);
        ASSERT_EQ(a, b);
    }
}

TEST(SorterTest, IntVerySmallReverseSorted) {
    vector<int> a = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    vector<int> a_copy = a;
    vector<int> b = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> kvals = {2, 3, 5, 10, 17};

    for (int k: kvals) {
        a = a_copy;
        sorter(a, k);
        ASSERT_EQ(a, b);
    }
}

TEST(SorterTest, IntVerySmallAllEqual) {
    vector<int> a = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    vector<int> b = a;
    vector<int> kvals = {2, 3, 5, 10, 17};

    for (int k: kvals) {
        sorter(a, k);
        ASSERT_EQ(a, b);
    }
}

TEST(SorterTest, StringVerySmall) {
    srand(1234);
    vector<string> a;
    for (int i = 0; i < 10; i++) {
        a.push_back(randomString((rand()%10) + 3));
    }
    vector<string> a_copy = a;
    vector<string> b = a;
    std::sort(b.begin(), b.end());

    vector<int> kvals = {2, 3, 5, 10, 17};

    for (int k: kvals) {
        a = a_copy;
        sorter(a, k);
        ASSERT_EQ(a, b);
    }
}

TEST(SorterTest, FooVerySmall) {
    srand(1234);
    vector<foo> a;
    for (int i = 0; i < 10; i++) {
        a.push_back(foo(rand() % 5, rand() % 5));
    }
    vector<foo> a_copy = a;
    vector<foo> b = a;
    std::sort(b.begin(), b.end());

    vector<int> kvals = {2, 3, 5, 10, 17};

    for (int k: kvals) {
        a = a_copy;
        sorter(a, k);
        ASSERT_EQ(a, b);
    }
}

TEST(SorterTest, LargeK2) {
    srand(1234);
    vector<int> a;
    for (int i = 0; i < LARGE_SET_SIZE; i++) {
        a.push_back(rand());
    }
    sorter(a, 2);
    ASSERT_TRUE(is_sorted(a.begin(),a.end()));
}

TEST(SorterTest, LargeK3) {
    srand(1234);
    vector<int> a;
    for (int i = 0; i < LARGE_SET_SIZE; i++) {
        a.push_back(rand());
    }
    sorter(a, 3);
    ASSERT_TRUE(is_sorted(a.begin(),a.end()));
}

TEST(SorterTest, LargeK30) {
    srand(1234);
    vector<int> a;
    for (int i = 0; i < LARGE_SET_SIZE; i++) {
        a.push_back(rand());
    }
    sorter(a, 30);
    ASSERT_TRUE(is_sorted(a.begin(),a.end()));
}

TEST(SorterTest, LargeK300) {
    srand(1234);
    vector<int> a;
    for (int i = 0; i < LARGE_SET_SIZE; i++) {
        a.push_back(rand());
    }
    sorter(a, 300);
    ASSERT_TRUE(is_sorted(a.begin(),a.end()));
}

TEST(SorterTest, VeryLarge) {
    srand(1234);
    vector<int> a;
    for (int i = 0; i < VERY_LARGE_SET_SIZE; i++) {
        a.push_back(rand());
    }
    sorter(a, 4);
    ASSERT_TRUE(is_sorted(a.begin(),a.end()));
}

#include "sneaky-student-sort.h"   // SneakyStudentSort test
