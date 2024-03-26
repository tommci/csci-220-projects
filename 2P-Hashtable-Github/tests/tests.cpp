/*
 * Authors: Joey Lovato & C. Painter Wakefield
 *
 * Tests for the hashtable assignment
 * 
 * Last modified: 10/17/2022
 */

#include <vector>
#include <unordered_set>

#include "gtest/gtest.h"

#include "hashtable.h"

#define MAX_WORD_SIZE 10
#define NUMBER_OF_WORDS 200000

using namespace std;

// helper function to produce random word of a given length
string random_word(int len) {
    string random;
    for(int i = 0; i < len; i++) {
        random += 'a' + (rand() % 26);
    }
    return random;
}

// a bad hash function class to test collisions
class bad_hash : hash<string> {
public:
    size_t operator()(const string&) { return 29; }
};

// fixture to set up unique random word vector for use in large testswords.size()
class HashtableTest: public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        srand(1234);
        unordered_set<string> word_set;
        while(word_set.size() < NUMBER_OF_WORDS) {
            word_set.insert(random_word((rand() % MAX_WORD_SIZE) + 1));
        }
        for(const string &s: word_set) {
            words.push_back(s);
        }
    }

    static void TearDownTestSuite() {
        words.clear();
    }

    static vector<string> words;
};

vector<string> HashtableTest::words = vector<string>();

TEST_F(HashtableTest, Empty) {
    hashtable<string> h;
    ASSERT_FALSE(h.contains("apple"));
    ASSERT_EQ(h.size(), 0);
}

TEST_F(HashtableTest, StringInsertRemoveOnce) {
    hashtable<string> h;
    h.insert("apple");
    ASSERT_TRUE(h.contains("apple"));
    ASSERT_EQ(h.size(), 1);
    h.remove("apple");
    ASSERT_FALSE(h.contains("apple"));
    ASSERT_EQ(h.size(), 0);
}

TEST_F(HashtableTest, IntInsertRemoveOnce) {
    hashtable<int> h;
    h.insert(17);
    ASSERT_TRUE(h.contains(17));
    ASSERT_EQ(h.size(), 1);
    h.remove(17);
    ASSERT_FALSE(h.contains(17));
    ASSERT_EQ(h.size(), 0);
}

TEST_F(HashtableTest, InsertTwiceRemoveOnce) {
    hashtable<string> h;
    h.insert("apple");
    h.insert("apple");
    ASSERT_TRUE(h.contains("apple"));
    ASSERT_EQ(h.size(), 1);
    h.remove("apple");
    ASSERT_FALSE(h.contains("apple"));
    ASSERT_EQ(h.size(), 0);
}

TEST_F(HashtableTest, InsertOnceRemoveTwice) {
    hashtable<string> h;
    h.insert("apple");
    ASSERT_TRUE(h.contains("apple"));
    ASSERT_EQ(h.size(), 1);
    h.remove("apple");
    h.remove("apple");
    ASSERT_FALSE(h.contains("apple"));
    ASSERT_EQ(h.size(), 0);
}

TEST_F(HashtableTest, InsertRemoveMany) {
    hashtable<string> h;
    for (size_t i = 0; i < 1000; i++) {
        h.insert(words[i]);
    }

    for (size_t i = 0; i < 1000; i++) {
        ASSERT_TRUE(h.contains(words[i]));
    }

    for (size_t i = 0; i < 1000; i += 2) {
        h.remove(words[i]);
    }

    for (size_t i = 0; i < 1000; i += 2) {
        ASSERT_FALSE(h.contains(words[i]));
    }

    for (size_t i = 1; i < 1000; i += 2) {
        ASSERT_TRUE(h.contains(words[i]));
    }

    for (size_t i = 0; i < 1000; i += 2) {
        h.insert(words[i]);
    }

    for (size_t i = 0; i < 1000; i++) {
        ASSERT_TRUE(h.contains(words[i]));
    }

    for (size_t i = 1; i < 1000; i += 2) {
        h.remove(words[i]);
    }

    for (size_t i = 1; i < 1000; i += 2) {
        ASSERT_FALSE(h.contains(words[i]));
    }

    for (size_t i = 0; i < 1000; i += 2) {
        ASSERT_TRUE(h.contains(words[i]));
    }
}

TEST_F(HashtableTest, CollisionTest) {
    hashtable<string, bad_hash> h;
    for (size_t i = 0; i < 100; i++) {
        h.insert(words[i]);
    }

    for (size_t i = 0; i < 100; i++) {
        ASSERT_TRUE(h.contains(words[i]));
    }

    for (size_t i = 0; i < 100; i += 2) {
        h.remove(words[i]);
    }

    for (size_t i = 0; i < 100; i += 2) {
        ASSERT_FALSE(h.contains(words[i]));
    }

    for (size_t i = 1; i < 100; i += 2) {
        ASSERT_TRUE(h.contains(words[i]));
    }

    for (size_t i = 0; i < 100; i += 2) {
        h.insert(words[i]);
    }

    for (size_t i = 0; i < 100; i++) {
        ASSERT_TRUE(h.contains(words[i]));
    }

    for (size_t i = 1; i < 100; i += 2) {
        h.remove(words[i]);
    }

    for (size_t i = 1; i < 100; i += 2) {
        ASSERT_FALSE(h.contains(words[i]));
    }

    for (size_t i = 0; i < 100; i += 2) {
        ASSERT_TRUE(h.contains(words[i]));
    }
}

TEST_F(HashtableTest, LoadFactorTest) {
    hashtable<string> h;

    // insert some to get the load factor up
    for (size_t i = 0; i < 100; i++) {
        h.insert(words[i]);
        ASSERT_LT(h.load_factor(), 0.76);
    }

    for (size_t i = 0; i < 1000; i++) {
        h.insert(words[i]);
        ASSERT_LT(h.load_factor(), 0.76);   // shouldn't be too full
        ASSERT_GT(h.load_factor(), 0.3);    // shouldn't be too empty, either
    }
}

TEST_F(HashtableTest, LargeTest) {
    hashtable<string> h;
    for (string &s: words) {
        h.insert(s);
    }
    ASSERT_EQ(h.size(), words.size());

    for (string &s: words) {
        ASSERT_TRUE(h.contains(s));
    }

    for (string &s: words) {
        h.remove(s);
    }
    ASSERT_EQ(h.size(), 0);

    for (string &s: words) {
        ASSERT_FALSE(h.contains(s));
    }
}
