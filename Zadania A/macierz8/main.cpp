#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

const int  Wymiar = 8;
const double DOKLADNOSC = 1e-6;

bool equal(const double& a, const double& b)
{
    return fabs(a-b) < DOKLADNOSC;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Wektor8
{
    private:
        std::vector<double> wektor_;

    public:
        Wektor8(std::vector<double> wektor = std::vector<double>(Wymiar, 0.0))
        {
            wektor.resize(Wymiar, 0.0);
            wektor_ = wektor;
        }

    double operator[](int indeks) const;
    double& operator[](int indeks);
    Wektor8& operator+=(Wektor8 W);
};

double Wektor8::operator[](int indeks) const
{
    assert(1 <= indeks && indeks <= Wymiar);
    return wektor_[indeks-1];
}

double& Wektor8::operator[](int indeks)
{
    assert(1 <= indeks && indeks <= Wymiar);
    return wektor_[indeks-1];
}

Wektor8& Wektor8::operator+=(Wektor8 W)
{
    for(int i=1; i <= Wymiar; i++)
    {
        wektor_[i-1] += W[i];
    }
    return *this;
}

Wektor8 operator+(const Wektor8& W1, const Wektor8& W2)
{
    Wektor8 WY(W1);
    WY+=W2;
    return WY;
}

double operator*(const Wektor8& W1,const Wektor8& W2)
{
    double wynik = 0.0;
    for(int i=1; i <= Wymiar; i++)
    {
        wynik += W1[i]*W2[i];
    }
    return wynik;
}

bool operator==(const Wektor8& W1, const Wektor8& W2)
{
    bool wyjscie = true;
    for(int i=1; i <= Wymiar; i++)
        wyjscie &= equal(W1[i],W2[i]);
    return wyjscie;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Wspolrzedne
{
    private:
        int i_ = 1;
        int j_ = 1;
    public:
        Wspolrzedne(int i = 1, int j = 1)
            : i_(i), j_(j)
            {
                assert(1 <= i && i <= Wymiar);
                assert(1 <= j && j <= Wymiar);
            }

        double i() const;
        double j() const;
};

double Wspolrzedne::i() const
{
    return i_;
}

double Wspolrzedne::j() const
{
    return j_-1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Macierz8
{
    private:
        std::vector<Wektor8> macierz_;

    public:
        Macierz8(std::vector<Wektor8> macierz = std::vector<Wektor8>())
        {
            macierz.resize(Wymiar);
            for (int i = 0; i < Wymiar; ++i)
            {
                std::vector<double> temp;
                for(int j = 1; j <= Wymiar; j++)
                {
                    temp.push_back(macierz[i][j]);
                }
                macierz[i] = Wektor8(temp);
            }
            macierz_ = macierz;
        }

    double operator[](Wspolrzedne wsp) const;
    double& operator[](Wspolrzedne wsp);
    Wektor8 Wiersz(int W) const;
    Wektor8 Kolumna(int K) const;
    Macierz8& operator+=(Macierz8 M);
    Macierz8& operator*=(Macierz8 M);
    Macierz8& operator=(Macierz8 M);

};

double Macierz8::operator[](Wspolrzedne wsp) const
{
    return macierz_[wsp.j()][wsp.i()];
}

double& Macierz8::operator[](Wspolrzedne wsp)
{
    return macierz_[wsp.j()][wsp.i()];
}

Wektor8 Macierz8::Wiersz(int K) const
{
    assert(1 <= K && K <= Wymiar);
    std::vector<double> kolumna;
    for (int i = 0; i < Wymiar; ++i)
        kolumna.push_back(macierz_[i][K]);

    return Wektor8(kolumna);
}

Wektor8 Macierz8::Kolumna(int W) const
{
  assert(1 <= W && W <= Wymiar);

  return macierz_[W-1];
}

Macierz8& Macierz8::operator+=(Macierz8 M)
{
    for (int i = 1; i <= Wymiar; ++i)
    {
        for (int j = 0; j < Wymiar; ++j)
        {
            macierz_[j][i] += M[{i,j+1}];
        }
    }

    return *this;
}

Macierz8& Macierz8::operator*=(Macierz8 M)
{
    std::vector<Wektor8> wynik(Wymiar, Wektor8());
    for (int i = 1; i <= Wymiar; ++i)
    {
        for (int j = 0; j < Wymiar; ++j)
        {
            wynik[j][i] = Wiersz(i) * M.Kolumna(j+1);
        }
    }
    macierz_ = wynik;

    return *this;
}

Macierz8& Macierz8::operator=(Macierz8 M)
{
    for (int i = 1; i <= Wymiar; ++i)
    {
        for (int j = 0; j < Wymiar; ++j)
        {
            macierz_[j][i] = M[{i, j+1}];
        }
    }
    return *this;
}

Macierz8 operator+(const Macierz8& M1, const Macierz8& M2)
{
    Macierz8 WY(M1);
    WY+=M2;
    return WY;
}

Macierz8 operator*(const Macierz8& M1, const Macierz8& M2)
{
    Macierz8 WY(M1);
    WY*=M2;
    return WY;
}

bool operator==(const Macierz8& M1, const Macierz8& M2)
{
    bool wyjscie = true;
    for(int i=1; i <= Wymiar; i++)
        for(int j=1; j <= Wymiar; j++)
            wyjscie &= equal(M2[{i,j}],M1[{i,j}]);
    return wyjscie;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Wektor8 operator*(const Macierz8& M, const Wektor8& W)
{
    std::vector<double> wyjscie;
    for(int i = 1; i <= Wymiar; i++)
        {
            Wektor8 temp(M.Wiersz(i));
            wyjscie.push_back(temp*W);
        }
    return Wektor8(wyjscie);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void test_Macierz();

int main()
{
    test_Macierz();
    return 0;
}

void test_Macierz()
{
    std::vector<double> first (2,1);
    std::vector<double> second (2,2);
    Wektor8 W1(first);
    Wektor8 W2(second);
//    std::cerr << W1[1] << ' ' << W2[1] << '\n'
//              << W1[2] << ' ' << W2[2] << '\n'
//              << W1[3] << ' ' << W2[3] << '\n'
//              << W1[4] << ' ' << W2[4] << "\n\n";


    std::vector<Wektor8> W3;
    W3.push_back(W1);
    W3.push_back(W2);
    Macierz8 M1(W3);
//    std::cerr << (M1)[{1,1}] << ' ' << (M1)[{1,2}] << ' ' << (M1)[{1,3}] << '\n'
//              << (M1)[{2,1}] << ' ' << (M1)[{2,2}] << ' ' << (M1)[{2,3}] << '\n'
//              << (M1)[{3,1}] << ' ' << (M1)[{3,2}] << ' ' << (M1)[{3,3}] << "\n\n";

    std::vector<Wektor8> W4;
    W4.push_back(W2);
    W4.push_back(W1);
    Macierz8 M2(W4);
//    std::cerr << (M2)[{1,1}] << ' ' << (M2)[{1,2}] << ' ' << (M2)[{1,3}] << '\n'
//              << (M2)[{2,1}] << ' ' << (M2)[{2,2}] << ' ' << (M2)[{2,3}] << '\n'
//              << (M2)[{3,1}] << ' ' << (M2)[{3,2}] << ' ' << (M2)[{3,3}] << "\n\n";


    first.clear();
    second.clear();
    first.push_back(3);
    first.push_back(3);
    second.push_back(3);
    second.push_back(3);
    Wektor8 W5(first);
    Wektor8 W6(second);
    W3.clear();
    W3.push_back(W5);
    W3.push_back(W6);
    Macierz8 M3(W3);
//    std::cerr << (M1+M2)[{1,1}] << ' ' << (M1+M2)[{1,2}] << ' ' << (M1+M2)[{1,3}] << '\n'
//              << (M1+M2)[{2,1}] << ' ' << (M1+M2)[{2,2}] << ' ' << (M1+M2)[{2,3}] << '\n'
//              << (M2+M1)[{3,1}] << ' ' << (M2+M1)[{3,2}] << ' ' << (M2+M1)[{3,3}] << "\n\n";

    assert(M1+M2==M3);

    first.clear();
    second.clear();
    first.push_back(3);
    first.push_back(3);
    second.push_back(6);
    second.push_back(6);
    Wektor8 W7(first);
    Wektor8 W8(second);
    W3.clear();
    W3.push_back(W7);
    W3.push_back(W8);
    Macierz8 M4(W3);
//    std::cerr << (M2*M1)[{1,1}] << ' ' << (M2*M1)[{1,2}] << ' ' << (M2*M1)[{1,3}] << '\n'
//              << (M2*M1)[{2,1}] << ' ' << (M2*M1)[{2,2}] << ' ' << (M2*M1)[{2,3}] << '\n'
//              << (M2*M1)[{3,1}] << ' ' << (M2*M1)[{3,2}] << ' ' << (M2*M1)[{3,3}] << "\n\n";
//
//    std::cerr << (M1*M2)[{1,1}] << ' ' << (M1*M2)[{1,2}] << ' ' << (M1*M2)[{1,3}] << '\n'
//              << (M1*M2)[{2,1}] << ' ' << (M1*M2)[{2,2}] << ' ' << (M1*M2)[{2,3}] << '\n'
//              << (M1*M2)[{3,1}] << ' ' << (M1*M2)[{3,2}] << ' ' << (M1*M2)[{3,3}] << "\n\n";
//
//    std::cerr << (M4)[{1,1}] << ' ' << (M4)[{1,2}] << ' ' << (M4)[{1,3}] << '\n'
//              << (M4)[{2,1}] << ' ' << (M4)[{2,2}] << ' ' << (M4)[{2,3}] << '\n'
//              << (M4)[{3,1}] << ' ' << (M4)[{3,2}] << ' ' << (M4)[{3,3}] << "\n\n";

    assert(M2*M1==M4);

    first.clear();
    second.clear();
    first.push_back(1);
    first.push_back(2);
    second.push_back(15);
    second.push_back(15);
    Wektor8 W9(first);
    Wektor8 W10(second);
    assert(M4*W9==W10);
//    std::cerr << (M4*W9)[1] << ' ' << W10[1] << '\n'
//              << (M4*W9)[2] << ' ' << W10[2] << '\n'
//              << (M4*W9)[3] << ' ' << W10[3] << '\n'
//              << (M4*W9)[4] << ' ' << W10[4] << "\n\n";

    std::cerr << "Testy ok!\n";
}
