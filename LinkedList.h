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
    //~linkedList();
    void addNode(T data);
    void addNode(Node<T>* temp);
    void print();
    void remove(T data);
    int size() { return this->length; }
    Node<T> *begin();
    Node<T> *end();
    Node<T> *find(T data);
    linkedList& operator=(const linkedList &rhs);

};

///////////////////////////////////
/* linked list member functions */
/////////////////////////////////

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

//fundtion to remove a node containing specific data
template <typename T>
void linkedList<T>::remove(T data) {
  Node<T>* iter = this->find(data);
  if (iter == nullptr) {
    cout << "not found" << endl;
    return;
  }
  if (iter == this->first) {
    Node<T>* temp = this->first;
    this->first = this->first->next;
    this->first->prev = nullptr;
    delete temp;
  }
  else if (iter == this->last) {
    Node<T>* temp = this->last;
    this->last = this->last->prev;
    this->last->next = nullptr;
    delete temp;
  }
  else {
    Node<T>* temp = iter;
    iter->prev->next = iter->next;
    iter->next->prev = iter->prev;
    delete temp;
  }
  --this->length;
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
