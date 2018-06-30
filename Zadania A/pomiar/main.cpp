#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <sstream>
#include <fstream>

const double DOKLADNOSC = 1e-2;

bool equal(double X, double Y)
{
    return fabs(X-Y) < DOKLADNOSC;
}

class Pomiar
{
    private:
        double czas_ = 0.0;
        double polozenie_ = 0.0;

    public:
        Pomiar(double czas = 0.0, double polozenie = 0.0)
            : czas_(czas), polozenie_(polozenie)
            {};

        double Polozenie() const;
        double Czas() const;

};

double Pomiar::Polozenie() const
{
  return polozenie_;
}

double Pomiar::Czas() const
{
  return czas_;
}

std::istream& operator>>(std::istream& WE, Pomiar& P)
{
      std::ios_base::fmtflags flagi = WE.flags() | std::ios::skipws;
    char N1 = ' ';
    char N2 = ' ';
    char sep = ' ';
    double polozenie = 0.0;
    double czas = 0.0;
    if (WE.eof())
        return WE;
    WE >> N1 >> std::skipws >> czas >> sep >> polozenie >> N2 >> std::ws;
    if (WE)
    {
        if (N1 == '(' && sep == ';' && N2 == ')')
            P = Pomiar(czas, polozenie);
        else if (WE && WE.eof())
        {
        }
        else
        {
            WE.setstate(std::ios_base::failbit);
        }
    }
    if (!flagi)
        WE >> std::noskipws;

    return WE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SeriaPomiarowa
{
    private:
        std::vector<Pomiar> pomiary_;
        long long liczba_pomiarow_;

    public:
        explicit SeriaPomiarowa(std::vector<Pomiar> pomiary=std::vector<Pomiar>())
            : pomiary_(pomiary), liczba_pomiarow_(pomiary.size())
            {};

        Pomiar operator[](const long long& i) const;
        double Predkosc(const long long& indeks) const;
        double Przyspieszenie(const long long& indeks) const;
        long long LiczbaPomiarow() const;

};

Pomiar SeriaPomiarowa::operator[](const long long& indeks) const
{
    return pomiary_[indeks];
}

double SeriaPomiarowa::Predkosc(const long long& indeks) const
{
    assert(indeks > 0 && indeks < liczba_pomiarow_);
    return ((pomiary_[indeks+1].Polozenie() - pomiary_[indeks-1].Polozenie())
          / (pomiary_[indeks+1].Czas() - pomiary_[indeks-1].Czas()));
}

double SeriaPomiarowa::Przyspieszenie(const long long& indeks) const
{
    assert(indeks > 0 && indeks < liczba_pomiarow_);
    return 2 * (((pomiary_[indeks].Czas() - pomiary_[indeks-1].Czas())
             * (pomiary_[indeks+1].Polozenie() - pomiary_[indeks].Polozenie()))
             - ((pomiary_[indeks+1].Czas() - pomiary_[indeks].Czas())
             * (pomiary_[indeks].Polozenie() - pomiary_[indeks-1].Polozenie())))
             / (pomiary_[indeks+1].Czas() - pomiary_[indeks-1].Czas());
}

long long SeriaPomiarowa::LiczbaPomiarow() const
{
    return liczba_pomiarow_;
}

std::ostream& operator<<(std::ostream& WY, const SeriaPomiarowa& seria)
{
    for (int i = 0; i < seria.LiczbaPomiarow(); ++i)
    {
        WY << seria[i].Czas() << ';' << seria[i].Polozenie();
        if (0 < i &&  i < seria.LiczbaPomiarow() - 1)
            WY << ';' << seria.Predkosc(i) << ';' << seria.Przyspieszenie(i);
        else
            WY << ";;";
        WY << '\n';
    }
    return WY;
}


std::istream& operator>>(std::istream& WE, SeriaPomiarowa& seria)
{
    std::vector<Pomiar> pomiary;
    Pomiar temp;
    int licznik = 1;
    while (WE >> temp)
    {
        std::cerr << "wczytanie nr " << licznik << "...\n";
        pomiary.push_back(temp);
        if (WE.eof()) break;
        licznik++;
    }
    if (WE)
        seria = SeriaPomiarowa(pomiary);
    return WE;
}

bool operator==(const SeriaPomiarowa& S1, const SeriaPomiarowa& S2)
{
    bool wyjscie = true;
    if(S1.LiczbaPomiarow() != S2.LiczbaPomiarow())
        wyjscie = false;
    else
        for (long long i = 0; i < S1.LiczbaPomiarow(); ++i)
            wyjscie &= (equal(S1[i].Czas(), S2[i].Czas()) && equal(S1[i].Polozenie(), S2[i].Polozenie()));
    return wyjscie;
}

void test_SeriaPomiarowa();

int main()
{
    test_SeriaPomiarowa();
    return 0;
}

void test_SeriaPomiarowa()
{
    std::istringstream WE("  (12; 3.14 )   \n\n (   12.52; 2.54)\n"
                          "  (13.14   ; \n\n 7.32)   (\n14.15; 10.1 )\n\n\n");
    SeriaPomiarowa S1;
    WE >> S1;
    SeriaPomiarowa S2{std::vector<Pomiar>{{12.0, 3.14}, {12.52, 2.54}, {13.14, 7.32}, {14.15, 10.1}}};
    assert (S1 == S2);
    std::ofstream WY("pomiary.txt");
    WY << S1;

    std::istringstream WE2("  (12; 3.14 )   \n\n (   12.52; 2.54)\n"
                          "  (13.14   ; \n\n 7.32)   (\n14.15; 10.1 )dsadasdasdsa\n\n\ndd");
    SeriaPomiarowa S3;
    WE2 >> S3;
    assert(!WE2);

    std::istringstream WE3("  (12; 3.14 )   \n\n (   12.52; 2.54)\n"
                          "  (13.14   ; \n\n 7.32)   (\n14.15; 10.1 )\n\n\ndsdasdasdsadasd");
    SeriaPomiarowa S4;
    WE3 >> S4;
    assert(!WE3);

    std::cerr << "test_SeriaPomiarowa ok\n";
}
