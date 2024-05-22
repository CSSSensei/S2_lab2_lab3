#include "LinkedList.h"

template<class T>
void LinkedList<T>::Append(T item) {
    auto *new_cell = new struct element;
    new_cell->value = item;
    new_cell->next_element = nullptr;

    if (head_element == nullptr) { //случай, когда список пустой
        head_element = new_cell;
        end_element = new_cell;
        len = 1;
        return;
    }

    end_element->next_element = new_cell;
    end_element = new_cell;
    len++;
}

template<class T>
LinkedList<T>::LinkedList() {
    len = 0;
    head_element = nullptr;
    end_element = nullptr;
}

template<class T>
LinkedList<T>::LinkedList(T *items, int count) {
    len = 0;
    head_element = nullptr;
    end_element = nullptr;

    for (int i = 0; i < count; i++) {
        Append(items[i]);
    }
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &list) {
    len = 0;
    head_element = nullptr;
    end_element = nullptr;
    struct element *cell = list.head_element;
    for (int i = 0; i < list.len; i++, cell = cell->next_element) {
        Append(cell->value);
    }
}

template<class T>
T LinkedList<T>::GetFirst() {
    if (head_element == nullptr) { throw IndexOutOfRange(); }

    return head_element->value;
}

template<class T>
T LinkedList<T>::GetLast() {
    if (end_element == nullptr) { throw IndexOutOfRange(); }

    return end_element->value;
}

template<class T>
T &LinkedList<T>::Get(int index) {
    if (index < 0 || index >= len) { throw IndexOutOfRange(); }

    struct element *cell = head_element;
    for (int i = 0; i < index; i++, cell = cell->next_element);

    return cell->value;
}

template<class T>
LinkedList<T> LinkedList<T>::GetSubList(int startIndex, int endIndex) {
    if (startIndex >= len || endIndex >= len || startIndex < 0 || endIndex < 0) {
        throw IndexOutOfRange();
    }

    LinkedList<T> new_list = LinkedList<T>();
    auto *cell = new struct element;
    cell = head_element;
    for (int i = 0; i < startIndex; i++, cell = cell->next_element);
    for (int i = startIndex; i <= endIndex; i++, cell = cell->next_element) {
        new_list.Append(cell->value);
    }

    return new_list;
}

template<class T>
int LinkedList<T>::GetLength() {
    return len;
}

template<class T>
void LinkedList<T>::Prepend(T item) {
    auto *new_cell = new struct element;
    new_cell->value = item;

    if (head_element == nullptr) {
        end_element = new_cell;
    }

    new_cell->next_element = head_element;
    head_element = new_cell;
    len++;
}

template<class T>
void LinkedList<T>::InsertAt(T item, int index) {
    if (index > len || index < 0) { throw IndexOutOfRange(); }

    if (index == 0) {
        Prepend(item);
        return;
    }
    else if (index == len) {
        Append(item);
        return;
    }
    else {
        auto *new_cell = new struct element;
        new_cell->value = item;
        struct element *previous_cell = head_element;
        for (int i = 0; i < index - 1; i++, previous_cell = previous_cell->next_element);
        new_cell->next_element = previous_cell->next_element;
        previous_cell->next_element = new_cell;
        len++;
    }
}

template<class T>
LinkedList<T> LinkedList<T>::Concat(LinkedList<T> *list) {
    LinkedList<T> new_list = LinkedList<T>();

    struct element *new_cell = head_element;
    for (int i = 0; i < len; i++, new_cell = new_cell->next_element) {
        new_list.Append(new_cell->value);
    }

    new_cell = list->head_element;
    for (int i = 0; i < list->len; i++, new_cell = new_cell->next_element) {
        new_list.Append(new_cell->value);
    }

    return new_list;
}

template<class T>
LinkedList<T>::~LinkedList() {
    Delete_LinkedList();
}

template<class T>
void LinkedList<T>::Delete_LinkedList() {
    struct element *this_cell;
    while (head_element != nullptr) {
        this_cell = head_element;
        head_element = head_element->next_element;
        delete this_cell;
    }
    end_element = nullptr;
    len = 0;
}

template<class T>
void LinkedList<T>::remove(int left_border, int right_border) {
    if (left_border < 0 || right_border >= len || left_border > right_border) {
        throw IndexOutOfRange();
    }

    struct element *prev_cell = nullptr;
    struct element *current_cell = head_element;

    // Переместимся к левой границе
    for (int i = 0; i < left_border; ++i) {
        prev_cell = current_cell;
        current_cell = current_cell->next_element;
    }

    // Удалим элементы в границах
    struct element *next_cell;
    for (int i = left_border; i <= right_border; ++i) {
        next_cell = current_cell->next_element;
        delete current_cell;
        current_cell = next_cell;
    }

    if (left_border == 0) {
        head_element = current_cell;
    } else {
        prev_cell->next_element = current_cell;
    }

    if (right_border == len - 1) {
        end_element = prev_cell;
    }

    len -= (right_border - left_border + 1);
}


//ImmutableLinkedList
template<class T>
ImmutableLinkedList<T>::ImmutableLinkedList(T *items, int count) {
    len = 0;
    head_element = nullptr;
    end_element = nullptr;

    for (int i = 0; i < count; ++i) {
        *this = this->Append(items[i]);
    }
}

// Конструктор для создания пустого списка
template<class T>
ImmutableLinkedList<T>::ImmutableLinkedList() {
    len = 0;
    head_element = nullptr;
    end_element = nullptr;
}

// Конструктор копирования
template<class T>
ImmutableLinkedList<T>::ImmutableLinkedList(const ImmutableLinkedList<T> &list) {
    len = list.len;
    if (len == 0) {
        head_element = nullptr;
        end_element = nullptr;
        return;
    }

    struct element *curr = list.head_element;
    struct element *new_head = new struct element;
    struct element *curr_new = new_head;

    while (curr != nullptr) {
        curr_new->value = curr->value;
        if (curr->next_element != nullptr) {
            curr_new->next_element = new struct element;
            curr_new = curr_new->next_element;
        } else {
            curr_new->next_element = nullptr;
        }
        curr = curr->next_element;
    }

    head_element = new_head;
    end_element = curr_new;
}

// Деструктор
template<class T>
ImmutableLinkedList<T>::~ImmutableLinkedList() {
    Delete_LinkedList();
}

// Метод удаления списка
template<class T>
void ImmutableLinkedList<T>::Delete_LinkedList() {
    struct element *curr = head_element;
    while (curr != nullptr) {
        struct element *next = curr->next_element;
        delete curr;
        curr = next;
    }
    len = 0;
    head_element = nullptr;
    end_element = nullptr;
}

// Метод получения первого элемента
template<class T>
T ImmutableLinkedList<T>::GetFirst() const {
    if (len == 0) {
        throw IndexOutOfRange();
    }
    return head_element->value;
}

// Метод получения последнего элемента
template<class T>
T ImmutableLinkedList<T>::GetLast() const {
    if (len == 0) {
        throw IndexOutOfRange();
    }
    return end_element->value;
}

// Метод получения элемента по индексу
template<class T>
T &ImmutableLinkedList<T>::Get(int index) const {
    if (index < 0 || index >= len) {
        throw IndexOutOfRange();
    }

    struct element *curr = head_element;
    for (int i = 0; i < index; ++i) {
        curr = curr->next_element;
    }
    return curr->value;
}

// Метод получения подсписка
template<class T>
ImmutableLinkedList<T> ImmutableLinkedList<T>::GetSubList(int startIndex, int endIndex) const {
    if (startIndex < 0 || endIndex >= len || startIndex > endIndex) {
        throw IndexOutOfRange();
    }

    ImmutableLinkedList<T> sublist;
    struct element *curr = head_element;
    for (int i = 0; i < startIndex; ++i) {
        curr = curr->next_element;
    }

    for (int i = startIndex; i <= endIndex; ++i) {
        sublist = sublist.Append(curr->value);
        curr = curr->next_element;
    }

    return sublist;
}

template<class T>
int ImmutableLinkedList<T>::GetLength() const {
    return len;
}

template<class T>
ImmutableLinkedList<T> ImmutableLinkedList<T>::remove(int left_border, int right_border) const {
    if (left_border < 0 || right_border >= len || left_border > right_border) {
        throw IndexOutOfRange();
    }

    ImmutableLinkedList<T> new_list;
    struct element *prev_cell = nullptr;
    struct element *current_cell = head_element;

    for (int i = 0; i < left_border; ++i) {
        ImmutableLinkedList<T> appended_list = new_list.Append(current_cell->value);
        new_list = appended_list;
        current_cell = current_cell->next_element;
    }

    for (int i = left_border; i <= right_border; ++i) {
        current_cell = current_cell->next_element;
    }

    while (current_cell != nullptr) {
        ImmutableLinkedList<T> appended_list = new_list.Append(current_cell->value);
        new_list = appended_list;
        current_cell = current_cell->next_element;
    }

    return new_list;
}


template<class T>
ImmutableLinkedList<T> ImmutableLinkedList<T>::Append(T item) const {
    struct element *new_end = new struct element;
    new_end->value = item;
    new_end->next_element = nullptr;

    ImmutableLinkedList<T> new_list = *this; // Создаем копию текущего списка

    if (new_list.len == 0) {
        new_list.head_element = new_end;
        new_list.end_element = new_end;
    } else {
        new_list.end_element->next_element = new_end;
        new_list.end_element = new_end;
    }

    new_list.len++;
    return new_list;
}

template<class T>
ImmutableLinkedList<T> ImmutableLinkedList<T>::Prepend(T item) const {
    struct element *new_head = new struct element;
    new_head->value = item;
    new_head->next_element = nullptr;

    ImmutableLinkedList<T> new_list = *this; // Создаем копию текущего списка

    if (new_list.len == 0) {
        new_list.head_element = new_head;
        new_list.end_element = new_head;
    } else {
        new_head->next_element = new_list.head_element;
        new_list.head_element = new_head;
    }

    new_list.len++;
    return new_list;
}