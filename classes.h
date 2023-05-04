//
// Created by donny on 5/3/23.
//

#ifndef GROUP_PROJECT_CLASSES_H
#define GROUP_PROJECT_CLASSES_H

#include <iostream>

using namespace std;

/* node class */
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

/* Linked List Iterator class */
template <typename T>
class linkedListIterator {
private:
  Node<T>* index;
public:
  Node<T>& operator++();
  Node<T>& operator=(Node<T>* other);
};

/* Linked List class */
template<typename T>
class linkedList {
private:
  Node<T>* first;
  Node<T>* last;
public:
  linkedList();
  void add(T data);
  void add(Node<T>* temp);
  void print();
  Node<T>* begin();
  Node<T>* end();
};

/* linked list iterator member functions */
template <typename T>
Node<T>& linkedListIterator<T>::operator++() {
  this->index = index->getNextNode();
  return *this;
}

template <typename T>
Node<T>& linkedListIterator<T>::operator=(Node<T>* other) {
  this->index = other;
  return *this;
}

/* linked list member functions */
template <typename T>
void linkedList<T>::add(Node<T>* temp) {
  if (this->first == nullptr) {
    this->first = temp;
    this->last = temp;
  }
  else {
    temp->setPrevNode(this->last);
    this->last->setNextNode(temp);
    this->last = temp;
  }
}

template <typename T>
void linkedList<T>::add(T data) {
  Node<T>* temp = new Node<T>(data);
  this->add(temp);
}

template <typename T>
linkedList<T>::linkedList() {
  this->first = nullptr;
  this->last = nullptr;
}

template <typename T>
void linkedList<T>::print() {
  linkedListIterator<T> iter = this->first;
  cout << iter->index->val;
}

template <typename T>
Node<T>* linkedList<T>::begin() {
  return this->first;
}

template <typename T>
Node<T>* linkedList<T>::end() {
  return this->end;
}

/* node member functions */
template <typename T>
void Node<T>::setVal(T data) {
  this->val = data;
}

template <typename T>
T Node<T>::getVal() {
  return this->val;
}

template <typename T>
Node<T>::Node() {
  this->val = NULL;
  this->prev = nullptr;
  this->next = nullptr;
}

template <typename T>
Node<T>::Node(T data) {
  this->val = data;
  this->prev = nullptr;
  this->next = nullptr;
}

template<typename T>
void Node<T>::setPrevVal(T data) {
  this->prev->val = data;
}

template<typename T>
void Node<T>::setNextVal(T data) {
  this->next->val = data;
}

template<typename T>
void Node<T>::setPrevNode(Node* temp) {
  this->prev = temp;
}

template<typename T>
void Node<T>::setNextNode(Node* temp) {
  this->next = temp;
}

template<typename T>
T Node<T>::getPrevVal() {
  return this->prev->val;
}

template<typename T>
T Node<T>::getNextVal() {
  return this->next->val;
}

template<typename T>
Node<T>* Node<T>::getPrevNode() {
  return this->prev;
}

template<typename T>
Node<T>* Node<T>::getNextNode() {
  return this->next;
}

#endif //GROUP_PROJECT_CLASSES_H
