#include <iostream>
#include <sstream>
#include <cmath>
#include <cassert>

const double DOKLADNOSC = 1e-6;

bool equal(double X, double Y)
{
    return fabs(X-Y) < DOKLADNOSC;
}

class Zespolona
{
    public:
        Zespolona (double Re = 0.0, double Im = 0.0): Re_(Re), Im_(Im), abs_(sqrt(Re * Re + Im * Im))
            {
                if (equal(Re, 0.0) && equal(Im, 0.0))
                    arg_ = 0.0;
                else
                    arg_ = asin(Im / sqrt(Re * Re + Im * Im));
            }

        double Re() {return Re_;}
        double Im() {return Im_;}
        double Abs() {return abs_;}
        double Arg() {return arg_;}

        std::string tekst()
        {
            std::ostringstream wy;
            wy << Re_ << std::showpos << Im_ << 'i';
            return wy.str();
        }

    private:
        double Re_;
        double Im_;
        double abs_;
        double arg_;

};

std::ostream& operator<<(std::ostream& wy, Zespolona liczba)
{
    wy << liczba.tekst();
    return wy;
}

std::istream& operator>>(std::istream& in, Zespolona &liczba)
{
    char i = char(0), znak = char(0);
    double real = 0.0;
    double imag = 0.0;
    in >> std::skipws >> real >> znak >> imag >> i;
    if (in && i == 'i' && (znak == '+' || znak == '-')) {
        if (znak == '-' && !equal(0, imag)) imag = -imag;
        liczba = Zespolona(real, imag);
    } else {
        in.setstate(std::ios_base::failbit);
    }
    return in;
}

void test_Zespolona(void)
{
    Zespolona a(2.14,-2.71);
    assert(equal(a.Re(), 2.14));
    assert(equal(a.Im(), -2.71));
    assert(equal(a.Abs(), 3.453071096));
    assert(equal(a.Arg(), -0.902387));
    std::ostringstream awy;
    awy << a.tekst();
    assert(awy.str()=="2.14-2.71i");

    Zespolona b(2.14,2.71);
    assert(equal(b.Re(), 2.14));
    assert(equal(b.Im(), 2.71));
    assert(equal(b.Abs(), 3.453071096));
    assert(equal(b.Arg(), 0.902387));
    std::ostringstream bwy;
    bwy << b.tekst();
    assert(bwy.str()=="2.14+2.71i");

    Zespolona c;
    assert(equal(c.Im(), 0.0));
    assert(equal(c.Re(), 0.0));
    assert(equal(c.Arg(), 0.0));
    assert(equal(c.Abs(), 0.0));

    Zespolona d(3.2, 1.2);
    assert(equal(d.Im(), 1.2));
    assert(equal(d.Re(), 3.2));
    assert(equal(d.Arg(), 0.358771));
    assert(equal(d.Abs(), 3.4176014981));

    Zespolona e(4);
    assert(equal(e.Im(), 0.0));
    assert(equal(e.Re(), 4.0));
    assert(equal(e.Arg(), 0.0));
    assert(equal(e.Abs(), 4.0));

    Zespolona f;
    std::istringstream fwe("2.35-4i");
    fwe >> f;
    assert(equal(f.Im(), -4.0));
    assert(equal(f.Re(), 2.35));
    assert(equal(f.Arg(), -1.039619));
    assert(equal(f.Abs(), 4.639234));
}

 Zespolona pobieranieZmiennych (std::string polecenie)
 {
    std::string wejscie;
    Zespolona liczba;

    std::cout << polecenie;
    std::getline(std::cin, wejscie);
    std::istringstream strumien(wejscie);
    strumien >> liczba;

    while (!strumien)
    {
        strumien.ignore(1000, '\n');
        strumien.clear();
        std::cout << "Podana wartość nie jest liczbą zespoloną."
                  << "\nPodaj liczbę jeszcze raz: ";
        std::getline(std::cin, wejscie);
        strumien.str (wejscie);
        strumien >> liczba;
    }

    std::cout << '\n';
    return(liczba);
 }

int main()
{
    test_Zespolona();
    Zespolona A = pobieranieZmiennych("Podaj liczbę zespoloną w formacie a+bi: ");
    std::cout << "Podana przez Ciebie liczba to " << A.tekst() << '\n' << '\n'
              << "Współrzędne biegunowe:\nargument: " << A.Arg() << " (w radianach)\nmoduł: " << A.Abs() << '\n';
    return 0;
}
