#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <stdexcept>
#include "node.h"

using namespace std;

template <typename T>
class Matrix {
private:
    Node<T> *root;
    unsigned rows, columns;

public:
    Matrix(unsigned rows, unsigned columns){
        int i = 0;
        Node<T>* temp = root ;
        while (i < rows){
            temp -> down = new HeaderNode<T>();
            temp = temp ->down;
            i++;
        }
        i = 0;
        temp = root;
        while (i < columns){
            temp -> next = new HeaderNode<T>();
            temp = temp ->next;
            i++;
        }

    };

    void set(unsigned, unsigned, T);

    T operator()(unsigned, unsigned) const{

    };
    Matrix<T> operator*(T scalar) const;
    Matrix<T> operator*(Matrix<T> other) const;
    Matrix<T> operator+(Matrix<T> other) const;
    Matrix<T> operator-(Matrix<T> other) const;
    Matrix<T> transpose() const;
    void print() const;

    ~Matrix();
};




#endif //SPARSE_MATRIX_MATRIX_H