//
// Created by tomin on 16.10.2024.
//

#ifndef S3_LABORATORY_WORK_2_UNQPTR_H
#define S3_LABORATORY_WORK_2_UNQPTR_H

template<typename T>
class UnqPtr {
private:
    T* ptr;

public:
    // Constructor
    explicit UnqPtr(T* p = nullptr) {
        ptr = p;
    }

    // Destructor
    ~UnqPtr() {
        delete ptr;
    }

    // Prohibit copying
    UnqPtr(const UnqPtr&) = delete;
    UnqPtr& operator=(const UnqPtr&) = delete;

    // Allow movement
    UnqPtr(UnqPtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    UnqPtr& operator=(UnqPtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    // Get raw pointer
    T* get() const {
        return ptr;
    }

    // Release the pointer
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }

    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    explicit operator bool() const {
        return ptr != nullptr;
    }
};

#endif //S3_LABORATORY_WORK_2_UNQPTR_H
