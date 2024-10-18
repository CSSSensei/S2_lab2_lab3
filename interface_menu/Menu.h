#ifndef LABORATORY_WORK_2_MENU_H
#define LABORATORY_WORK_2_MENU_H
#include <iostream>
#include "../DataStructures/Vector.h"
#include <complex>

using namespace std;

int chooseTypeVector();
int chooseFunctionVector();
template<class T>
void saveVector(ArraySequence<Vector<T>> *Arr, Vector<T> *n_vector);

void menu();
//1
void inputAndSaveVectorMenu(ArraySequence<Vector<int>> *intArr,
                        ArraySequence<Vector<float>> *floatArr,
                        ArraySequence<Vector<complex<int>>> *complexArr);
template <class T>
void inputVectorTyped(ArraySequence<Vector<T>> *Arr, int count);
//2
void functionWithVectorMenu(ArraySequence<Vector<int>> *intArr,
                         ArraySequence<Vector<float>> *floatArr,
                         ArraySequence<Vector<complex<int>>> *complexArr);
template<class T>
void functionVectorTyped(ArraySequence<Vector<T>> *Arr);

//3
void outputVectorMenu(ArraySequence<Vector<int>> *intArr,
                  ArraySequence<Vector<float>> *floatArr,
                  ArraySequence<Vector<complex<int>>> *complexArr);

template<class T>
void outputTypedVector(ArraySequence<Vector<T>> *Arr, int index);












#endif //LABORATORY_WORK_2_MENU_H
