#pragma once

#include <algorithm>
#include <stdexcept>


#define START_CAPACITY 2

namespace stack_lib {
    template<class T>
    class Stack {
    private:
        size_t capacity_{START_CAPACITY};
        size_t size_{0};
        T* data_;

        void checkAndRealloc() {
            if (size_ == capacity_) {
                capacity_ *= 2;
                T* new_data_ = new T[capacity_];
                std::copy(data_, data_ + size_, new_data_);
                delete[] data_;
                data_ = new_data_;
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

        [[nodiscard]] size_t size() const noexcept {
            return size_;
        }

        [[nodiscard]] bool empty() const {
            return size_ == 0;
        }

        template<class U>
        void push(U&& elem) {
            checkAndRealloc();
            data_[size_] = elem;
            size_++;
        }

        void pop() {
            checkNonempty();
            size_--;
        }

        T top() const {
            checkNonempty();
            return data_[size_ - 1];
        }

        const T* begin() const {
            return data_;
        }

        const T* end() const {
            return data_ + size_;
        }
    };
}