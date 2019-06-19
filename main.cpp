#include <iostream>

#include "tester/tester.h"
#include "matrix.h"

int main() {
    //Tester::execute();


    Matrix<int> Matriz(3,4);

    Matriz.set(1,0,7);
    Matriz.set(2,2,4);
    Matriz.print();

    Matrix<int> C(3,4);
    Matrix<int> D(3,4);
    Matrix<int> E(3,4);



    D.set(1,0,4);
    D.set(1,1,5);
    D.set(2,2,6);
    D.print();

    C = D + Matriz;
    C.print();

    E  = Matriz-D;
    E.print();
   /*


    C = Matriz*5;
    C.print();

    cout<< Matriz(1,1)<< endl;

    cout<< Matriz(2,1)<< endl;

    cout<< Matriz(1,0)<< endl;*/

    return EXIT_SUCCESS;
}

