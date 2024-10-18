

#ifndef S3_LABORATORY_WORK_2_SHRDPTR_H
#define S3_LABORATORY_WORK_2_SHRDPTR_H
//
// Created by tomin on 29.09.2024.
//

#include <iostream>
#include "Counter.h"

template<typename T>
class ShrdPtr {
private:
    Counter* counter;
    T* ptr;

public:
    // Constructor
    explicit ShrdPtr(T* p = nullptr) : ptr(p), counter(new Counter()) {
        (*counter)++;
    }

    // Copy constructor
    ShrdPtr(const ShrdPtr<T>& sp) : ptr(sp.ptr), counter(sp.counter) {
        (*counter)++;
    }

    // Move constructor
    ShrdPtr(ShrdPtr<T>&& sp) noexcept : ptr(sp.ptr), counter(sp.counter) {
        sp.ptr = nullptr;
        sp.counter = nullptr;
    }

    // reference count getter
    unsigned int use_count() const {
        return counter ? counter->get() : 0;
    }

    // shared pointer getter
    T* get() const {
        return ptr;
    }

    T& operator*() {
        return *ptr;
    }

    T* operator->() {
        return ptr;
    }

    // Overloading the = operator
    ShrdPtr& operator=(const ShrdPtr& sp) {
        if (this != &sp) {
            --(*counter);
            if (counter && (counter->get() == 0)) {
                delete counter;
                delete ptr;
            }
            ptr = sp.ptr;
            counter = sp.counter;
            if (counter) {
                (*counter)++;
            }
        }
        return *this;
    }

    // Destructor
    ~ShrdPtr() {
        if (counter) {
            --(*counter);
            if (counter->get() == 0) {
                delete counter;
                delete ptr;
            }
        }
    }

    explicit operator bool() const {
        return ptr != nullptr;
    }

    friend std::ostream& operator<<(std::ostream& os, const ShrdPtr<T>& sp) {
        os << "Address pointed: " << sp.get() << std::endl;
        os << "Reference count: " << sp.use_count() << std::endl;
        return os;
    }
};

// Шаблон для обработки массивов
template<typename T>
class ShrdPtr<T[]> {
private:
    Counter* counter;
    T* ptr;

public:
    explicit ShrdPtr(T* p = nullptr) : ptr(p), counter(new Counter()) {
        (*counter)++;
    }

    // Copy constructor
    ShrdPtr(const ShrdPtr& sp) : ptr(sp.ptr), counter(sp.counter) {
        std::cout << "COPY\n";
        (*counter)++;
    }

    // Move constructor
    ShrdPtr(ShrdPtr&& sp) noexcept : ptr(sp.ptr), counter(sp.counter) {
        sp.ptr = nullptr;
        sp.counter = nullptr;
    }

    unsigned int use_count() const {
        return counter ? counter->get() : 0;
    }

    T* get() const {
        return ptr;
    }

    T& operator[](int i) {
        return ptr[i];
    }

    T* operator->() {
        return ptr;
    }

    ShrdPtr& operator=(const ShrdPtr& sp) {
        if (this != &sp) {
            if (counter) {
                --(*counter);
                if (counter->get() == 0) {
                    delete counter;
                    delete[] ptr;
                }
            }
            ptr = sp.ptr;
            counter = sp.counter;
            if (counter) {
                (*counter)++;
            }
        }
        return *this;
    }

    const T& operator[](int i) const {
        return ptr[i];
    }

    ~ShrdPtr() {
        if (counter) {
            --(*counter);
            if (counter->get() == 0) {
                delete counter;
                delete[] ptr;
            }
        }
    }

    explicit operator bool() const {
        return ptr != nullptr;
    }
};


#endif //S3_LABORATORY_WORK_2_SHRDPTR_H
