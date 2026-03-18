#include <iostream>

class Set {
private:
    int* array;
    int length; // kapacita
    int count;  // aktualni pocet prvku

    // Pomocná metoda pro kontrolu existence prvku v množině
    bool contains(int value) const {
        for (int i = 0; i < count; i++) {
            if (array[i] == value) {
                return true;
            }
        }
        return false;
    }

public:
    // Konstruktor s určením kapacity (length), ve kterém alokujeme pamět pro pole
    Set(int capacity) {
        length = capacity;
        count = 0;
        array = new int[length];
    }

    // Destruktor pro uvolnění dynamicky alokovaného pole
    ~Set() {
        delete[] array;
    }

    // Metoda pro získání počtu prvků
    int getCount() const {
        return count;
    }

    // Metoda pro získání prvku na daném indexu
    int getAt(int i) const {
        if (i >= 0 && i < count) {
            return array[i];
        }
        return -1; // Vracíme -1 jako indikační hodnotu při neplatném indexu
    }

    // Metoda pro vložení prvků do množiny (respektuje požadavek unikátnosti prvků)
    bool insert(int value) {
        if (count < length) {
            if (!contains(value)) {
                array[count] = value;
                count++;
                return true;
            }
        }
        else {
            std::cout << "Kapacita mnoziny byla vycerpana pro prvek: " << value << "\n";
        }
        return false;
    }

    // 2. Metoda pro sjednocení dvou množin.
    Set* unionSet(Set* secondSet) {
        // Velikost bude rovna součtu počtu prvků v obou množinách
        int newLength = this->count + secondSet->getCount();
        Set* newSet = new Set(newLength);

        // Nakopírování první množiny
        for (int i = 0; i < this->count; i++) {
            newSet->insert(this->getAt(i));
        }

        // Nakopírování druhé množiny (metoda insert sama zařídí unikátnost prvků)
        for (int i = 0; i < secondSet->getCount(); i++) {
            newSet->insert(secondSet->getAt(i));
        }

        return newSet;
    }

    // 3. Metoda pro získání doplňku dvou objektů Set
    Set* complement(Set* secondSet) {
        // Kapacita bude rovna kapacite objektu Set, na který byla metoda zavolána
        Set* newSet = new Set(this->length);

        for (int i = 0; i < this->count; i++) {
            int currentVal = this->getAt(i);
            // Vlozíme prvky, které jsou v první množině, ale nejsou ve druhé
            if (!secondSet->contains(currentVal)) {
                newSet->insert(currentVal);
            }
        }

        return newSet;
    }
};

int main() {
    // Vytvoreni prvni mnoziny s kapacitou 10
    Set setA(10);
    setA.insert(1);
    setA.insert(2);
    setA.insert(3);
    setA.insert(4);

    // Vytvoreni druhe mnoziny s kapacitou 10
    Set setB(10);
    setB.insert(3);
    setB.insert(4);
    setB.insert(5);
    setB.insert(6);

    // Test sjednoceni
    Set* unionResult = setA.unionSet(&setB);
    std::cout << "Sjednoceni: ";
    for (int i = 0; i < unionResult->getCount(); i++) {
        std::cout << unionResult->getAt(i) << " ";
    }
    std::cout << std::endl;

    // Test doplnku (setA \ setB)
    Set* complementResult = setA.complement(&setB);
    std::cout << "Doplnek (setA bez setB): ";
    for (int i = 0; i < complementResult->getCount(); i++) {
        std::cout << complementResult->getAt(i) << " ";
    }
    std::cout << std::endl;

    // Uvolneni pameti
    delete unionResult;
    delete complementResult;

    return 0;
}