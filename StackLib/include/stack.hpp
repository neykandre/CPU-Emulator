#pragma once

#include <algorithm>

#define START_CAPACITY 1

namespace StackLib {
    template<class T>
    class Stack {
    private:
        size_t _capacity{START_CAPACITY};
        size_t _size{0};
        T* data;

        void checkAndRealloc() {
            if (_size == _capacity) {
                _capacity *= 2;
                T* newData = new T[_capacity];
                std::copy(data, data + _size, newData);
                delete[] data;
                data = newData;
            }
        }

    public:
        Stack() {
            data = new T[_capacity];
        }

        Stack(const Stack& other)
                : _capacity(other._capacity),
                  _size(other._size) {
            data = new T[_capacity];
            std::copy(other.data, other.data + other._size, data);
        }

        Stack(Stack&& other) noexcept
                : _capacity(other._capacity),
                  _size(other._size),
                  data(std::exchange(other.data, nullptr)) {}

        Stack& operator=(Stack other) noexcept {
            std::swap(_capacity, other._capacity);
            std::swap(_size, other._size);
            std::swap(data, other.data);
            return *this;
        }

        ~Stack() noexcept {
            delete[] data;
            data = nullptr;
            _capacity = 0;
            _size = 0;
        }

        size_t size() const noexcept {
            return _size;
        }

        bool empty() const {
            return _size == 0;
        }

        template<class U>
        void push(U&& elem) {
            checkAndRealloc();
            data[_size] = elem;
            _size++;
        }

        void pop() {
            if (!empty()) {
                _size--;
            }
        }

        T peek() const {
            if (!empty()) {
                return data[_size - 1];
            } else {
                return {};
            }
        }

        T* begin() const {
            return data;
        }

        T* end() const {
            return data + _size;
        }
    };
}