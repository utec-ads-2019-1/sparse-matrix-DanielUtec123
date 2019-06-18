#include <iostream>

#include "tester/tester.h"
#include "matrix.h"

int main() {
    //Tester::execute();


    Matrix<int> Matriz(3,4);

    Matriz.print();
    Matriz.set(1,0,7);
    Matriz.print();

    cout<< Matriz(1,1)<< endl;

    cout<< Matriz(2,1)<< endl;

    cout<< Matriz(1,0)<< endl;

    return EXIT_SUCCESS;
}

