#ifndef LinkedListSequence_h
#define LinkedListSequence_h

#include "Sequence.h"
#include "../Base/LinkedList.cpp"

template <class T>
class LinkedListSequence : public  Sequence<T>{
private:
    LinkedList<T> listSequence;
public:
    class IndexOutOfRange : LinkedList<T>::IndexOutOfRange{};

    //Создание объекта
    LinkedListSequence (T* items, int count){
        listSequence = LinkedList<T>(items, count);
    }//Копирует элемнеты из переданного массива
    LinkedListSequence (){
        listSequence = LinkedList<T>();
    }//Создает пустую последовательность
    explicit LinkedListSequence (const LinkedList <T> &list){
        listSequence = LinkedList<T>(list);
    }//Копирующий конструктор

    //Удаление объекта
    ~LinkedListSequence(){
        listSequence.Delete_LinkedList();
    }//деструктор
    void Delete_LinkedListSequene(){
        listSequence.Delete_LinkedList();
    }//функция удаление последовательности

    //Декомпозиция
    T GetFirst() const {
        if (listSequence.GetLength() == 0) {
            throw IndexOutOfRange();
        }
        return listSequence.GetFirst();
    }//Возвращает первый элемент
    T GetLast() const {
        if (listSequence.GetLength() == 0) {
            throw IndexOutOfRange();
        }
        return listSequence.GetLast();
    }//Возвращает последний элемент

    T& Get(int index) const {
        return listSequence.Get(index);
    }//Возвращает элемент по индексу
    LinkedListSequence<T>* GetSubsequence(int startIndex, int endIndex) const {
        //auto *new_LinkedList = new LinkedList<T>;
        auto new_LinkedList = listSequence.GetSubList(startIndex, endIndex);
        auto *new_LinkedListSequence = new LinkedListSequence<T>(new_LinkedList);
        return new_LinkedListSequence;
    }//Получить список из всех элементов, начиная с startIndex и заканчивая endIndex
    int GetLength() const {
        return listSequence.GetLength();
    }

    //Операции
    void Append(T item){
        listSequence.Append(item);
    }//Добавляет элемент в конец списка
    void Prepend(T item){
        listSequence.Prepend(item);
    }//Добавляет элемент в начало списка
    void InsertAt(T item, int index){
        listSequence.InsertAt(item, index);
    }//Вставляет элемент в заданную позицию
    void Set(int index, T item){
        listSequence.Set(index, item);
    }
    LinkedListSequence<T>* Concat(Sequence<T> *list) {
        auto *new_LinkedList = new LinkedListSequence<T> (*this);
        for (int i = 0; i < list->GetLength(); i++){
            new_LinkedList->Append(list->Get(i));
        }

        return new_LinkedList;
    }//Сцепляет два списка

    //Перегрузка операторов
    LinkedListSequence<T>& operator = (LinkedListSequence<T> listSequence) {
        listSequence = listSequence.listSequence;
        return *this;
    }

    T Pop() {
        if (listSequence.GetLength() == 0) {
            throw IndexOutOfRange();
        }
        T lastElement = listSequence.GetLast();
        listSequence.remove(listSequence.GetLength() - 1, listSequence.GetLength() - 1); // Удаление последнего элемента
        return lastElement;
    }
    void Remove(int left_border, int right_border) {
        if (listSequence.GetLength() == 0) {
            throw IndexOutOfRange();
        }
        listSequence.remove(left_border, right_border);
    }

};

#endif