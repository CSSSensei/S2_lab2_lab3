cmake_minimum_required(VERSION 3.17)
project(S3_laboratory_work_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(S3_laboratory_work_2
        main.cpp
        "Tests/Tests_DA and LL.h"
        "Tests/Tests_DA and LL.cpp"
        "Tests/Tests_AS and LLS.h"
        Vector.h
        Vector.cpp
        "Tests/Tests_AS and LLS.cpp"
        Sequence.cpp
        MenuVector.h
        MenuVector.cpp
        MenuMatrix.h
        MenuMatrix.cpp
        MenuAll.h
        MenuAll.cpp
        Menu.h
        Menu.cpp
        Matrix.cpp
        Sequence/LinkedListSequence.h
        Base/LinkedListSequence.cpp
        Base/LinkedList.h
        Base/LinkedList.cpp
        Base/ArraySequence.cpp
        MenuSequence.h
        MenuSequence.cpp
        Tests/Tests_Vector.h
        Tests/Tests_Matrix.h
        Tests/Tests_Vector.cpp
        Tests/Tests_Matrix.cpp
)