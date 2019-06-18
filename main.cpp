#include <iostream>

#include "tester/tester.h"
#include "matrix.h"

int main() {
    //Tester::execute();


    Matrix<int> Matriz(3,4);

    Matriz.print();
    Matriz.set(1,0,7);
    Matriz.print();


    return EXIT_SUCCESS;
}

