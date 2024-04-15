#pragma once

#include "dynamicArray.hpp"


class Heap{
private:
    // liczone od 1
    node* ptr_;
    unsigned size_;
    unsigned capacity_;

    void increaseCapacity();
public:
    Heap(unsigned capacity);
    ~Heap();

    void insert(int element, int priority);
    int extractMax();
    int findMax();
    void modifyKey(int element, int new_priority);
    unsigned returnSize();


    void maxHeapify(unsigned i);
    void buildMaxHeap();
};