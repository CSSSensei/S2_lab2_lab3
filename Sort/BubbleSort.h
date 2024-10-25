//
// Created by tomin on 18.10.2024.
//

#ifndef S3_LABORATORY_WORK_2_BUBBLESORT_H
#define S3_LABORATORY_WORK_2_BUBBLESORT_H

#include "ISorter.h"

template<typename T>
class BubbleSorter : public ISorter<T> {
public:
    Sequence<T>* Sort(Sequence<T>* seq, int (*cmp)(T, T)) override {
        int length = seq->GetLength();
        for (int i = 0; i < length - 1; ++i) {
            for (int j = 0; j < length - i - 1; ++j) {
                if (cmp(seq->Get(j), seq->Get(j + 1)) > 0) {
                    T temp = seq->Get(j);
                    seq->Set(j, seq->Get(j + 1));
                    seq->Set(j + 1, temp);
                }
            }
        }
        return seq;
    }
};

#endif //S3_LABORATORY_WORK_2_BUBBLESORT_H
