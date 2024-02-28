#pragma once

#include <algorithm>
#include <stdexcept>


namespace stack_lib {
    template<typename T>
    class Stack {
    public:
        using value_type = T;
        using pointer = T*;
        using size_type = size_t;
    private:
        size_type capacity_{start_capacity_};
        size_type size_{0};
        pointer data_;
        static constexpr int start_capacity_ = 2;

        void checkAndRealloc() {
            if (size_ == capacity_) {
                capacity_ *= 2;
                pointer new_data = new T[capacity_];
                std::copy(data_, data_ + size_, new_data);
                delete[] data_;
                data_ = new_data;
            }
        }

        void checkNonempty() const {
            if (empty()) {
                throw std::out_of_range("Stack is empty and top or pop method was called");
            }
        }

    public:
        Stack() {
            data_ = new T[capacity_];
        }

        Stack(const Stack& other)
                : capacity_(other.capacity_),
                  size_(other.size_) {
            data_ = new T[capacity_];
            std::copy(other.data_, other.data_ + other.size_, data_);
        }

        Stack(Stack&& other) noexcept
                : capacity_(other.capacity_),
                  size_(other.size_),
                  data_(std::exchange(other.data_, nullptr)) {}

        Stack& operator=(const Stack& other) {
            *this = Stack(other);
            return *this;
        }

        Stack& operator=(Stack&& other) noexcept {
            std::swap(capacity_, other.capacity_);
            std::swap(size_, other.size_);
            data_ = std::exchange(other.data_, nullptr);
            return *this;
        }

        ~Stack() noexcept {
            delete[] data_;
            data_ = nullptr;
            capacity_ = 0;
            size_ = 0;
        }

        [[nodiscard]] size_type size() const noexcept {
            return size_;
        }

        [[nodiscard]] bool empty() const {
            return size_ == 0;
        }

        void push(const value_type& elem) {
            checkAndRealloc();
            data_[size_] = elem;
            size_++;
        }

        void push(value_type&& elem) {
            checkAndRealloc();
            data_[size_] = std::move(elem);
            size_++;
        }

        void pop() {
            checkNonempty();
            size_--;
        }

        value_type top() {
            checkNonempty();
            return data_[size_ - 1];
        }
    };
}