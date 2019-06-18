#ifndef SPARSE_MATRIX_NODE_H
#define SPARSE_MATRIX_NODE_H

template <typename T>
class Matrix;

template <typename T>
class Node {

public:
    Node<T> *next, *down;
    Node() : next(nullptr),down(nullptr){};
    friend class Matrix<T>;
};


template <typename T>
class HeaderNode : public Node<T> {
    public:
        HeaderNode() : Node<T>(){}
};


template <typename T>
class ElementNode : public Node<T> {
public:
    int x;
    int y;
    ElementNode() : Node<T>(){}
    ElementNode(int x,int y,T data) {
        this->x = x;
        this->y = y;
        this->data = data;
    }


    void set_data(T data){
        this->data = data;
    }

    T data;
};


#endif //SPARSE_MATRIX_NODE_H
