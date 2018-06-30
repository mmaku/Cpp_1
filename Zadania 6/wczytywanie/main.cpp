#include <iostream>
#include <sstream>



 int pobieranieZmiennych (std::string polecenie)
 {
    std::string wejscie;
    int liczba = 0;

    std::cout << polecenie;
    std::cin >> wejscie;
    std::istringstream strumien(wejscie);
    strumien >> liczba;

    while (strumien.fail())
    {
        strumien.clear();
        std::cout << "Podana wartość nie jest liczbą."
                  << "\nPodaj liczbę jeszcze raz: ";
        std::cin >> wejscie;
        strumien.str (wejscie);
        strumien >> liczba;
    }

    std::cout << '\n';
    return(liczba);
 }


int main()
{
    std::cout << "Podana liczba: " << pobieranieZmiennych("Podaj liczbę: ") << '\n';
    return 0;
}
