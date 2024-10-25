//
// Created by tomin on 22.10.2024.
//

#ifndef S3_LABORATORY_WORK_2_SELECTIONSORT_H
#define S3_LABORATORY_WORK_2_SELECTIONSORT_H
#include "ISorter.h"

template<typename T>
class SelectionSorter : public ISorter<T> {
public:
    Sequence<T>* Sort(Sequence<T>* seq, int (*cmp)(T, T)) override {
        int n = seq->GetLength();
        for (int i = 0; i < n - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < n; j++) {
                if (cmp(seq->Get(j), seq->Get(minIndex)) < 0) {
                    minIndex = j;
                }
            }
            if (minIndex != i) {
                T temp = seq->Get(i);
                seq->Set(i, seq->Get(minIndex));
                seq->Set(minIndex, temp);
            }
        }
        return seq;
    }
};

#endif //S3_LABORATORY_WORK_2_SELECTIONSORT_H
