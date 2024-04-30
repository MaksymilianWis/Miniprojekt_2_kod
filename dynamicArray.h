//
// Created by Patryk on 20.04.2024.
//

#ifndef KOLEJKA_PRIORYTETOWA_DYNAMICARRAY_H
#define KOLEJKA_PRIORYTETOWA_DYNAMICARRAY_H


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <random>
#include <fstream>
#include <sstream>

using namespace std;

struct Element {
    int value;
    int priority;
};

class dynamicArray {
private:
    Element* dynamicArrayPtr;
    int dynamicArraySize;
    int dynamicArrayCapacity;

    void increaseCapacity();
    void decreaseCapacity();

public:
    dynamicArray(int capacity);
    dynamicArray();
    ~dynamicArray();

    int getDynamicArraySize() const;
    bool isDynamicArrayEmpty();
    Element getDynamicArrayElementAt(int index) const;


    void addBack(Element element);
    void add(int index, Element element);
    void remove(int index);
};


#endif //KOLEJKA_PRIORYTETOWA_DYNAMICARRAY_H
