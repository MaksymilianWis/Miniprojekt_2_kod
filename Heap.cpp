#pragma once

#include "Heap.hpp"


// NODE
node::node() : key_(0), value_(0) {};
node::node(int key, int value) : key_(key), value_(value) {};

// HEAP
Heap::Heap(unsigned capacity) : size_(capacity), capacity_(capacity), ptr_(new node[capacity]) {};
Heap::~Heap(){
    delete[] ptr_;
    ptr_ = nullptr;
}

void Heap::insert(int element, int priority){

}

int Heap::extractMax(){

}

int Heap::findMax(){

}

void Heap::modifyKey(int element, int priority){

}

unsigned Heap::returnSize(){

}