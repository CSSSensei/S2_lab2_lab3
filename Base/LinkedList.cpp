#include "LinkedList.h"

template<class T>
void LinkedList<T>::Append(T item) {
    UnqPtr<element> new_cell(new element);
    new_cell->value = item;
    new_cell->next_element.reset(nullptr);

    if (!head_element) { // Если список пустой
        head_element.reset(new_cell.release());
        end_element = head_element.get();
        len = 1;
        return;
    }

    end_element->next_element.reset(new_cell.release());
    end_element = end_element->next_element.get();
    len++;
}

template<class T>
LinkedList<T>::LinkedList() {
    len = 0;
    head_element.reset();
    end_element = nullptr;
}

template<class T>
LinkedList<T>::LinkedList(T *items, int count) {
    len = 0;
    head_element.reset();
    end_element = nullptr;

    for (int i = 0; i < count; i++) {
        Append(items[i]);
    }
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &list) {
    len = 0;
    head_element.reset();
    end_element = nullptr;
    for (element* cell = list.head_element.get(); cell; cell = cell->next_element.get()) {
        Append(cell->value);
    }
}

template<class T>
T LinkedList<T>::GetFirst() const {
    if (!head_element) throw IndexOutOfRange();
    return head_element->value;
}

template<class T>
T LinkedList<T>::GetLast() const {
    if (!end_element) throw IndexOutOfRange();
    return end_element->value;
}

template<class T>
T &LinkedList<T>::Get(int index) const {
    if (index < 0 || index >= len) throw IndexOutOfRange();

    element *cell = head_element.get();
    for (int i = 0; i < index; i++, cell = cell->next_element.get());
    return cell->value;
}

template<class T>
LinkedList<T> LinkedList<T>::GetSubList(int startIndex, int endIndex) const {
    if (startIndex >= len || endIndex >= len || startIndex < 0 || endIndex < 0) {
        throw IndexOutOfRange();
    }

    LinkedList<T> new_list;
    auto cell = head_element.get();
    for (int i = 0; i < startIndex; i++, cell = cell->next_element.get());
    for (int i = startIndex; i <= endIndex; i++, cell = cell->next_element.get()) {
        new_list.Append(cell->value);
    }

    return new_list;
}

template<class T>
int LinkedList<T>::GetLength() const {
    return len;
}

template<class T>
void LinkedList<T>::Prepend(T item) {
    UnqPtr<element> new_cell(new element);
    new_cell->value = item;
    new_cell->next_element = std::move(head_element);

    head_element = std::move(new_cell);
    if (!end_element) {
        end_element = head_element.get();
    }
    len++;
}

template<class T>
void LinkedList<T>::InsertAt(T item, int index) {
    if (index > len || index < 0) throw IndexOutOfRange();

    if (index == 0) {
        Prepend(item);
        return;
    } else if (index == len) {
        Append(item);
        return;
    } else {
        UnqPtr<element> new_cell(new element);
        new_cell->value = item;
        element *previous_cell = head_element.get();
        for (int i = 0; i < index - 1; i++, previous_cell = previous_cell->next_element.get());
        new_cell->next_element = std::move(previous_cell->next_element);
        previous_cell->next_element.reset(new_cell.release());
        len++;
    }
}

template<class T>
void LinkedList<T>::Set(int index, T item) {
    if (index >= len || index < 0) throw IndexOutOfRange();

    element *cell = head_element.get();
    for (int i = 0; i < index; i++, cell = cell->next_element.get());

    cell->value = item;
}

template<class T>
LinkedList<T> LinkedList<T>::Concat(LinkedList<T> *list) {
    LinkedList<T> new_list;
    element* new_cell = head_element.get();
    while (new_cell) {
        new_list.Append(new_cell->value);
        new_cell = new_cell->next_element.get();
    }

    new_cell = list->head_element.get();
    while (new_cell) {
        new_list.Append(new_cell->value);
        new_cell = new_cell->next_element.get();
    }

    return new_list;
}

template<class T>
LinkedList<T>::~LinkedList() {
    Delete_LinkedList();
}

template<class T>
void LinkedList<T>::Delete_LinkedList() {
    if (!head_element) {
        return;
    }
    UnqPtr<element> current = std::move(head_element);
    while (current) {
        UnqPtr<element> next = std::move(current->next_element);
        current.reset();
        current = std::move(next);
    }
    end_element = nullptr;
    len = 0;
}

template<class T>
void LinkedList<T>::remove(int left_border, int right_border) {
    if (left_border < 0 || right_border >= len || left_border > right_border) {
        throw IndexOutOfRange();
    }

    UnqPtr<element>* current = &head_element;
    int index = 0;

    while (*current) {
        if (index >= left_border && index <= right_border) {
            UnqPtr<element> temp = std::move(*current);
            *current = std::move(temp->next_element);
            len--;

            if (temp.get() == end_element) {
                end_element = nullptr;
            }
            index++;
            continue;
        }
        else if (index > right_border) {
            break;
        }
        current = &(*current)->next_element;
        index++;
    }
    if (len == 0) {
        head_element.reset();
        end_element = nullptr;
    } else if (left_border == 0) {
        head_element = std::move(*current);
    }

    if (index >= len) {
        UnqPtr<element>* iter = &head_element;
        while (*iter) {
            end_element = (*iter).get();
            iter = &(*iter)->next_element;
        }
    }
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