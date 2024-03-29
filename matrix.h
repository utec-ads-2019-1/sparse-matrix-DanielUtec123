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
        //cout << "se crearon "<< i << " filas"<< endl;
        i = 0;
        temp = root;
        while (i < columns){
            temp -> next = new HeaderNode<T>();
            temp = temp ->next;
            i++;
        }

        //cout << "se crearon "<< i << " columnas"<< endl;

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
            element_ptr = (ElementNode<T> *) element_ptr->next;
        }
        return nullptr;
    }

    void set(unsigned y, unsigned x , T data){
        if(y>=rows or x >=columns)
            throw runtime_error("los indices");

        ElementNode<T>* element_ptr =  IsNode(x,y);
        if(element_ptr)
            element_ptr->data = data;
        else{
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

    T operator()(unsigned y, unsigned x) const{
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
                result.set(ptr_element->y,ptr_element->x,scalar*(ptr_element->data));
                ptr_element = (ElementNode<T> *)ptr_element->next;
            }
        }
        return result;
    };
    Matrix<T> operator*(Matrix<T> other) const{

        //cout << "multi"<<endl;
        if(other.rows != columns)
            throw runtime_error("dimensiones incorrectas");
        Matrix<T> result(rows, other.columns);

        Node<T>* temp_1 = root;
        Node<T>* temp_2;
        Node<T>* temp_col= other.root;


        ElementNode<T>* ptr_element1;
        ElementNode<T>* ptr_element2;

        for (int i = 0; i < rows ; ++i) {
            temp_1 = temp_1->down;
            temp_2 = temp_col;
            for (int j = 0; j <other.columns ; ++j) {
                ptr_element1 = (ElementNode<T>*)temp_1->next;
                temp_2 = temp_2->next;
                ptr_element2 = (ElementNode<T>*)temp_2->down;

                T total = 0;
                while (ptr_element1 and ptr_element2){
                    if(ptr_element1->x == ptr_element2->y){
                        total += ptr_element1->data*ptr_element2->data;
                        ptr_element1 = (ElementNode<T>*)ptr_element1->next;
                        ptr_element2 = (ElementNode<T>*)ptr_element2->down;
                    }
                    else if(ptr_element1->x > ptr_element2->y){
                        ptr_element2 = (ElementNode<T>*)ptr_element2->down;
                    }
                    else if(ptr_element1->x < ptr_element2->y){
                        ptr_element1 = (ElementNode<T>*)ptr_element1->next;
                    }
                }

                if(total!=0)
                    result.set(i,j,total);
            }

        }
        return result;




    };
    Matrix<T> operator+(Matrix<T> other) const{

        if(other.rows != rows or other.columns != columns)
            throw runtime_error("dimensiones incorrectas");

        Matrix<T> result(rows, columns);
        Node<T>* temp_1 = other.root;
        Node<T>* temp_2 = root;

        ElementNode<T>* ptr_element1;
        ElementNode<T>* ptr_element2;

        for (int i = 0; i < rows ; ++i) {
            temp_1 = temp_1->down;
            temp_2 = temp_2->down;

            ptr_element1 = (ElementNode<T>*)temp_1->next;
            ptr_element2 = (ElementNode<T>*)temp_2->next;

            while (ptr_element1 or ptr_element2){
                if(ptr_element1 and ptr_element2){
                    if(ptr_element1->x == ptr_element2->x){
                        result.set(i,ptr_element1->x,ptr_element1->data + ptr_element2->data);
                        ptr_element1 = (ElementNode<T>*)ptr_element1->next;
                        ptr_element2 = (ElementNode<T>*)ptr_element2->next;
                    }
                    else if(ptr_element1->x > ptr_element2->x){
                        result.set(i,ptr_element2->x,ptr_element2->data);
                        ptr_element2 = (ElementNode<T>*)ptr_element2->next;
                    }
                    else if(ptr_element1->x < ptr_element2->x){
                        result.set(i,ptr_element1->x,ptr_element1->data);
                        ptr_element1 = (ElementNode<T>*)ptr_element1->next;
                    }
                } else if(ptr_element1){
                    result.set(i,ptr_element1->x,ptr_element1->data);
                    ptr_element1 = (ElementNode<T>*)ptr_element1->next;

                } else if(ptr_element2){
                    result.set(i,ptr_element2->x,ptr_element2->data);
                    ptr_element2 = (ElementNode<T>*)ptr_element2->next;
                }
            }
        }
        //result.print();
        return result;


    };
    Matrix<T> operator-(Matrix<T> other) const{
        if(other.rows != rows or other.columns != columns)
            throw runtime_error("dimensiones incorrectas");

        Matrix<T> result(rows, columns);
        Node<T>* temp_1 = other.root;
        Node<T>* temp_2 = root;

        ElementNode<T>* ptr_element1;
        ElementNode<T>* ptr_element2;

        for (int i = 0; i < rows ; ++i) {
            temp_1 = temp_1->down;
            temp_2 = temp_2->down;

            ptr_element1 = (ElementNode<T>*)temp_1->next;
            ptr_element2 = (ElementNode<T>*)temp_2->next;

            while (ptr_element1 or ptr_element2){

                if(ptr_element1 and ptr_element2){
                    if(ptr_element1->x == ptr_element2->x){
                        result.set(i,ptr_element1->x,ptr_element2->data - ptr_element1->data);
                        ptr_element1 = (ElementNode<T>*)ptr_element1->next;
                        ptr_element2 = (ElementNode<T>*)ptr_element2->next;
                    }
                    else if(ptr_element1->x > ptr_element2->x){
                        result.set(i,ptr_element2->x,ptr_element2->data);
                        ptr_element2 = (ElementNode<T>*)ptr_element2->next;
                    }
                    else if(ptr_element1->x < ptr_element2->x){
                        result.set(i,ptr_element1->x,(-1)*ptr_element1->data);
                        ptr_element1 = (ElementNode<T>*)ptr_element1->next;
                    }
                } else if(ptr_element1){
                    result.set(i,ptr_element1->x,(-1)*ptr_element1->data);
                    ptr_element1 = (ElementNode<T>*)ptr_element1->next;

                } else if(ptr_element2){
                    result.set(i,ptr_element2->x,ptr_element2->data);
                    ptr_element2 = (ElementNode<T>*)ptr_element2->next;
                }
            }
        }
        return result;

    };
    Matrix<T> transpose() const{
        Matrix<T> result(columns, rows);
        ElementNode<T> *ptr_element;
        Node<T>* temp = root;

        for (int i = 0; i < rows ; ++i) {
            temp = temp->down;
            ptr_element = (ElementNode<T>*)temp->next;
            while (ptr_element){
                result.set(ptr_element->y,ptr_element->x,ptr_element->data);
            ptr_element = (ElementNode<T> *)ptr_element->next;
            }
        }
        return result;



    };
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

    };

    ~Matrix(){

       /* root->next->DeleteAllNext();
        root->DeleteAsRoot();
        */
    };
};


#endif //SPARSE_MATRIX_MATRIX_H