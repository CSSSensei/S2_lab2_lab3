//            _   ___ __         __           __
//           / | / (_) /______  / /__  ____  / /______
//          /  |/ / / //_/ __ \/ / _ \/ __ \/ //_/ __ \
//         / /|  / / ,< / /_/ / /  __/ / / / ,< / /_/ /
//        /_/ |_/_/_/|_|\____/_/\___/_/ /_/_/|_|\____/
//           __ _  ___ ___  / /  (_)   (_)___(_)__
//          /  ' \/ -_) _ \/ _ \/ /   / / __/ (_-<
//         /_/_/_/\__/ .__/_//_/_/   /_/\__/_/___/
//                  /_/


#ifndef S3_LABORATORY_WORK_2_DYNAMICARRAY_H
#define S3_LABORATORY_WORK_2_DYNAMICARRAY_H
#include <iostream>
#include "../pointers/ShrdPtr.h"
#include <memory>

template<class T>
class DynamicArray {
private:
    ShrdPtr<T[]> array;
    int length; // на сколько элементов у пользователя есть доступ
    int size; // на сколько элементов выделена память
public:
    class IndexOutOfRange {};

    // Создание объекта
    DynamicArray(); // создание пустого массива
    DynamicArray(T *items, int count); // создает пустой массив и копирует элементы из исходного
    explicit DynamicArray(int newSize); // создание пустого массива заданной длины
    explicit DynamicArray(int newLength, int needSize); // Создание массива заданной длины со свободным местом needSize - newLenght
    DynamicArray(const DynamicArray<T> &dynArr);

    DynamicArray<T> Concat(const DynamicArray<T> &otherArray) const;

    // Удаление объекта
    ~DynamicArray(); // деструктор
    void Delete_DynamicArray(); // удаление массива

    // Декомпозиция
    T& Get(int index) const; // возвращает элемент по индексу
    int GetSize() const; // Общее число ячеек, под которые выделили память
    int GetLength() const; // Число ячеек, которые может использовать пользователь


    // Операции над параметрами массива
    void Set(int index, T value); // Задает элемент по индексу
    void Resize(int newSize); // Изменяет длину массива доступную пользователю
    DynamicArray<T>& operator=(DynamicArray<T> dynamicArray);
    T& operator[](int index);
    void ChangeLength(int newLength);
};

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
DynamicArray<T>::DynamicArray(const DynamicArray<T>& dynArr)
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



template<typename T>
class ImmutableDynArray {
private:
    T *array;
    size_t length;
    size_t size;

    ImmutableDynArray(size_t new_size, size_t newlength, T *new_arr) : size(new_size), length(newlength),
                                                                       array(new_arr) {}

    T *copy_array(size_t new_size) const {
        T *new_arr = new T[new_size];
        for (size_t i = 0; i < length; i++) {
            new_arr[i] = array[i];
        }
        return new_arr;
    }

public:
    class IndexOutOfRange {
    };

    ImmutableDynArray() : size(10), length(0), array(new T[10]) {}

    ImmutableDynArray(const ImmutableDynArray &other) : size(other.size), length(other.length),
                                                        array(other.copy_array(other.size)) {}

    ImmutableDynArray push_back(const T &elem) const {
        size_t new_size = size;
        if (length == size) {
            new_size *= 2;
        }
        T *new_arr = copy_array(new_size);
        new_arr[length] = elem;
        return ImmutableDynArray(new_size, length + 1, new_arr);
    }

    ImmutableDynArray push_forward(const T &elem) const {
        size_t new_size = size;
        if (length == size) {
            new_size *= 2;
        }
        T *new_arr = copy_array(new_size);
        for (size_t i = length; i > 0; --i) {
            new_arr[i] = new_arr[i - 1];
        }
        new_arr[0] = elem;
        return ImmutableDynArray(new_size, length + 1, new_arr);
    }

    ImmutableDynArray insert(const T &elem, size_t index) const {
        if (index > length) {
            throw IndexOutOfRange();
        }
        size_t new_size = size;
        if (length == size) {
            new_size *= 2;
        }
        T *new_arr = copy_array(new_size);
        for (size_t i = length; i > index; --i) {
            new_arr[i] = new_arr[i - 1];
        }
        new_arr[index] = elem;
        return ImmutableDynArray(new_size, length + 1, new_arr);
    }

    size_t get_length() const {
        return length;
    }

    size_t get_size() const {
        return size;
    }

    T get(size_t index) const {
        if (index >= length || index < 0) {
            throw IndexOutOfRange();
        }
        return array[index];
    }
};


#endif //S3_LABORATORY_WORK_2_DYNAMICARRAY_H
