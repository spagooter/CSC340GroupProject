//
// Created by donny on 5/3/23.
//

#ifndef GROUP_PROJECT_CLASSES_H
#define GROUP_PROJECT_CLASSES_H

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
    linkedList();
    void addNode(T val);
    void print();
};

#endif //GROUP_PROJECT_CLASSES_H
