#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>

template<class T>
class LinkedList {
private:
    struct element {
        T value;
        struct element *next_element;
    };
    int len = 0;
    struct element *head_element = nullptr;
    struct element *end_element = nullptr;

public:
    class IndexOutOfRange {
    };

    //Создание объекта
    LinkedList(T *items, int count); //Копирует элементы из переданного списка
    LinkedList(); //Создает пустой список
    LinkedList(const LinkedList<T> &list); //Копирующий конструктор

    //удаление объекта
    ~LinkedList();//деструктор
    void Delete_LinkedList(); //удаление списка
    void remove(int left_border, int right_border);

    //декомпозиция
    T GetFirst();//Возвращает первый элемент
    T GetLast();//Возвращает последний элемент
    T &Get(int index);//Возвращает элемент по индексу
    LinkedList<T> GetSubList(int startIndex, int endIndex);//Возваращет список элементов в исходных пределах
    int GetLength();//Возвращает длину

    //Операции
    void Append(T item); //Добавление элемента в конец списка
    void Prepend(T item); //Добавление элемента в начало списка
    void InsertAt(T item, int index); //Вставка элемента в заданную позицию
    LinkedList<T> Concat(LinkedList<T> *list); //Сцепляет два списка
    //Перегрузка операторов
    LinkedList<T> &operator=(LinkedList<T> linkedlist) {
        Delete_LinkedList();
        struct element *cell = linkedlist.head_element;
        for (int i = 0; i < linkedlist.len; i++, cell = cell->next_element) {
            Append(cell->value);
        }
        return *this;
    }

};


template<class T>
class ImmutableLinkedList {
private:
    struct element {
        T value;
        struct element *next_element;
    };
    int len = 0;
    struct element *head_element = nullptr;
    struct element *end_element = nullptr;

public:
    class IndexOutOfRange {
    };

    // Создание объекта
    ImmutableLinkedList(T *items, int count); // Копирует элементы из переданного списка
    ImmutableLinkedList(); // Создает пустой список
    ImmutableLinkedList(const ImmutableLinkedList<T> &list); // Копирующий конструктор

    // Удаление объекта
    ~ImmutableLinkedList(); // Деструктор
    void Delete_LinkedList(); // Удаление списка
    ImmutableLinkedList<T> remove(int left_border, int right_border) const;

    // Декомпозиция
    T GetFirst() const; // Возвращает первый элемент
    T GetLast() const; // Возвращает последний элемент
    T &Get(int index) const; // Возвращает элемент по индексу
    ImmutableLinkedList<T>
    GetSubList(int startIndex, int endIndex) const; // Возвращает список элементов в заданном диапазоне
    int GetLength() const; // Возвращает длину

    // Операции
    ImmutableLinkedList<T> Append(T item) const; // Добавление элемента в конец списка
    ImmutableLinkedList<T> Prepend(T item) const; // Добавление элемента в начало списка

};


#endif