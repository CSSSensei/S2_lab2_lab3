

#include "DynamicArray.h"
#include <memory>
#include <iostream>

template<class T>
void DynamicArray<T>::Resize(int newLenght /* подразумевается место для пользователя*/) {
    int ConstMemory = int(0.25 * newLenght); //будем увеличивать память пачками

    if (newLenght < 0) {
        throw IndexOutOfRange();
    }// неправильный размер массива

    if (newLenght == 0) {
        delete[] array;
        array = nullptr;
        size = 0;
        length = 0;
        return;
    }// удаление массива

    if (newLenght == length) { return; }// длина не изменится

    if (newLenght < length) {
        length = newLenght;
        return;
    }// укорачивание массива

    if (newLenght > 0 && length == 0) {
        T *new_array = new T[newLenght + ConstMemory];
        delete[] array;
        length = newLenght;
        size = newLenght + ConstMemory;
        array = new_array;
        return;
    }//увеличение размера массива 0 длины

    if (newLenght > length) {
        if (newLenght >= size) {
            T *new_array = new T[newLenght + ConstMemory];
            for (int i = 0; i < length; i++) {
                new_array[i] = array[i];
            }
            delete[] array;
            length = newLenght;
            size = newLenght + ConstMemory;
            array = new_array;
        } else {
            length = newLenght;
        }
        return;
    }// увеличение длины
}


template<class T>
DynamicArray<T>::DynamicArray() {
    array = nullptr;
    length = 0;
    size = 0;
}

template<class T>
DynamicArray<T>::DynamicArray(T *items, int count) {
    array = nullptr;
    size = 0;
    length = 0;
    Resize(count);
    for (int i = 0; i < count; i++) {
        array[i] = items[i];
    }
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
T &DynamicArray<T>::Get(int index) {
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
int DynamicArray<T>::GetSize() {
    return size;
}

template<class T>
int DynamicArray<T>::GetLength() {
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