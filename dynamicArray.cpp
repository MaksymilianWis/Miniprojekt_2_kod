#include "dynamicArray.hpp"

dynamicArray::dynamicArray(int capacity) : dynamicArrayCapacity(capacity), dynamicArrayPtr(new int[capacity]) {
    //konstruktor z argumentem rozmiaru tablicy, pointer wskazuje na początek tej tablicy
    for (int i = 0; i < dynamicArrayCapacity; i++) {
        dynamicArrayPtr[i] = 0;
    }
}
dynamicArray::dynamicArray() : dynamicArraySize(0), dynamicArrayCapacity(0), dynamicArrayPtr(new int[0])
{
    //konstruktor domyślny
}
dynamicArray::~dynamicArray() {
    if (dynamicArrayPtr == nullptr) return;
    free(dynamicArrayPtr);
    dynamicArrayCapacity = 0;
    dynamicArraySize = 0;
    dynamicArrayPtr = nullptr;
}

void dynamicArray::increaseCapacity() {
    // Sprawdzamy, czy tablica ma wystarczającą pojemność
    if (dynamicArraySize == dynamicArrayCapacity) {

        // Tworzymy nowy bufor o zwiększonej pojemności
        int* buffer = new int[dynamicArrayCapacity * 2];

        // Kopiujemy istniejące elementy do nowego bufora
        for (int i = 0; i < dynamicArraySize + 1; i++) {
            buffer[i] = dynamicArrayPtr[i];
        }

        // Usuwamy stary bufor
        delete[] dynamicArrayPtr;

        // Przypisujemy nowy bufor do dynamicArrayPtr
        dynamicArrayPtr = buffer;
        dynamicArrayCapacity *= 2;
    }
}

void dynamicArray::decreaseCapacity() {
    // Sprawdzamy, czy liczba elementów w tablicy spadła poniżej połowy jej aktualnej pojemności
    if (dynamicArraySize == (dynamicArrayCapacity / 2)) {

        // Tworzymy nowy bufor o zmniejszonej pojemności
        int* buffer = new int[dynamicArrayCapacity / 2];

        // Kopiujemy istniejące elementy do nowego bufora
        for (int i = 0; i < dynamicArraySize + 1; ++i) {
            buffer[i] = dynamicArrayPtr[i];
        }

        // Usuwamy stary bufor
        delete[] dynamicArrayPtr;

        // Przypisujemy nowy bufor do dynamicArrayPtr
        dynamicArrayPtr = buffer;
        dynamicArrayCapacity /= 2;
    }
}


int dynamicArray::getDynamicArraySize() const {
    return dynamicArraySize;
}

bool dynamicArray::isDynamicArrayEmpty() {
    return dynamicArraySize == 0;
}

int dynamicArray::getDynamicArrayElementAt(int index) {
    if (index < 0 || index >= dynamicArraySize) {
        cout << "Błąd: Indeks poza zakresem!" << endl;
        exit(EXIT_FAILURE);
    }
    return dynamicArrayPtr[index];
}

int dynamicArray::findElement(int element) {
    for (int i = 0; i < dynamicArraySize; i++) {
        if (dynamicArrayPtr[i] == element) {
            return i;
        }
    }
    return -1;
}

void dynamicArray::displayDynamicArrayWCapacity() {
    for (int i = 1; i < dynamicArrayCapacity + 1; i++) {
        cout << dynamicArrayPtr[i] << "\t"; // Wyświetlamy wartość na pozycji i
    }
    cout << endl;
}

void dynamicArray::displayDynamicArray() {  //wyswietlenie tablicy
    // Przechodzimy przez tablicę i wyświetlamy jej zawartość
    for (int i = 1; i < dynamicArraySize + 1; i++) {
        cout << dynamicArrayPtr[i] << "\t"; // Wyświetlamy wartość na pozycji i
    }
    cout << endl;
}

void dynamicArray::addBack(int element) { // dodaje element w koniec tablicy
    increaseCapacity();
    dynamicArraySize++;
    dynamicArrayPtr[dynamicArraySize] = element;
}

void dynamicArray::add(int index, int element) {
    if (index < 0) {
        cout << "Błąd: Niepoprawny indeks!" << endl;
        return;
    }

    if (index < dynamicArraySize) {
        increaseCapacity();
        dynamicArraySize++;
        for (int i = dynamicArraySize; i > index; i--) {
            dynamicArrayPtr[i + 1] = dynamicArrayPtr[i];
        }
        dynamicArrayPtr[index + 1] = element;
    }
    else {
        //gdy index jest większy niż size, wstaw nowy element na pierwszą wolną pozycję
        increaseCapacity();
        addBack(element);
    }
}

void dynamicArray::remove(int index) {
    if (index < 0 || index > dynamicArraySize) {
        cout << "Błąd: Niepoprawny indeks!" << endl;
        return;
    }

    // Usuwamy element na podanym indeksie
    for (int i = index + 1; i < dynamicArraySize; ++i) {
        dynamicArrayPtr[i] = dynamicArrayPtr[i + 1];
    }
    dynamicArraySize--;

    decreaseCapacity();
}

void dynamicArray::removeBack() {
    dynamicArraySize--;
    decreaseCapacity();
}

void dynamicArray::addFront(int element) {
    increaseCapacity();
    dynamicArraySize++;
    for (int i = dynamicArraySize; i > 0; i--) {
        dynamicArrayPtr[i] = dynamicArrayPtr[i - 1];
    }
    dynamicArrayPtr[1] = element;
}

void dynamicArray::removeFront() {
    for (int i = 1; i < dynamicArraySize; i++) {
        dynamicArrayPtr[i] = dynamicArrayPtr[i + 1];
    }
    dynamicArraySize--;
    decreaseCapacity();
}

void dynamicArray::fillFromArrayCSV(const std::string& filename, int maxElements) {
    // Otwieramy plik CSV
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open the file: " << filename << std::endl;
        return;
    }

    std::string line;
    int elementsAdded = 0;
    while (std::getline(file, line) && elementsAdded < maxElements) {
        std::istringstream iss(line);
        std::string value;
        while (std::getline(iss, value, ',') && elementsAdded < maxElements) {
            int element;
            try {
                // Konwertujemy wartość z ciągu znaków na liczbę całkowitą
                element = std::stoi(value);
            }
            catch (const std::invalid_argument& e) {
                // Ignorujemy nieprawidłowe wartości
                continue;
            }
            // Dodajemy element do tablicy
            addBack(element);
            elementsAdded++;
        }
    }

    // Zamykamy plik
    file.close();
}