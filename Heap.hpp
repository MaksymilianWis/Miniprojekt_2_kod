#pragma once

struct node
{
    node();
    node(int key, int value);
    
    int key_;
    int value_;
};


class Heap{
private:
    node* ptr_;
    unsigned size_;
    unsigned capacity_;

public:
    Heap(unsigned capacity);
    ~Heap();

    void insert(int element, int priority);
    int extractMax();
    int findMax();
    void modifyKey(int element, int new_priority);
    unsigned returnSize();


    void maxHeapify();
};