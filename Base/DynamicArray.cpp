

#include "DynamicArray.h"
#include <memory>
#include <iostream>

template<class T>
void DynamicArray<T>::Resize(int newSize /* подразумевается место для пользователя*/) {

    if (newSize < 0) { // неправильный размер массива
        throw IndexOutOfRange();
    }

    if (newSize == 0) { // удаление массива
        delete[] array;
        array = nullptr;
        size = 0;
        length = 0;
        return;
    }

    if (newSize == size) { return; } // длина не изменится

    if (newSize < length) {
        length = newSize;
    }
    if (newSize * 4 < size) { // укорачивание массива
        size = newSize * 2;
        T* new_array = new T[size];
        for (int i = 0; i < length; i++) {
            new_array[i] = array[i];
        }
        delete[] array;
        array = new_array;
        return;
    }

    if (newSize > 0 && length == 0) { //увеличение размера массива 0 длины
        size = newSize * 2;
        T* new_array = new T[size];
        delete[] array;
        array = new_array;
        return;
    }

    if (newSize > size) { // увеличение длины
        size = newSize * 2;
        T* new_array = new T[size];
        for (int i = 0; i < length; i++) {
            new_array[i] = array[i];
        }
        delete[] array;
        array = new_array;
    }
}


template<class T>
void DynamicArray<T>::ChangeLength(int newLength /* подразумевается место для пользователя*/) {
    if (newLength < 0) { // неправильный размер массива
        throw IndexOutOfRange();
    }
    Resize(newLength);
    length = newLength;
}


template<class T>
DynamicArray<T>::DynamicArray() {
    array = nullptr;
    length = 0;
    size = 0;
}

template<class T>
DynamicArray<T>::DynamicArray(T* items, int count) {
    array = nullptr;
    size = 0;
    length = 0;
    Resize(count);
    for (int i = 0; i < count; i++) {
        array[i] = items[i];
    }
    length = count;
}

template<class T>
DynamicArray<T>::DynamicArray(int newSize) {
    if (newSize < 0) { newSize = 0; }

    array = nullptr;
    size = 0;
    length = 0;
    Resize(newSize);
}

template<class T>
DynamicArray<T>::DynamicArray(int newLength, int needSize) {
    if (newLength < 0 || needSize < newLength) {
        throw IndexOutOfRange();
    }
    std::unique_ptr<T[]> newArray(new T[needSize]);
    array = std::move(newArray);
    length = newLength;
    size = needSize;
}

template<class T>
T &DynamicArray<T>::Get(int index) const {
    if (index < 0 || index >= length) {
        throw IndexOutOfRange();
    }

    return array[index];
}

template<class T>
void DynamicArray<T>::Set(int index, T value) {
    if (index < 0 || index >= length) {
        throw IndexOutOfRange();
    }

    array[index] = value;
}

template<class T>
int DynamicArray<T>::GetSize() const {
    return size;
}

template<class T>
int DynamicArray<T>::GetLength() const {
    return length;
}


template<class T>
void DynamicArray<T>::Delete_DynamicArray() {
    delete[] array;
    array = nullptr;
    size = 0;
    length = 0;
}

template<class T>
DynamicArray<T>::~DynamicArray() {
    delete[] array;
    array = nullptr;
    size = 0;
    length = 0;
}