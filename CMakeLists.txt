cmake_minimum_required(VERSION 3.17)
project(S3_laboratory_work_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(S3_laboratory_work_2
        main.cpp
        "Tests/Tests_DA and LL.h"
        "Tests/Tests_DA and LL.cpp"
        "Tests/Tests_AS and LLS.h"
        DataStructures/Vector.h
        "Tests/Tests_AS and LLS.cpp"
        interface_menu/MenuVector.h
        interface_menu/MenuVector.cpp
        interface_menu/MenuMatrix.h
        interface_menu/MenuMatrix.cpp
        interface_menu/MenuAll.h
        interface_menu/Menu.h
        interface_menu/Menu.cpp
        Sequence/LinkedListSequence.h
        Base/LinkedList.h
        Base/LinkedList.cpp
        interface_menu/MenuSequence.h
        interface_menu/MenuSequence.cpp
        Tests/Tests_Vector.h
        Tests/Tests_Matrix.h
        Tests/Tests_Vector.cpp
        Tests/Tests_Matrix.cpp
        pointers/ShrdPtr.h
        pointers/Counter.h
        pointers/UnqPtr.h
        Sort/ISorter.h
        Sort/BubbleSort.h
        Sort/BatcherSort.h
)