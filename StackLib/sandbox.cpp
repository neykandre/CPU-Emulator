#include <iostream>
#include "stack.hpp"

using namespace stack_lib;

int main() {
    Stack<int> st;
    st.push(123);
    int a = 32;
    st.push(a);
    st.push(std::move(a));

    Stack<int> st2;
    st2 = st;

    for (auto& x: st2) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    st2.pop();
    std::cout << st2.top() << std::endl;

    for (auto& x: st2) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    st2.pop();
    std::cout << st2.top() << std::endl;
    for (auto& x: st2) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    st2.pop();
    std::cout << st2.top() << std::endl;
//    st2.pop();
    std::cout << st2.top() << std::endl;

    st2.push(a);


//    for (auto& x: st) {
//        std::cout << x << std::endl;
//    }
    std::cout << "--------" << std::endl;



    for (auto& x: st2) {
        std::cout << x << std::endl;
    }
}