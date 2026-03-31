#include <iostream>
#include <stdexcept>

class DynamicArray {
private:
    // 1. Třída DynamicArray, pole celých čísel (int), počítadlo prvků, délka pole (kapacita).
    int* array;
    int elementCount;
    int capacity;
    static const int defaultSize = 10; // statická konstanta výchozí velikosti pro konstruktor bez parametrů

public:
    // 2. a. Konstruktor bez parametrů. Vytvoří se prázdné pole o výchozí velikosti.
    DynamicArray() {
        capacity = defaultSize;
        elementCount = 0;
        array = new int[capacity];
    }

    // 2. b. Konstruktor s parametrem n, vytvoří prázdné pole o velikosti n.
    DynamicArray(int n) {
        capacity = n;
        elementCount = 0;
        array = new int[capacity];
    }

    // 2. c. Konstruktor pro zkopírování pole, vytvoří pole o dvojnásobné velikosti length a zkopíruje prvky z arr.
    DynamicArray(int* arr, int length) {
        capacity = length * 2;
        elementCount = length;
        array = new int[capacity];
        for (int i = 0; i < length; i++) {
            array[i] = arr[i];
        }
    }

    ~DynamicArray() {
        delete[] array;
    }

    // 1. Metoda pro přístup k jednotlivým prvkům v poli.
    int getAt(int index) {
        if (index < 0 || index >= elementCount) {
            throw std::out_of_range("Index out of range");
        }
        return array[index];
    }

    // 1. Metoda pro nastavení hodnoty pro jednotlivý prvek v poli.
    void setAt(int index, int value) {
        if (index < 0 || index >= elementCount) {
            throw std::out_of_range("Index out of range");
        }
        array[index] = value;
    }

    // 3. Metoda void Add(int number), která vloží prvek za poslední prvek v poli a případně pole zdvojnásobí.
    void Add(int number) {
        if (elementCount == capacity) {
            capacity = capacity == 0 ? 1 : capacity * 2;
            int* newArray = new int[capacity];
            for (int i = 0; i < elementCount; i++) {
                newArray[i] = array[i];
            }
            delete[] array;
            array = newArray;
        }
        array[elementCount] = number;
        elementCount++;
    }

    // 4. Metoda int removeAt(unsigned int index), vymaže prvek a posune všechny prvky za ním o index níže, vrací smazaný prvek.
    int removeAt(unsigned int index) {
        if (index >= (unsigned int)elementCount) {
            throw std::out_of_range("Index out of range");
        }
        int removedValue = array[index];
        for (unsigned int i = index; i < (unsigned int)elementCount - 1; i++) {
            array[i] = array[i + 1];
        }
        elementCount--;
        return removedValue;
    }
};

int main() {
    std::cout << "--- Testovani DynamicArray ---\n";

    DynamicArray arr1;
    for (int i = 0; i < 15; i++) {
        arr1.Add(i * 10);
    }

    std::cout << "Prvek na indexu 5: " << arr1.getAt(5) << "\n";
    arr1.setAt(5, 999);
    std::cout << "Prvek na indexu 5 po setAt: " << arr1.getAt(5) << "\n";

    int removed = arr1.removeAt(5);
    std::cout << "Odstraneny prvek z indexu 5: " << removed << "\n";
    std::cout << "Novy prvek na indexu 5 po posunuti: " << arr1.getAt(5) << "\n";

    int initArr[] = { 1, 2, 3, 4, 5 };
    DynamicArray arr2(initArr, 5);
    std::cout << "Prvky v poli z konstruktoru s parametrem pole:\n";
    for (int i = 0; i < 5; i++) {
        std::cout << arr2.getAt(i) << " ";
    }
    std::cout << "\n";

    return 0;
}
