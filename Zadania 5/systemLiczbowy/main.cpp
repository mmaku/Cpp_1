#include <iostream>
#include <sstream>
#include <cassert>

std::string zamiana(int liczba, int podstawa)
{
    std::string wyjscie, znak;
    if (liczba == 0) return "0";
    if (liczba < 0) {
        znak = "-";
        liczba = -liczba;
    }
    while (liczba) {
        int liczbaPoZamianie = liczba % podstawa;
        if (liczbaPoZamianie < 10) {
            wyjscie = char('0' + liczbaPoZamianie) + wyjscie;
        } else {
            wyjscie = char('A' + liczbaPoZamianie - 10) + wyjscie;
        }
        liczba = liczba / podstawa;
    }
    return znak + wyjscie;
}

void test_zamiana()
{
    assert(zamiana(23, 24) == "N");
    assert(zamiana(255, 16) == "FF");
    assert(zamiana(0, 17) == "0");
    assert(zamiana(-8, 2) == "-1000");
}

int main()
{
    test_zamiana();

    int podstawa = 0, liczba = 0;
    std::cout << "Podaj podstawę systemu liczbowego: ";
    std::cin >> podstawa;
    while (std::cin.fail() || podstawa < 2 || podstawa > 36)
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Podana wartość nie jest liczbą całkowitą\nz zakresu [2, 36]..."
                 << "\nPodaj podstawę jeszcze raz: ";
        std::cin >> podstawa;
    }

    std::cout << "Podaj liczbę, która chcesz przekonwertować: ";
    std::cin >> liczba;
    while (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Podana wartość nie jest liczbą całkowitą\nz zakresu [-2 147 483 647, 2 147 483 647]..."
                 << "\nPodaj liczbę jeszcze raz: ";
        std::cin >> liczba;
    }

    std::cout << zamiana(liczba, podstawa) << "\n";
    return 0;
}
