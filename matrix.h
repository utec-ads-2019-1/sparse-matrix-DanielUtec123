#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <stdexcept>
#include "node.h"
#include <iostream>

using namespace std;

template <typename T>
class Matrix {
private:
    Node<T> *root;
    unsigned rows, columns;

public:
    Matrix(unsigned rows, unsigned columns){
        this->rows = rows;
        this->columns = columns;

        root = new Node<T>;
        int i = 0;
        Node<T>* temp = root ;
        while (i < rows){
            temp -> down = new HeaderNode<T>();
            temp = temp ->down;
            i++;
        }
        cout << "se crearon "<< i << " filas"<< endl;
        i = 0;
        temp = root;
        while (i < columns){
            temp -> next = new HeaderNode<T>();
            temp = temp ->next;
            i++;
        }

        cout << "se crearon "<< i << " columnas"<< endl;

    };


    ElementNode<T>* IsNode(int x, int y){
        if(y>=rows or x >=columns)
            throw runtime_error("los indices");
        Node<T>* temp = root;
        for (int j = 0; j <= y ; ++j) {
            temp = temp->down;
        }
        ElementNode<T>* element_ptr;
        element_ptr = (ElementNode<T> *) temp->next;
        while (element_ptr){
            if(element_ptr->x==x)
                return element_ptr;
        }
        return nullptr;
    }

    void set(unsigned x, unsigned y , T data){
        if(y>=rows or x >=columns)
            throw runtime_error("los indices");

        ElementNode<T>* element_ptr =  IsNode(x,y);
        if(element_ptr)
            element_ptr->data = data;
        else{
            cout << "elemento no exite"<< endl;
            Node<T>* temp_y = root;
            for (int j = 0; j <=  y ; ++j) {
                temp_y = temp_y->down;
            }
            //temp_y apunta al header_row y

            Node<T>* temp_x = root;
            for (int i = 0; i <= x ; ++i) {
                temp_x = temp_x->next;
            }
            //temp_x apunta al header_column x

            ElementNode<T>* new_element = new ElementNode<T>(x,y,data);

            ElementNode<T>* ptr_column = (ElementNode<T> *)temp_y->next;

            ElementNode<T>* ptr_row = (ElementNode<T> *)temp_x->down;

            while (ptr_column){

                if(ptr_column->next){
                    if(((ElementNode<T> *)ptr_column->next)->x>x) {
                        ElementNode<T>* t = (ElementNode<T> *)ptr_column ->next;
                        ptr_column->next = new_element;
                        new_element->next = t;
                        break;
                    }
                } else{
                    ptr_column->next = new_element;
                    break;
                }
                ptr_column = (ElementNode<T> *)ptr_column->next;
            }


            while (ptr_row){

                if(ptr_row->down){
                    if(((ElementNode<T> *)ptr_row->down)->y > y) {
                        ElementNode<T>* t = (ElementNode<T> *)ptr_row ->down;
                        ptr_row->down = new_element;
                        new_element->down = t;
                        break;
                    }
                } else{
                    ptr_row->down = new_element;

                    break;
                }
                ptr_row = (ElementNode<T> *)ptr_row->down;
            }
            if(!ptr_column)
                temp_y->next = new_element;

            if(!ptr_row)
                temp_x->down = new_element;


        }
    };

    T operator()(unsigned x, unsigned y) const{
        Node<T>* temp_y = root ;

        for (int j = 0; j <=  y ; ++j) {
            temp_y = temp_y->down;
        }
        //temp_y apunta al header_row y
        ElementNode<T>* ptr_column = (ElementNode<T> *)temp_y->next;

        if(!ptr_column)
            return 0;

        while (ptr_column){
            if(ptr_column->x == x)
                return ptr_column->data;
            if(ptr_column->x > x)
                return 0;
            ptr_column = (ElementNode<T> *)ptr_column->next;
        }

        return 0;



    };
    Matrix<T> operator*(T scalar) const{

        ElementNode<T> *ptr_element;
        Node<T>* temp = root;
        Matrix<T> result(rows, columns);


        for (int i = 0; i < rows ; ++i) {
            temp = temp->down;
            ptr_element = (ElementNode<T>*)temp->next;
            while (ptr_element){
                result.set(ptr_element->x,ptr_element->y,scalar*(ptr_element->data));
                ptr_element = (ElementNode<T> *)ptr_element->next;
            }
        }

        return result;

    };
    Matrix<T> operator*(Matrix<T> other) const;
    Matrix<T> operator+(Matrix<T> other) const;
    Matrix<T> operator-(Matrix<T> other) const;
    Matrix<T> transpose() const;
    void print() const{
        Node<T>* temp = root ;

        ElementNode<T>* element_ptr;

        for (int i = 0; i < rows; ++i) {
            temp = temp->down;
            element_ptr = (ElementNode<T> *) temp->next;
            for (int j = 0; j < columns; ++j) {
                if (element_ptr and element_ptr->x == j) {

                        cout << element_ptr->data << " ";
                        element_ptr = (ElementNode<T> *) element_ptr->next;

                } else {
                    cout << 0 << " ";
                }
            }
            cout << endl;
        }
        temp = root;
        for (int i = 0; i < rows; ++i) {
            temp = temp->down;
            element_ptr = (ElementNode<T> *) temp->next;
            for (int j = 0; j < columns; ++j) {
                if (element_ptr) {
                    if (element_ptr->x == j) {
                        cout << element_ptr->data << " x = " << element_ptr->x << "  y = "<< element_ptr->y<< endl;
                        element_ptr = (ElementNode<T> *) element_ptr->next;
                    }
                }
            }
            cout << endl;
        }


    };

    ~Matrix(){};
};




#endif //SPARSE_MATRIX_MATRIX_H