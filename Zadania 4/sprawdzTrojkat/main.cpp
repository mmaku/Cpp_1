#include <iostream>
#include <assert.h>


// ZADANIE 2


bool sprawdzTrojkat(double a, double b, double c)
{
    assert(a > 0 && b > 0 && c > 0);
    if (a>c-b && a>b-c && b>a-c) return(true);
    else return(false);
}

int main()
{
    double bokA, bokB, bokC;

    std::cout << "Podaj długość pierwszego z boków trójkąta: ";
    std::cin >> bokA;
    while (std::cin.fail() || bokA <= 0.0)
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Podana wartość nie jest liczbą dodatnią...\nPodaj liczbę jeszcze raz: ";
        std::cin >> bokA;
    }

    std::cout << "Podaj długość drugiego z boków trójkąta: ";
    std::cin >> bokB;
    while (std::cin.fail() || bokB <= 0.0)
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Podana wartość nie jest liczbą dodatnią...\nPodaj liczbę jeszcze raz: ";
        std::cin >> bokB;
    }

    std::cout << "Podaj długość trzeciego z boków trójkąta: ";
    std::cin >> bokC;

    while (std::cin.fail() || bokC <= 0.0)
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Podana wartość nie jest liczbą dodatnią...\nPodaj liczbę jeszcze raz: ";
        std::cin >> bokC;
    }

    std::cout << "\n";
    if (sprawdzTrojkat(bokA, bokB, bokC)) std::cout << "Z boków o dł.: " << bokA
                                                    << ", " << bokB
                                                    << ", " << bokC
                                                    << " można skonstruować trójkąt.\n";
    else std::cout << "Z boków o dł.: " << bokA
                                        << ", " << bokB
                                        << ", " << bokC
                                        << " nie można skonstruować trójkąta.\n";

    return(0);
}
