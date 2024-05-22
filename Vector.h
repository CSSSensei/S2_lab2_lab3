#include "Sequence/ArraySequence.h"
#include <cmath>
#include <iostream>
#include <complex>

#ifndef LABORATORY_WORK_2_VECTOR_H
#define LABORATORY_WORK_2_VECTOR_H

template<class T>
class Vector {
private:
    ArraySequence<T> vector;
public:
    //Создание объекта
    Vector() {
        ArraySequence<T> new_vector;
        vector = new_vector;
    }//создание пустого вектора
    Vector(T *coords, int count) {
        ArraySequence<T> new_vector(coords, count);
        vector = new_vector;
    }// создание вектора по массиву
    explicit Vector(ArraySequence<T> &n_vector) {
        vector = n_vector;
    }//копирующий конструктор

    //Удаление объекта
    ~Vector() {
        vector.Delete_ArraySequence();
    }

    void Delete_Vector() {
        vector.Delete_ArraySequence();
    }

    T &GetCoord(int index) {
        return vector.Get(index);
    }

    int GetVectorLen() {
        return vector.GetLength();
    }

    //Операции
    Vector<T> SumOfVectors(Vector<T> b) {
        Vector<T> new_vector;
        if (vector.GetLength() == b.vector.GetLength()) {
            for (int i = 0; i < vector.GetLength(); i++) {
                new_vector.vector.Append(this->vector.Get(i) + b.vector.Get(i));
            }
        } else {
            int maxlen;
            int minlen;
            Vector<T> biger_vector;
            if (vector.GetLength() > b.vector.GetLength()) {
                biger_vector = Vector<T>(vector);//c *this тоже работает
                maxlen = vector.GetLength();
                minlen = b.vector.GetLength();
            } else {
                biger_vector = Vector<T>(b);
                maxlen = b.vector.GetLength();
                minlen = vector.GetLength();
            }

            for (int i = 0; i < minlen; i++) {
                new_vector.vector.Append(this->vector.Get(i) + b.vector.Get(i));
            }
            for (int i = minlen; i < maxlen; i++) {
                new_vector.vector.Append(biger_vector.vector.Get(i));
            }
        }
        return new_vector;
    }//cложит вектора любой размерности
    Vector<T> SubOfVectors(Vector<T> b) {
        Vector<T> new_vector;
        if (vector.GetLength() == b.vector.GetLength()) {
            for (int i = 0; i < vector.GetLength(); i++) {
                new_vector.vector.Append(this->vector.Get(i) - b.vector.Get(i));
            }
        } else {
            int maxlen;
            int minlen;
            Vector<T> bigger_vector;
            if (vector.GetLength() > b.vector.GetLength()) {
                bigger_vector = Vector<T>(vector);
                maxlen = vector.GetLength();
                minlen = b.vector.GetLength();
            } else {
                bigger_vector = Vector<T>(b);
                maxlen = b.vector.GetLength();
                minlen = vector.GetLength();
            }

            for (int i = 0; i < minlen; i++) {
                new_vector.vector.Append(this->vector.Get(i) - b.vector.Get(i));
            }
            for (int i = minlen; i < maxlen; i++) {
                new_vector.vector.Append(bigger_vector.vector.Get(i));
            }
        }
        return new_vector;
    }

    Vector<T> MulOfVectors(T scalar) {
        Vector<T> new_vector;
        for (int i = 0; i < vector.GetLength(); i++) {
            new_vector.vector.Append(this->vector.Get(i) * scalar);
        }
        return new_vector;
    }

    float Norm() {
        float norm = 0;

        for (int i = 0; i < vector.GetLength(); i++) {
            norm += std::abs(vector.Get(i)) * std::abs(vector.Get(i));
        }

        return std::sqrt(norm);
    }

    Vector<T> Normalization() {
        T len = 0;
        if (std::is_same<T, std::complex<double>>::value ||
            std::is_same<T, std::complex<float>>::value) { // Check if T is a complex type

            for (int i = 0; i < vector.GetLength(); i++) {
                len += std::norm(vector.Get(i)); // taking squared norm for complex numbers
            }
            len = std::sqrt(len);
            Vector<T> new_vector;
            for (int i = 0; i < vector.GetLength(); i++) {
                new_vector.vector.Append(vector.Get(i) / len);
            }
            return new_vector;
        } else { // T is not a complex type
            for (int i = 0; i < vector.GetLength(); i++) {
                len += vector.Get(i) * vector.Get(i);
            }
        }
        len = std::sqrt(len);
        Vector<T> new_vector;
        for (int i = 0; i < vector.GetLength(); i++) {
            new_vector.vector.Append(vector.Get(i) / len);
        }
        return new_vector;
    }

    T ScalarMulOfVectors(Vector<T> b) {
        T scalar = vector.Get(0) * b.vector.Get(0);
        int minlen;
        if (vector.GetLength() > b.vector.GetLength()) {
            minlen = b.vector.GetLength();
        } else {
            minlen = vector.GetLength();
        }
        for (int i = 1; i < minlen; i++) {
            scalar = scalar + vector.Get(i) * b.vector.Get(i);
        }

        return scalar;
    }

    //Перегрузка операторов
    friend std::ostream &operator<<(std::ostream &cout, Vector<T> &n_vector) {
        cout << '{';
        for (int i = 0; i < n_vector.GetVectorLen(); i++) {
            cout << n_vector.GetCoord(i);
            if (i != n_vector.GetVectorLen() - 1) {
                cout << ", ";
            }
        }
        cout << '}';
        return cout;
    }

    Vector<T> &operator=(Vector<T> n_vector) {
        vector = n_vector.vector;
        return *this;
    }

};


#endif //LABORATORY_WORK_2_VECTOR_H
