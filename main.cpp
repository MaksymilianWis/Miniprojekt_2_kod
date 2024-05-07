#include <iostream>
#include "priorityQueue.h"

#include "dynamicArray.h"
#include "Zapis.h"
#include "test.h"
#include "cstdlib"
#include <ctime>
#include <chrono>

using namespace std;

//void runDynamicArray() {
//    dynamicArray dynamicArray1(4);
//    int element, index;
//    char choice2;
//    do {
//        cout << "1. addFront" << endl;
//        cout << "2. addBack" << endl;
//        cout << "3. add" << endl;
//        cout << "4. removeFront" << endl;
//        cout << "5. removeBack" << endl;
//        cout << "6. remove" << endl;
//        cout << "7. display" << endl;
//        cout << "8. display with capacity" << endl;
//        cout << "9. isDynamicArrayEmpty" << endl;
//        cout << "10. getDynamicArrayElementAt" << endl;
//        cout << "11. getDynamicArraySize" << endl;
//        cout << "12. fillFromArrayCSV" << endl;
//        cout << "13. Exit" << endl;
//
//        cin >> choice2;
//        switch (choice2) {
//            case '1':
//                cout << "Enter the element you want to add: ";
//                cin >> element;
//                dynamicArray1.addFront(element);
//                break;
//            case '2':
//                cout << "Enter the element you want to add (back): ";
//                cin >> element;
//                dynamicArray1.addBack(element);
//                break;
//            case '3':
//                cout << "Enter the index and the element you want to add: ";
//                cin >> index >> element;
//                dynamicArray1.add(index, element);
//                break;
//            case '4':
//                cout << "Removing the first element..." << endl;
//                dynamicArray1.removeFront();
//                break;
//            case '5':
//                cout << "Removing the last element..." << endl;
//                dynamicArray1.removeBack();
//                break;
//            case '6':
//                cout << "Enter the index you want to remove: ";
//                cin >> index;
//                dynamicArray1.remove(index);
//                break;
//            case '7':
//                dynamicArray1.displayDynamicArray();
//                break;
//            case '8':
//                dynamicArray1.displayDynamicArrayWCapacity();
//                break;
//            case '9':
//                if (dynamicArray1.isDynamicArrayEmpty()) {
//                    cout << "The dynamicArray is empty." << endl;
//                } else {
//                    cout << "The dynamicArray is not empty." << endl;
//                }
//                break;
//            case '10':
//                cout << "Enter the index of the element you want to get: ";
//                cin >> index;
//                cout << "The element at index " << index << " is: " << dynamicArray1.getDynamicArrayElementAt(index)
//                     << endl;
//                break;
//            case '11':
//                cout << "The size of the dynamicArray is: " << dynamicArray1.getDynamicArraySize() << endl;
//                break;
//            case '12':
//                cout << "Filling the dynamicArray from a CSV file: random_numbers.csv ..." << endl;
//                dynamicArray1.fillFromArrayCSV("random_numbers.csv", 50000);
//                break;
//            case '13':
//                cout << "Exiting..." << endl;
//                break;
//
//        }
//    } while (choice2 != '13');
//}



void testing(const unsigned numOfPQ, int size, int iteration){

    Zapis plik_insert("PriorityQueue_insert.csv");
    Zapis plik_extract_max("PriorityQueue_extract_max.csv");
    Zapis plik_findMax("PriorityQueue_findMax.csv");
    Zapis plik_modifyKey("PriorityQueue_modifyKey.csv");

    cout << "Please wait..." << endl;
    //   PriorityQueue *pQ[numOfPQ];
    //   PriorityQueue *pQbackup[numOfPQ];

    PriorityQueue** pQ = new PriorityQueue * [numOfPQ];
    PriorityQueue** pQbackup = new PriorityQueue * [numOfPQ];


    // Tworzymy numOfArrays priorytetowych kolejek
    for (int i = 0; i < numOfPQ; ++i) {
        pQ[i] = new PriorityQueue;
        pQbackup[i] = new PriorityQueue;
    }

    for (int i = 0; i < numOfPQ; i++) {
        pQ[i]->fillFromCSV("random_numbers.csv", "random_numbers_priority.csv", size);
        pQbackup[i]->fillFromCSV("random_numbers.csv", "random_numbers_priority.csv", size);
    }

//    pQ[1]->display();
//    cout << pQ[1]->returnSize() << endl;

    //insert
    auto begin = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < numOfPQ; i++) {
        pQ[i]->insert(5, 5);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    plik_insert.shot(iteration, elapsed.count()/numOfPQ, size);

    //powrot do stanu poczatkowego
    for (int i = 0; i < numOfPQ + 1; i++) {
        pQ[i] = pQbackup[i];
    }

    //extract-max()
    auto begin2 = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < numOfPQ; i++) {
        pQ[i]->extractMax();
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    auto elapsed2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2);
    plik_extract_max.shot(iteration, elapsed2.count()/numOfPQ, size);

    //powrot do stanu poczatkowego
    for (int i = 0; i < numOfPQ-1; i++) {
        delete pQ[i];
    }
    for (int i = 0; i < numOfPQ; i++) {
        pQ[i] = new PriorityQueue;
    }
    for (int i = 0; i < numOfPQ; i++) {
        pQ[i]->fillFromCSV("random_numbers.csv", "random_numbers_priority.csv", size);
    }


    //find max
    auto begin3 = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < numOfPQ; i++) {
        pQ[i]->findMax();
    }
    auto end3 = std::chrono::high_resolution_clock::now();
    auto elapsed3 = std::chrono::duration_cast<std::chrono::microseconds>(end3 - begin3);
    plik_findMax.shot(iteration, elapsed3.count()/numOfPQ, size);


    //modify key
    int val = pQ[0]->getElementAt(5).value;
    auto begin4 = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < numOfPQ; i++) {
        pQ[i]->modifyKey(val, 1000);
    }

    auto end4 = std::chrono::high_resolution_clock::now();
    auto elapsed4 = std::chrono::duration_cast<std::chrono::microseconds>(end4 - begin4);
    plik_modifyKey.shot(iteration, elapsed4.count()/numOfPQ, size);
    for (int i = 0; i < numOfPQ + 1; i++) {
        pQ[i] = pQbackup[i];
    }
}
void runTests(const unsigned numOfArrays) {

    test::generateRandomNumbers(150000, 0, 100000, "random_numbers.csv", 5);
    test::generateRandomNumbers(150000, 0, 100000, "random_numbers_priority.csv", 3);

    char choice3;
    do {
        cout << "1. array_2k" << endl;
        cout << "2. array_4k" << endl;
        cout << "3. array_6k" << endl;
        cout << "4. array_8k" << endl;
        cout << "5. array_10k" << endl;
        cout << "6. array_12k" << endl;
        cout << "7. array_14k" << endl;
        cout << "8. array_16k" << endl;
        cout << "9. array_18k" << endl;
        cout << "X. array_20k" << endl;
        cout << "A. Test all" << endl;
        cout << "0. Exit" << endl;



        cin >> choice3;
        switch (choice3) {
            case '0':
                cout << "Exiting..." << endl;
                break;
            case '1':
            {
                testing(numOfArrays, 2000, 1);
                break;
            }
            case '2':
            {
                testing(numOfArrays, 4000, 2);
                break;
            }
            case '3':
            {
                testing(numOfArrays, 6000, 3);
                break;
            }
            case '4':
            {
                testing(numOfArrays, 8000, 4);
                break;
            }
            case '5':
            {
                testing(numOfArrays, 10000, 5);
                break;
            }
            case '6':
            {
                testing(numOfArrays, 12000, 6);
                break;
            }
            case '7':
            {
                testing(numOfArrays, 14000, 7);
                break;
            }
            case '8':
            {
                testing(numOfArrays, 16000, 8);
                break;
            }
            case '9':
            {
                testing(numOfArrays, 18000, 9);
                break;
            }
            case 'X':
            {
                testing(numOfArrays, 20000, 10);
                break;
            }
            case 'A':
            {
                testing(numOfArrays, 1024, 1);
                testing(numOfArrays, 2048, 2);
                testing(numOfArrays, 4096, 3);
                testing(numOfArrays, 8192, 4);
                testing(numOfArrays, 16384, 5);
                testing(numOfArrays, 32768, 6);
                testing(numOfArrays, 65536, 7);
                testing(numOfArrays, 131072, 8);
//                testing(numOfArrays, 18000, 9);
//                testing(numOfArrays, 20000, 10);
                break;
            }

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice3 != '0');
}


int main() {
    char choice;
    do {
        cout << "Menu:" << endl;
        cout << "1. Your dynamicArray" << endl;
        cout << "2. Tests" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: " << endl;
        cin >> choice;

        switch(choice) {
            case '1':
                //runDynamicArray();
                break;
            case '2':
                cout << "Running tests..." << endl;
                cout << "Please choose the number of priority queues, " << endl;
                int numOfArrays;
                cin >> numOfArrays;
                cout << "Please wait..." << endl;
                runTests(numOfArrays);
                break;
            case '3':
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

    } while (choice != '3');

    return 0;
}