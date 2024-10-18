

#include "DynamicArray.h"
#include <memory>
#include <iostream>

template<class T>
void DynamicArray<T>::Resize(int newSize /* подразумевается место для пользователя*/) {

    if (newSize < 0) { // неправильный размер массива
        throw IndexOutOfRange();
    }

    if (newSize == 0) { // удаление массива
        array = ShrdPtr<T[]>();
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
        ShrdPtr<T[]> new_array(new T[size]);
        for (int i = 0; i < length; i++) {
            new_array[i] = array[i];
        }
        array = std::move(new_array);
        return;
    }

    if (newSize > 0 && length == 0) { //увеличение размера массива 0 длины
        size = newSize * 2;
        array = ShrdPtr<T[]>(new T[size]);
        return;
    }

    if (newSize > size) { // увеличение длины
        size = newSize * 2;
        ShrdPtr<T[]> new_array(new T[size]);
        for (int i = 0; i < length; i++) {
            new_array[i] = array[i];
        }
        array = std::move(new_array);
        return;
    }
//    ShrdPtr<T[]> new_array(new T[size]);
//    for (int i = 0; i < length; i++) {
//        new_array[i] = array[i];
//    }
//    array = std::move(new_array);
}


template<class T>
void DynamicArray<T>::ChangeLength(int newLength /* подразумевается место для пользователя*/) {
    if (newLength < 0) { // неправильный размер массива
        throw IndexOutOfRange();
    }
    if (!(newLength < size && newLength * 4 > size)) Resize(newLength);
    length = newLength;
}


template<class T>
DynamicArray<T>::DynamicArray() : array(nullptr), length(0), size(0) {}

template<class T>
DynamicArray<T>::DynamicArray(T* items, int count) : length(0), size(0) {
    Resize(count);
    ShrdPtr<T[]> temp(new T[count]);
    for (int i = 0; i < count; i++) {
        temp[i] = items[i];
    }
    length = count;
    array = std::move(temp);
}

template<class T>
DynamicArray<T>::DynamicArray(int newSize) : length(0), size(0) {
    array = std::move(ShrdPtr<T[]>(new T[newSize]));
    Resize(newSize);
}

template<class T>
DynamicArray<T>::DynamicArray(int newLength, int needSize) : length(newLength), size(needSize) {
    if (newLength < 0 || needSize < newLength) {
        throw IndexOutOfRange();
    }
    array = ShrdPtr<T[]>(new T[needSize]);
}

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray& dynArr)
        : length(dynArr.length),
          size(dynArr.size),
          array(ShrdPtr<T[]>(new T[dynArr.size])) {
    for (int i = 0; i < length; i++) {
        array[i] = dynArr.array[i];
    }
}

template<class T>
DynamicArray<T> DynamicArray<T>::Concat(const DynamicArray<T>& otherArray) const {
    DynamicArray<T> result;
    result.Resize(length + otherArray.length);

    for (int i = 0; i < length; i++) {
        result.array[i] = array[i];
    }

    for (int i = 0; i < otherArray.length; i++) {
        result.array[length + i] = otherArray.array[i];
    }

    return result;
}

template<class T>
T &DynamicArray<T>::Get(int index) const {
    if (index < 0 || index >= length) {
        throw IndexOutOfRange();
    }

    return const_cast<T&>(array[index]);
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
void DynamicArray<T>::Delete_DynamicArray() {}

template<class T>
DynamicArray<T>::~DynamicArray() {
    Delete_DynamicArray();
}

template<class T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray<T> dynamicArray) {
    std::swap(array, dynamicArray.array);
    size = dynamicArray.size;
    length = dynamicArray.length;
    return *this;
}

template<class T>
T& DynamicArray<T>::operator[](int index) {
    if (index < 0 || index >= length) {
        throw IndexOutOfRange();
    }
    return array[index];
}
