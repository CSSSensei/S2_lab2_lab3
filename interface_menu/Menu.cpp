#include "Menu.h"
#include "../Base/DynamicArray.cpp"

int chooseTypeVector(){
    int type;
    wcout << L"Выберете тип, с которым будете работать: \n"
         << L"\t1: int\n"
         << L"\t2: float\n"
         << L"\t3: complex\n"
         << L"Введите число: ";
    cin >> type;

    return type;
}
int chooseFunction(){
    int func;
    wcout << L"Выберете функцию, которую нужно произвести над векторами: \n"
         << L"\t1: Суммировать вектора\n"
         << L"\t2: Вычесть один вектор из другого\n"
         << L"\t3: Нормализовать вектор\n"
         << L"\t4: Скалярное умножение векторов\n"
         << L"Введите число: ";
    cin >> func;

    return func;
}
template<class T>
void saveVector(ArraySequence<Vector<T>> *Arr, Vector<T> *n_vector){
    Arr->Append(n_vector);
}

template<class T>
void outputTypedVector(ArraySequence<Vector<T>> *Arr, int index){
    auto k = Arr->Get(index);
    cout << k << endl;
}

void menu(){
    auto *intArr = new ArraySequence<Vector<int>>;
    auto *floatArr = new ArraySequence<Vector<float>>;
    auto *complexArr = new ArraySequence<Vector<complex<int>>>;

    int oper;
    while(true){
        wcout << L"Выберете операцию: \n"
             << L"\t1: Ввести и запомнить вектор\n"
             << L"\t2: Выполнить операцию над векторами\n"
             << L"\t3: Вывести вектор в консоль\n"
             << L"\t4: Закончить выполнение программы\n"
             << L"Введите число: ";
        cin >> oper;

        if (oper == 4)
            break;

        switch(oper){
            case 1: inputAndSaveVectorMenu(intArr, floatArr, complexArr);
            case 2: functionWithVectorMenu(intArr, floatArr, complexArr);
            case 3: outputVectorMenu(intArr, floatArr, complexArr);
            default: break;
        }
    }
}

void inputAndSaveVectorMenu(ArraySequence<Vector<int>> *intArr,
                        ArraySequence<Vector<float>> *floatArr,
                        ArraySequence<Vector<complex<int>>> *complexArr){

    int type = chooseTypeVector();
    int count;
    wcout << L"Введите размерность вектора:";
    cin >> count;

    switch(type){
        case 1: inputVectorTyped(intArr, count); break;
        case 2: inputVectorTyped(floatArr, count); break;
        case 3: inputVectorTyped(complexArr, count); break;
        default: break;
    }
}

template<class T>
void inputVectorTyped(ArraySequence<Vector<T>> *Arr, int count){
    wcout << L"Введите координаты вектора по порядку ";
    ArraySequence<T> n_arr;
    T item;
    for (int i = 0; i < count; i++){
        cin >> item;
        n_arr.Append(item);
    }
    Vector<T> n_vector(n_arr);
    Arr->Append(n_vector);
}

void functionWithVectorMenu(ArraySequence<Vector<int>> *intArr,
                        ArraySequence<Vector<float>> *floatArr,
                        ArraySequence<Vector<complex<int>>> *complexArr){

    int type = chooseTypeVector();

    switch(type){
        case 1: functionVectorTyped(intArr);
        case 2: functionVectorTyped(floatArr);
        case 3: functionVectorTyped(complexArr);
        default: break;
    }
}

template<class T>
void functionVectorTyped(ArraySequence<Vector<T>> *Arr){
    int func = chooseFunction();
    int len = Arr->GetLength();
    int indexOfArr1 = -1;
    int indexOfArr2 = -1;

    if (func == 3){
        wcout << L"В памяти находится \""<< len << "\" векторов" << endl;
        wcout << L"Выберете индекс вектора, который хотите нормализовать:";
        cin >> indexOfArr1;
        if (indexOfArr1 >= len || indexOfArr1 < 0){
            wcout << L"Массива с такой размерностью нет в памяти!" << endl;
            func = -1;
        }
    }else{
        wcout << L"В памяти находится \""<< len << "\" векторов" << endl;
        wcout << L"Выберете индексы векторов, с которыми хотите работать:";
        cin >> indexOfArr1;
        cin >> indexOfArr2;
        if (indexOfArr1 >= len || indexOfArr1 < 0 || indexOfArr2 >= len || indexOfArr2 < 0){
            wcout << L"Массива с такой размерностью нет в памяти!" << endl;
            func = -1;
        }
    }

    T scalar;
    switch(func){
        default:
            break;
        case 1:
            Arr->Append(Arr->Get(indexOfArr1).SumOfVectors(Arr->Get(indexOfArr2)));
            break;
        case 2:
            Arr->Append(Arr->Get(indexOfArr1).SubOfVectors(Arr->Get(indexOfArr2)));
            break;
        case 3:
            wcout << L"Введите скаляр, на который будете умножать:";
            cin >> scalar;
            Arr->Append(Arr->Get(indexOfArr1).MulOfVectors(scalar));
            break;
        case 4:
            T result;
            result = Arr->Get(indexOfArr1).ScalarMulOfVectors(Arr->Get(indexOfArr2));
            wcout << L"А вот и результат умножения:" << result << endl;
            break;
    }//результат записывается в последнюю ячейку памяти массива

    if (func != 3){
        Vector<T> resultVector (Arr->Get(Arr->GetLength() - 1));
        cout << resultVector;
    }
}

void outputVectorMenu(ArraySequence<Vector<int>> *intArr,
                  ArraySequence<Vector<float>> *floatArr,
                  ArraySequence<Vector<complex<int>>> *complexArr){

    int type = chooseTypeVector();
    int index;

    wcout << L"Введите индекс вектора, который хотите вывести:";
    cin >> index;

    switch (type){
        case 1: outputTypedVector(intArr, index); break;
        case 2: outputTypedVector(floatArr, index); break;
        case 3: outputTypedVector(complexArr, index);
        default: break;
    }

}

