#include <iostream>
#include "stack.hpp"

using namespace StackLib;

int main() {
    Stack<int> st;
    st.push(123);
    int a = 32;
    st.push(a);
    st.push(std::move(a));

    Stack<int> st2;
    st2 = st;

    st2.pop();
    std::cout << st2.peek() << std::endl;
    st2.pop();
    std::cout << st2.peek() << std::endl;
    st2.pop();
    std::cout << st2.peek() << std::endl;
    st2.pop();
    std::cout << st2.peek() << std::endl;

    st2.push(a);


//    for (auto& x: st) {
//        std::cout << x << std::endl;
//    }
    std::cout << "--------" << std::endl;

    for (auto& x: st2) {
        std::cout << x << std::endl;
    }
}