#include <ctime>
#include <iostream>
#include <string>
#include "stack.hpp"

using namespace stack_lib;

int main() {
    Stack<int> sub_st;
    Stack<int> sub_st2;
    Stack<Stack<int>> st;
    std::clock_t start, end;

    for(int i = 0; i < 1e8; ++i) {
        sub_st.push(10);
    }

    start = std::clock();
    st.push(sub_st);
    end = std::clock();
    std::cout << "Copy push: ";
    std::cout << 1000.0 * (end - start) / CLOCKS_PER_SEC << std::endl;
    std::cout << sub_st.size() << std::endl;

    start = std::clock();
    st.push(std::move(sub_st));
    end = std::clock();
    std::cout << "Move push: ";
    std::cout << 1000.0 * (end - start) / CLOCKS_PER_SEC << std::endl;
    std::cout << sub_st.size() << std::endl;

    sub_st = Stack<int>();


    for(int i = 0; i < 1e8; ++i) {
        sub_st.push(10);
    }

    start = std::clock();
    sub_st2 = sub_st;
    end = std::clock();
    std::cout << "Copy assignment: ";
    std::cout << 1000.0 * (end - start) / CLOCKS_PER_SEC << std::endl;
    std::cout << sub_st.size() << std::endl;
    std::cout << sub_st2.size() << std::endl;

    start = std::clock();
    sub_st2 = std::move(sub_st);
    end = std::clock();
    std::cout << "Move assignment: ";
    std::cout << 1000.0 * (end - start) / CLOCKS_PER_SEC << std::endl;
    std::cout << sub_st.size() << std::endl;
    std::cout << sub_st2.size() << std::endl;

    start = std::clock();
    Stack<int> sub_st3(sub_st2);
    end = std::clock();
    std::cout << "Copy constructor: ";
    std::cout << 1000.0 * (end - start) / CLOCKS_PER_SEC << std::endl;
    std::cout << sub_st2.size() << std::endl;
    std::cout << sub_st3.size() << std::endl;

    start = std::clock();
    Stack<int> sub_st4(std::move(sub_st2));
    end = std::clock();
    std::cout << "Move constructor: ";
    std::cout << 1000.0 * (end - start) / CLOCKS_PER_SEC << std::endl;
    std::cout << sub_st2.size() << std::endl;
    std::cout << sub_st4.size() << std::endl;
}