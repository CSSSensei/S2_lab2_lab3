//
// Created by tomin on 18.10.2024.
//

#ifndef S3_LABORATORY_WORK_2_ISORTER_H
#define S3_LABORATORY_WORK_2_ISORTER_H

#include "../Sequence/Sequence.h"

template<typename T>
class ISorter {
public:
    virtual Sequence<T>* Sort(Sequence<T>* seq, int (*cmp)(T, T)) = 0;
    virtual ~ISorter() = default;
};

#endif //S3_LABORATORY_WORK_2_ISORTER_H
