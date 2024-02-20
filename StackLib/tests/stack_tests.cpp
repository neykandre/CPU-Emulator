#include "stack.hpp"
#include "gtest/gtest.h"


void testFilling(stack_lib::Stack<int>& a) {
    for (int i = 0; i < 10; ++i) {
        a.push(i);
    }
}

TEST(Constructors, defaultConstructor) {
    EXPECT_NO_THROW(stack_lib::Stack<int> a);
}

TEST(Constructors, copyConstructor) {
    stack_lib::Stack<int> a;
    testFilling(a);
    EXPECT_NO_THROW(stack_lib::Stack<int> (a));
}

TEST(Constructors, moveConstructor) {
    stack_lib::Stack<int> a;
    testFilling(a);
    EXPECT_NO_THROW(stack_lib::Stack<int>(std::move(a)));
}

TEST(Assignment, copyAssignment) {
    stack_lib::Stack<int> a;
    stack_lib::Stack<int> b;
    testFilling(a);
    EXPECT_NO_THROW(b = a);
}

TEST(Assignment, moveAssignment) {
    stack_lib::Stack<int> a;
    stack_lib::Stack<int> b;
    testFilling(a);
    EXPECT_NO_THROW(b = std::move(a));
}

TEST(Methods, pushThrow) {
    stack_lib::Stack<int> a;
    int b = 34;
    EXPECT_NO_THROW(a.push(12));
    EXPECT_NO_THROW(a.push(b));
    EXPECT_NO_THROW(a.push(std::move(b)));
}

TEST(Methods, peekThrow) {
    stack_lib::Stack<int> a;
    EXPECT_THROW(a.top(), std::out_of_range);
    int b = 34;
    a.push(12);
    EXPECT_NO_THROW(a.top());
    a.push(b);
    EXPECT_NO_THROW(a.top());
}

TEST(Methods, popThrow) {
    stack_lib::Stack<int> a;
    EXPECT_THROW(a.pop(), std::out_of_range);
    int b = 34;
    a.push(12);
    EXPECT_NO_THROW(a.pop());
    a.push(b);
    EXPECT_NO_THROW(a.pop());
    EXPECT_THROW(a.pop(), std::out_of_range);
}

TEST(Methods, pushPeekValue) {
    stack_lib::Stack<int> a;
    int b = 34;
    a.push(12);
    EXPECT_EQ(a.top(), 12);
    a.push(b);
    EXPECT_EQ(a.top(), b);
    a.push(std::move(b));
    EXPECT_EQ(a.top(), 34);
}

TEST(Methods, pushPopPeekValue) {
    stack_lib::Stack<int> a;
    int b = 34;

    a.push(12);
    a.push(b);
    EXPECT_EQ(a.top(), b);
    a.pop();
    EXPECT_EQ(a.top(), 12);

    a.push(std::move(b));
    EXPECT_EQ(a.top(), 34);
    a.pop();
    EXPECT_EQ(a.top(), 12);
}

TEST(Methods, size) {
    stack_lib::Stack<int> a;
    EXPECT_EQ(a.size(), 0);
    testFilling(a);
    EXPECT_EQ(a.size(), 10);
    a.pop();
    EXPECT_EQ(a.size(), 9);
    a.pop();
    EXPECT_EQ(a.size(), 8);
    a.top();
    EXPECT_EQ(a.size(), 8);
    a.push(1);
    EXPECT_EQ(a.size(), 9);
    a.push(1); //10
    a.push(1); //11
    a.push(1); //12
    a.push(1); //13
    a.push(1); //14
    a.push(1); //15
    EXPECT_EQ(a.size(), 15);
    a.push(1); //16 (power of 2)
    EXPECT_EQ(a.size(), 16);
    a.push(1); //17 (realloc)
    EXPECT_EQ(a.size(), 17);
}

TEST(Methods, empty) {
    stack_lib::Stack<int> a;
    EXPECT_TRUE(a.empty());

    a.push(1);
    EXPECT_FALSE(a.empty());
    a.push(1);
    EXPECT_FALSE(a.empty());

    a.pop();
    EXPECT_FALSE(a.empty());
    a.pop();
    EXPECT_TRUE(a.empty());
}

TEST(Pointers, begin) {
    stack_lib::Stack<int> a;
    testFilling(a);
    EXPECT_NO_THROW(a.begin());
}

TEST(Pointers, end) {
    stack_lib::Stack<int> a;
    testFilling(a);
    EXPECT_NO_THROW(a.end());
}

TEST(Pointers, iteration) {
    stack_lib::Stack<int> a;
    testFilling(a);
    EXPECT_NO_THROW(
            for (auto x: a) {}
    );
    EXPECT_NO_THROW(
            for (auto& x: a) {}
    );

    int i = 0;
    for (auto &x : a) {
        EXPECT_EQ(x, i);
        i++;
    }

    i = 0;
    for (auto x : a) {
        EXPECT_EQ(x, i);
        i++;
    }
}