#ifndef GROUP_PROJECT_CLASSES_H
#define GROUP_PROJECT_CLASSES_H

#include <iostream>

using namespace std;

/////////////////
/* node class */
///////////////
template<typename T>
class Node {
private:
    T val;
    Node* prev;
    Node* next;
public:
    Node();
    Node(T data);
    Node* getNextNode();
    Node* getPrevNode();
    T getNextVal();
    T getPrevVal();
    T getVal();
    void setNextNode(Node* temp);
    void setPrevNode(Node* temp);
    void setNextVal(T data);
    void setPrevVal(T data);
    void setVal(T data);
};

////////////////////////
/* Linked List class */
//////////////////////
template<typename T>
class linkedList {
private:
    Node<T>* first;
    Node<T>* last;
    int length;
public:
    linkedList();
    void addNode(T data);
    void addNode(Node<T>* temp);
    void print();
    Node<T>* begin();
    Node<T>* end();
    int size();
};

///////////////////////////////////
/* linked list member functions */
/////////////////////////////////
template <typename T>
int linkedList<T>::size(){
  return this->length;
}

//template to add nodes
template <typename T>
void linkedList<T>::addNode(Node<T>* temp) {
    if (this->first == nullptr) {
        this->first = temp;
        this->last = temp;
    }
    else {
        temp->setPrevNode(this->last);
        this->last->setNextNode(temp);
        this->last = temp;
    }
    ++this->length;
}

//template to add nodes from data
template <typename T>
void linkedList<T>::addNode(T data) {
    auto temp = new Node<T>(data);
    this->addNode(temp);
}

//default constructor
template <typename T>
linkedList<T>::linkedList() {
    this->first = nullptr;
    this->last = nullptr;
    this->length = 0;
}

//this function prints the list
template <typename T>
void linkedList<T>::print() {
    Node<T>* iter = this->first;
    while (iter != nullptr) {
        cout << iter->getVal() << endl;
        iter = iter->getNextNode();
    }
}

//returns the beginning of the list
template <typename T>
Node<T>* linkedList<T>::begin() {
    return this->first;
}

//returns the end of the list
template <typename T>
Node<T>* linkedList<T>::end() {
    return this->last;
}

////////////////////////////
/* node member functions */
//////////////////////////
//sets the current node value
template <typename T>
void Node<T>::setVal(T data) {
    this->val = data;
}

//returns the current node value
template <typename T>
T Node<T>::getVal() {
    return this->val;
}

//default node template constructor
template <typename T>
Node<T>::Node() {
    this->val = NULL;
    this->prev = nullptr;
    this->next = nullptr;
}

//node template constructor with data
template <typename T>
Node<T>::Node(T data) {
    this->val = data;
    this->prev = nullptr;
    this->next = nullptr;
}

//sets the value of the previous node
template<typename T>
void Node<T>::setPrevVal(T data) {
    this->prev->val = data;
}

//sets the value of the next node
template<typename T>
void Node<T>::setNextVal(T data) {
    this->next->val = data;
}

//sets the previous node
template<typename T>
void Node<T>::setPrevNode(Node* temp) {
    this->prev = temp;
}

//sets the next node
template<typename T>
void Node<T>::setNextNode(Node* temp) {
    this->next = temp;
}

//returns the previous value
template<typename T>
T Node<T>::getPrevVal() {
    return this->prev->val;
}
 //returns the next value
template<typename T>
T Node<T>::getNextVal() {
    return this->next->val;
}

//returns the previous node
template<typename T>
Node<T>* Node<T>::getPrevNode() {
    return this->prev;
}

//returns the next node
template<typename T>
Node<T>* Node<T>::getNextNode() {
    return this->next;
}



#endif //GROUP_PROJECT_CLASSES_H
