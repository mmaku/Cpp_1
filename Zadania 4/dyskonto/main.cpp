#include <iostream>
#include <math.h>
#include <assert.h>


// ZADANIE 4


double czynnikKap (double stopaProcentowa, int lata)
{
    assert(lata >= 0);
    double czynnik=1;
    stopaProcentowa=stopaProcentowa/100.0;
    return(czynnik=pow(1+stopaProcentowa,lata));
}

int main()
{
    double lata = -1.0, stopaProcentowa = 100.0, kapital = 0.0;
    std::string czas=" latach, ", zmiana=" uróśł do ";

    std::cout << "Podaj nieujemny czas trawnia umowy w latach\n(przy podaniu liczby niecałkowitej zostanie on zaokrąglony w dół): ";
    std::cin >> lata;
    lata=floor(lata);
    while (std::cin.fail() || lata <= 0.0)
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        if (lata==0.0) std::cout << "Czy jest sens zakładać lokatę na zerowy czas?\nPodaj czas jeszcze raz: ";
        else std::cout << "Podana wartość nie jest liczbą nieujemną...\nPodaj czas jeszcze raz: ";
        std::cin >> lata;
    }

    std::cout << "\n";
    std::cout << "Podaj stopę procentową (np. dla 5% wpisz 5): ";
    std::cin >> stopaProcentowa;
    while (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Podana wartość nie jest liczbą...\nPodaj stopę jeszcze raz: ";
        std::cin >> stopaProcentowa;
    }

    std::cout << "\n";
    std::cout << "Podaj kapitał startowy: ";
    std::cin >> kapital;
    while (std::cin.fail() || kapital < 0)
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Podana wartość nie jest liczbą nieujemnną...\nPodaj kapitał jeszcze raz: ";
        std::cin >> kapital;
    }

    if (lata==1) czas = " roku, ";
    if (stopaProcentowa<0) zmiana = " zmalał do ";
    if (stopaProcentowa==0) zmiana = " nie zmienił się i nadal jest równy ";

    std::cout << "\n";
    std::cout << "Po " << lata << czas << "przy oprocentowaniu " << stopaProcentowa <<"%,\nnasz kapitał" << zmiana << czynnikKap(stopaProcentowa, lata)*kapital << "\n";
    return(0);
}
