//
// Created by donny on 5/3/23.
//

#ifndef GROUP_PROJECT_CLASSES_H
#define GROUP_PROJECT_CLASSES_H
#include <iostream>
using namespace std;

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
    void print();
};

template <typename T>
linkedList<T>::linkedList(){
  this->first = nullptr;
  this->last = nullptr;
}

template <typename T>
void linkedList<T>::print(){
  cout << "print" << endl;
}

#endif //GROUP_PROJECT_CLASSES_H
