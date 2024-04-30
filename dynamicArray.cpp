#include "dynamicArray.h"

dynamicArray::dynamicArray(int capacity) : dynamicArrayCapacity(capacity), dynamicArrayPtr(new Element[capacity]), dynamicArraySize(0) {
    for(int i = 0; i < dynamicArrayCapacity; i++) {
        dynamicArrayPtr[i].value = 0;
        dynamicArrayPtr[i].priority = 0;
    }
}

dynamicArray::dynamicArray() : dynamicArraySize(0), dynamicArrayCapacity(0), dynamicArrayPtr(new Element[0]) {}

dynamicArray::~dynamicArray() {
    delete[] dynamicArrayPtr;
    dynamicArrayCapacity = 0;
    dynamicArraySize = 0;
    dynamicArrayPtr = nullptr;
}

void dynamicArray::increaseCapacity() {
    if (dynamicArraySize == dynamicArrayCapacity) {
        int newCapacity = dynamicArrayCapacity * 2;
        Element* newPtr = new Element[newCapacity];
        for (int i = 0; i < dynamicArraySize; ++i) {
            newPtr[i] = dynamicArrayPtr[i];
        }
        delete[] dynamicArrayPtr;
        dynamicArrayPtr = newPtr;
        dynamicArrayCapacity = newCapacity;
    }
}

void dynamicArray::decreaseCapacity() {
    if (dynamicArraySize < dynamicArrayCapacity / 4) {
        int newCapacity = dynamicArrayCapacity / 2;
        Element* newPtr = new Element[newCapacity];
        for (int i = 0; i < dynamicArraySize; ++i) {
            newPtr[i] = dynamicArrayPtr[i];
        }
        delete[] dynamicArrayPtr;
        dynamicArrayPtr = newPtr;
        dynamicArrayCapacity = newCapacity;
    }
}

int dynamicArray::getDynamicArraySize() const {
    return dynamicArraySize;
}

bool dynamicArray::isDynamicArrayEmpty() {
    return dynamicArraySize == 0;
}

Element dynamicArray::getDynamicArrayElementAt(int index) const{
    if (index < 0 || index >= dynamicArraySize) {
        std::cerr << "Błąd: Indeks poza zakresem!" << std::endl;
        exit(EXIT_FAILURE);
    }
    return dynamicArrayPtr[index];
}

void dynamicArray::addBack(Element element) {
    increaseCapacity();
    dynamicArrayPtr[dynamicArraySize] = element;
    dynamicArraySize++;
}

void dynamicArray::add(int index, Element element) {
    if (index < 0) {
        std::cerr << "Błąd: Niepoprawny indeks!" << std::endl;
        return;
    }

    if(index < dynamicArraySize) {
        increaseCapacity();
        for (int i = dynamicArraySize; i > index; i--) {
            dynamicArrayPtr[i] = dynamicArrayPtr[i-1];
        }
        dynamicArrayPtr[index] = element;
        dynamicArraySize++;
    } else {
        increaseCapacity();
        dynamicArrayPtr[dynamicArraySize] = element;
        dynamicArraySize++;
    }
}

void dynamicArray::remove(int index) {
    if (index < 0 || index >= dynamicArraySize) {
        std::cerr << "Błąd: Niepoprawny indeks!" << std::endl;
        return;
    }

    for (int i = index; i < dynamicArraySize - 1; ++i) {
        dynamicArrayPtr[i] = dynamicArrayPtr[i + 1];
    }
    dynamicArraySize--;

    decreaseCapacity();
}


