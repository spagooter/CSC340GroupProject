//
// Created by donny on 5/3/23.
//

#ifndef GROUP_PROJECT_CLASSES_H
#define GROUP_PROJECT_CLASSES_H
#include "classesImp.h"

template <typename T>
class Node{
private:
    T data;
    Node* prev;
    Node* next;
public:

};

template <typename T>
class linkedList{
private:
    Node<T>* first;
    Node<T>* last;
public:
    void addNode(T val);

};

#endif //GROUP_PROJECT_CLASSES_H
