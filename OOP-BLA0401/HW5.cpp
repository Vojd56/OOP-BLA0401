#include <iostream>   // vstup/výstup do konzole
#include <vector>     // dynamické pole (zásobník)
#include <string>     // práce s textem
#include <sstream>    // stringstream – rozdělení stringu
#include <random>     

class Card {
private:
    std::string barva;   // barva karty
    std::string cislo;   // číslo / hodnota karty

public:
    // Konstruktor – vytvoří kartu s danou barvou a číslem
    Card(const std::string& barva, const std::string& cislo)
        : barva(barva), cislo(cislo) {}

    // Vrátí barvu karty
    std::string getBarva() const {
        return barva;
    }

    // Vrátí číslo karty
    std::string getCislo() const {
        return cislo;
    }

    // Vrátí textovou reprezentaci karty (např. "7 Srdce")
    std::string toString() const {
        return cislo + " " + barva;
    }
};
class CardStack {
private:
    // Vnitřní pole zásobníku (poslední prvek = vrchol)
    std::vector<Card> data;

public:
    /*
     * Přidá kartu na vrchol zásobníku
     */
    void push(const Card& card) {
        data.push_back(card);
    }

    /*
     * Odebere a vrátí kartů z vrcholu zásobníku
     */
    Card pop() {
        Card top = data.back(); // vezmeme poslední kartu
        data.pop_back();        // odstraníme ji
        return top;
    }

     // Vrátí kartu z vrcholu bez odebrání

    Card peek() const {
        return data.back();
    }

    void Shuffle() {
        std::random_device rd;    // zdroj náhodnosti
        std::mt19937 gen(rd());   // generátor

        // Jdeme od konce pole směrm na začátek
        for (int i = data.size() - 1; i > 0; i--) {
            // vygenerujeme náhodný index <0, i>
            std::uniform_int_distribution<int> dist(0, i);
            int j = dist(gen);

            // prohodíme karty
            std::swap(data[i], data[j]);
        }
    }

    const std::vector<Card>* getData() const {
        return &data;
    }

    static CardStack* createSevenToAceDeck() {
        CardStack* stack = new CardStack();

        // Stringy s barvami a čísly, oddělené mezerou
        std::string barvy = "Srdce Kary Piky Krize";
        std::string cisla = "7 8 9 10 J Q K A";

        // Rozdělení stringů pomocí stringstream
        std::stringstream ssBarvy(barvy);
        std::stringstream ssCisla(cisla);

        std::vector<std::string> poleBarev;
        std::vector<std::string> poleCisel;

        std::string temp;

        // Naplnění pole barev
        while (ssBarvy >> temp)
            poleBarev.push_back(temp);

        // Naplnění pole čísel
        while (ssCisla >> temp)
            poleCisel.push_back(temp);

        // Vytvoření všech kombinací barva + číslo
        for (const auto& b : poleBarev) {
            for (const auto& c : poleCisel) {
                stack->push(Card(b, c));
            }
        }

        return stack;
    }
};

class CardStackIterator {
private:
    const std::vector<Card>* data; // data zásobníku
    int index;                     // aktuální pozice

public:
    // Konstruktor – přijme pointer na pole karet
    CardStackIterator(const std::vector<Card>* data)
        : data(data), index(0) {}

    /*
     * Vrátí true, pokud existuje další prvek
     */
    bool hasNext() {
        return index < data->size();
    }

    /*
     * Vrátí další kartu a posune index
     */
    Card Next() {
        return (*data)[index++];
    }
};

int main() {
    std::cout << "Vytvarim balicek karet pro hru Prsi...\n\n";

    // Vytvoření balíčku
    CardStack* stack = CardStack::createSevenToAceDeck();

    std::cout << "Micham balicek...\n\n";

    // Zamíchání balíčku
    stack->Shuffle();

    std::cout << "Vypis zamichaneho balicku:\n\n";

    // Vytvoření iterátoru
    CardStackIterator iterator(stack->getData());

    // Výpis všech karet
    while (iterator.hasNext()) {
        Card card = iterator.Next();
        std::cout << card.toString() << std::endl;
    }

    // Uvolnění paměti
    delete stack;
    return 0;
}
