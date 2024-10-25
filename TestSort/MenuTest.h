//
// Created by tomin on 22.10.2024.
//

#ifndef S3_LABORATORY_WORK_2_MENUTEST_H
#define S3_LABORATORY_WORK_2_MENUTEST_H
#include "../Sequence/LinkedListSequence.h"
#include "../Sort/BubbleSort.h"
#include "../Sort/BatcherSort.h"
#include "../Sort/QuickSort.h"
#include "../Sort/SelectionSort.h"
#include <cassert>


template<typename T>
void TestSorting(ISorter<T>* sorter) {
    // Тестовые данные
    srand(time(0));
    int i = 1000;
    auto arr = new int[i];
    for (int j = 0; j < i; j++) {
        arr[j] = rand();
    }
    LinkedListSequence<T> seq(arr, i);

    // Компаратор для сортировки по возрастанию
    auto cmp = [](T a, T b) { return (a >= b) - (a <= b); };

    // Сортировка
    sorter->Sort(&seq, cmp);

    // Проверка отсортированности
    for (size_t i = 1; i < seq.GetLength(); ++i) {
        assert(seq.Get(i - 1) <= seq.Get(i) && "Sequence is not sorted!");
    }
    delete[] arr;
}

void test_sort_main() {
    // Параметризованные тесты для различных сортировок
    {
        BatcherSort<int> batcherSorter;
        TestSorting(&batcherSorter);
        std::cout << "BatcherSort passed.\n";
    }

    {
        BubbleSorter<int> bubbleSorter;
        TestSorting(&bubbleSorter);
        std::cout << "BubbleSorter passed.\n";
    }

    {
        SelectionSorter<int> selectionSorter;
        TestSorting(&selectionSorter);
        std::cout << "SelectionSorter passed.\n";
    }

    {
        QuickSort<int> quickSorter;
        TestSorting(&quickSorter);
        std::cout << "QuickSort passed.\n";
    }
}

#endif //S3_LABORATORY_WORK_2_MENUTEST_H
