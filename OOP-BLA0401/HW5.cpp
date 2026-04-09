#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <random>

class Card {
public:
    std::string barva;
    std::string cislo;

    Card() {}

    Card(const std::string& b, const std::string& c)
        : barva(b), cislo(c) {}

    std::string toString() const {
        return cislo + " " + barva;
    }
};

class DynamicArray {
private:
    Card* array;          
    int elementCount;     
    int capacity;    
    static const int defaultSize = 10;

public:
    // Konstruktor bez parametrů
    DynamicArray() {
        capacity = defaultSize;
        elementCount = 0;
        array = new Card[capacity];
    }

    // Destruktor
    ~DynamicArray() {
        delete[] array;
    }

    // Vrátí prvek na indexu
    Card getAt(int index) const {
        if (index < 0 || index >= elementCount)
            throw std::out_of_range("Index mimo rozsah");
        return array[index];
    }

    // Nastaví prvek na indexu
    void setAt(int index, const Card& value) {
        if (index < 0 || index >= elementCount)
            throw std::out_of_range("Index mimo rozsah");
        array[index] = value;
    }

    // Přidání prvku na konec pole
    void Add(const Card& value) {
        if (elementCount == capacity) {
            capacity *= 2;
            Card* newArray = new Card[capacity];
            for (int i = 0; i < elementCount; i++)
                newArray[i] = array[i];
            delete[] array;
            array = newArray;
        }
        array[elementCount++] = value;
    }

    // Odebrání prvku na indexu
    Card removeAt(int index) {
        if (index < 0 || index >= elementCount)
            throw std::out_of_range("Index mimo rozsah");

        Card removed = array[index];
        for (int i = index; i < elementCount - 1; i++)
            array[i] = array[i + 1];

        elementCount--;
        return removed;
    }

    int size() const {
        return elementCount;
    }

    // Přístup pro iterátor
    Card* getRawArray() const {
        return array;
    }
};

class CardStack {
private:
    DynamicArray data;

public:
    // push – přidání karty
    void push(const Card& card) {
        data.Add(card);
    }

    // pop – odebrání karty z vrcholu
    Card pop() {
        return data.removeAt(data.size() - 1);
    }

    // peek – nahlédnutí na vrchol
    Card peek() const {
        return data.getAt(data.size() - 1);
    }

    void Shuffle() {
        std::random_device rd;
        std::mt19937 gen(rd());

        for (int i = data.size() - 1; i > 0; i--) {
            std::uniform_int_distribution<int> dist(0, i);
            int j = dist(gen);

            Card tmp = data.getAt(i);
            data.setAt(i, data.getAt(j));
            data.setAt(j, tmp);
        }
    }

    static CardStack* createSevenToAceDeck() {
        CardStack* stack = new CardStack();

        std::string barvy = "Srdce Kary Piky Krize";
        std::string cisla = "7 8 9 10 J Q K A";

        std::stringstream ssBarvy(barvy);
        std::stringstream ssCisla(cisla);

        std::string b, c;

        while (ssBarvy >> b) {
            std::stringstream tempCisla(cisla);
            while (tempCisla >> c) {
                stack->push(Card(b, c));
            }
        }

        return stack;
    }

    // Pro iterátor
    DynamicArray* getData() {
        return &data;
    }
};

class CardStackIterator {
private:
    DynamicArray* data;
    int index;

public:
    CardStackIterator(DynamicArray* d)
        : data(d), index(0) {}

    bool hasNext() {
        return index < data->size();
    }

    Card Next() {
        return data->getAt(index++);
    }
};

int main() {
    std::cout << "Vytvarim balicek pro hru Prsi...\n\n";

    CardStack* stack = CardStack::createSevenToAceDeck();

    std::cout << "Micham balicek...\n\n";
    stack->Shuffle();

    std::cout << "Vypis zamichaneho balicku:\n\n";

    CardStackIterator it(stack->getData());

    while (it.hasNext()) {
        std::cout << it.Next().toString() << std::endl;
    }

    delete stack;
    return 0;
}
