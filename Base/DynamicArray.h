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

template<class T>
class DynamicArray {
private:
    T *array;
    int length; //на сколько элементов у пользователя есть доступ
    int size; //на сколько элементов выделена память
public:
    class IndexOutOfRange {
    };

    // Создание объект
    DynamicArray(); //создание пустого массива
    DynamicArray(T *items, int count); //создает пустой массив и копирует элементы из исходного
    explicit DynamicArray(int newSize); //создание пустого массива заданной длины
    explicit DynamicArray(int newLength,
                          int needSize);//Создание массива заданной длины со свободным местом needSize - newLenght
    DynamicArray(const DynamicArray &dynArr) {
        size = dynArr.size;
        length = dynArr.length;

        array = new T[size];
        for (int i = 0; i < length; i++) {
            array[i] = dynArr.array[i];
        }
    }

    DynamicArray<T> Concat(const DynamicArray<T> &otherArray) {
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

    //Удаление объекта
    ~DynamicArray(); //деструктор
    void Delete_DynamicArray(); //удаление массива

    //Декомпозиция
    T &Get(int index); //возвращает элемент по индексу
    int GetSize();//Общее число ячеек, под которые выделили память
    int GetLength();//Число ячеек, которые может использовать пользователь


    //Операции над параметрами массива
    void Set(int index, T value); //Задает элемент по индексу
    void Resize(int newSize); //Изменяет длину массива доступную пользователю
    DynamicArray<T> &operator=(DynamicArray<T> dynamicArray) {
        std::swap(array, dynamicArray.array);
        size = dynamicArray.size;
        length = dynamicArray.length;
        return *this;
    }

    T &operator[](int index) {
        if (index < 0 || index >= length) {
            throw IndexOutOfRange();
        }

        return array[index];
    }

    void ChangeLength(int newLength);
};


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

    void print() const {
        for (size_t i = 0; i < length; i++) {
            std::cout << array[i] << " ";
        }
        std::cout << "\n";
    }
};


#endif //S3_LABORATORY_WORK_2_DYNAMICARRAY_H
