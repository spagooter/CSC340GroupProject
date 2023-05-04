//
// Created by donny on 5/3/23.
//
#ifndef CLASSES_IMP_CPP
#define CLASSES_IMP_CPP
#include "classes.h"
#include <iostream>


using namespace std;

template <typename T>
linkedList<T>::linkedList(){
  this->first = nullptr;
  this->last = nullptr;
}

template <typename T>
void linkedList<T>::print(){
  cout << "print" << endl;
}
#endif