#include <iostream>
#include <sstream>
#include <assert.h>

struct Zespolona
{
    double Re;
    double Im;
    Zespolona (double R = 0.0, double I = 0.0): Re(R), Im(I)
        {
        }

};

std::ostream& operator<<(std::ostream& wy, Zespolona liczba)
{
    wy << liczba.Re << std::showpos << liczba.Im << 'i';
    return wy;
}

std::istream& operator>>(std::istream& in, Zespolona &liczba)
{
    char i = char(0);
    double real = 0.0;
    double imag = 0.0;
    in >> real >> imag >> i;
    if (in)
        liczba = Zespolona(real, imag);
    return in;
}

void test_Zespolona(void)
{
    Zespolona a(2.14,-2.71);
    assert(a.Re == 2.14);
    assert(a.Im == -2.71);
    std::ostringstream awy;
    awy << a;
    assert(awy.str()=="2.14-2.71i");
    Zespolona b(2.14,2.71);
    assert(b.Re == 2.14);
    assert(b.Im == 2.71);
    std::ostringstream bwy;
    bwy << b;
    assert(bwy.str()=="2.14+2.71i");
}

 Zespolona pobieranieZmiennych (std::string polecenie)
 {
    std::string wejscie;
    Zespolona liczba;

    std::cout << polecenie;
    std::getline(std::cin, wejscie);
    std::istringstream strumien(wejscie);
    strumien >> std::skipws >> liczba;

    while (!strumien)
    {
        strumien.ignore(1000, '\n');
        strumien.clear();
        std::cout << "Podana wartość nie jest liczbą zespoloną."
                  << "\nPodaj liczbę jeszcze raz: ";
        std::getline(std::cin, wejscie);
        strumien.str (wejscie);
        strumien >> std::skipws >> liczba;
    }

    std::cout << '\n';
    return(liczba);
 }

int main()
{
    test_Zespolona();
    Zespolona A = pobieranieZmiennych("Podaj liczbę zespoloną w formacie a+bi: ");
    std::cout << "Podana przez Ciebie liczba to " << A << '\n';
    return 0;
}
