#pragma once

#include <algorithm>
#include <stdexcept>


namespace stack_lib {
    struct empty_access : public std::out_of_range {
        explicit empty_access(const char* message)
        : std::out_of_range(message),
          message(message) {}
    private:
        const char* message;
    };

    template<typename T>
    class Stack {
    public:
        using size_type = size_t;
    private:
        size_type capacity_{start_capacity_};
        size_type size_{0};
        T* data_;
        static constexpr int start_capacity_ = 2;

        void checkAndRealloc() {
            if (size_ == capacity_) {
                capacity_ *= 2;
                auto new_data = new T[capacity_];
                std::copy(data_, data_ + size_, new_data);
                delete[] data_;
                data_ = new_data;
            }
        }

        void checkNonempty() const {
            if (isEmpty()) {
                throw empty_access("Access to empty stack");
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

        [[nodiscard]] bool isEmpty() const {
            return size_ == 0;
        }

        void push(const T& elem) {
            checkAndRealloc();
            data_[size_] = elem;
            size_++;
        }

        void push(T&& elem) {
            checkAndRealloc();
            data_[size_] = std::move(elem);
            size_++;
        }

        void pop() {
            checkNonempty();
            size_--;
        }

        T& top() {
            checkNonempty();
            return data_[size_ - 1];
        }
    };
}