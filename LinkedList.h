#ifndef GROUP_PROJECT_CLASSES_H
#define GROUP_PROJECT_CLASSES_H

#include <iostream>

using namespace std;

template <typename T>
class linkedList;

/////////////////
/* node class */
///////////////
template<typename T>
class Node {
    friend class linkedList<T>;
private:
    T val;
    Node* prev;
    Node* next;
public:
    Node();
    Node(T data);
    Node* getNextNode() { return this->next; }
    Node* getPrevNode() { return this->prev; }
    T getNextVal() { return this->next->val; }
    T getPrevVal() { return this->prev->val; }
    T getVal() { return this->val; }
    void setNextNode(Node* temp) { this->next = temp; }
    void setPrevNode(Node* temp) { this->prev = temp; }
    void setNextVal(T data) { this->next->val = data; }
    void setPrevVal(T data) { this->prev->val = data; }
    void setVal(T data) { this->val = data; }
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
    ~linkedList();
    void addNode(T data);
    void addNode(Node<T>* temp);
    void print();
    void remove(T data);
    void removeNode(Node<T> *temp);
    int size() { return this->length; }
    Node<T> *begin() { return this->first; }
    Node<T> *end() { return this->last; }
    Node<T> *find(T data);
    linkedList& operator=(const linkedList &rhs);

};

///////////////////////////////////
/* linked list member functions */
/////////////////////////////////
//destructor
template <typename T>
linkedList<T>::~linkedList<T>(){
  auto iter = this->first;
  while (iter != nullptr){
    auto next = iter->next;
    delete iter;
    iter = next;
  }
  this->first = nullptr;
  this->last = nullptr;
  delete iter;
  delete this;
}

//assignment operator overload
template <typename T>
linkedList<T>& linkedList<T>::operator=(const linkedList<T> &rhs){
  auto iter = rhs.first;
  while (iter != nullptr){
    this->addNode(iter);
    iter = iter->next;
  }
  return *this;
}

//function to find a node with specific data
template <typename T>
Node<T>* linkedList<T>::find(T data) {
  bool found = false;
  auto iter = this->first;
  while (iter != nullptr) {
    if (iter->val == data) {
      found = true;
      break;
    }
    iter = iter->next;
  }
  return found ? iter : nullptr;
}

//template to add nodes
template <typename T>
void linkedList<T>::addNode(Node<T>* temp) {
    if (this->first == nullptr) {
        this->first = temp;
        this->last = temp;
    }
    else {
        temp->prev = this->last;
        this->last->next = temp;
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
    auto iter = this->first;
    while (iter != nullptr) {
        cout << iter->val << endl;
        iter = iter->next;
    }
}

////////////////////////////
/* node member functions */
//////////////////////////

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

#endif //GROUP_PROJECT_CLASSES_H
