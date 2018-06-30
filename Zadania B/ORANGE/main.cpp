#include <cassert>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <vector>

const std::string kursplik = "ORANGEPL.mst";
const int iloscZnakowWnazwieSpolki = 9;
const std::string trendplik = "trend.txt";

class Data
{
    public:
          explicit Data(long long data);
          double Ulamkowo() const;

    private:
        bool czyPrzestepny(int R);
        int iloscWmiesiacu(int R, int M);
        bool Sensowna(int rok, int miesiac, int dzien);
        double NaUlamek();
        int dzien_;
        int miesiac_;
        int rok_;
        bool przestepny_;
        double ulamek_;
};

Data::Data(long long data)
{
      int D = data % 100;
      data /= 100;
      int M = data % 100;
      data /= 100;
      int R = data;
      Sensowna(R, M, D);
      przestepny_ = czyPrzestepny(R);
      dzien_ = D;
      miesiac_ = M;
      rok_ = R;
      ulamek_ = NaUlamek();
}

double Data::Ulamkowo() const
{
  return ulamek_;
}

bool Data::czyPrzestepny (int R)
{
    return((R%4 == 0 && R%100 != 0) || R%400 == 0);
}

int Data::iloscWmiesiacu(int R, int M)
{
    assert(1 <= M && M <= 12);
    int WY = 0;
    if(M == 2)
    {
        if(czyPrzestepny(R)) WY = 29;
        if(!czyPrzestepny(R)) WY = 28;
    }
    else if((M % 2 == 1 && M <= 7)
          || (M % 2 == 0 && M >= 8)) WY = 30;
    else WY = 31;
    return WY;
}

bool Data::Sensowna(int R, int M, int D)
{
    bool wyjscie = false;
    if (0 <= R)
    {
        if(1 <= M && M <= 12)
        {
            if(M == 2)
            {
                if(czyPrzestepny(R) && 1 <= D && D <= 29) wyjscie = true;
                if(!czyPrzestepny(R) && 1 <= D && D <= 28) wyjscie = true;
            }
            else if(((M % 2 == 1 && M <= 7)
                     || (M % 2 == 0 && M >= 8))
                    && (1 <= D && D <= 31)) wyjscie = true;
            else if(1 <= D && D <= 31) wyjscie = true;
        }
    }
    return(wyjscie);
}

double Data::NaUlamek()
{
    int liczba_dni = iloscWmiesiacu(rok_, miesiac_);
    int mianownik = (przestepny_ ? 366 : 365);
    return (double(rok_) + double(liczba_dni) / double(mianownik));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Notowanie
{
     public:
          Notowanie(long long data, double cenaNAkoniec);
          double DataN() const;
          double cenaNAkoniec() const;

     private:
          Data data_;
          double cenaNAkoniec_;
};

Notowanie::Notowanie(long long data, double cenaNAkoniec)
    : data_(data), cenaNAkoniec_(cenaNAkoniec)
{

}

double Notowanie::DataN() const
{
    return data_.Ulamkowo();
}

double Notowanie::cenaNAkoniec() const
{
    return cenaNAkoniec_;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void wylicz_trend(std::vector<Notowanie> N, double& a, double& b)
{
    double SX = 0.0;
    double SY = 0.0;
    double SXX = 0.0;
    double SXY = 0.0;
    double ile = N.size();
    for (unsigned int i = 0; i < N.size(); ++i)
    {
        double x = N[i].DataN();
        double y = N[i].cenaNAkoniec();
        SX += x;
        SY += y;
        SXX += x * x;
        SXY += x * y;
    }

//    Mamy do rozwiazania uklad rownan:
//        SXY - a * SXX - b * SX  = 0
//        SY  - a * SX  - b * ile = 0

//    double delta = SX * SX - SXX * ile;
//    if (delta != 0)
//    {
//        a = (SX * SY - SXY * ile) / delta;
//        b = (SX * SXY - SXX * SY) / delta;
//    }
//    else
//    {
//        a = 0.0;
//        b = 0.0;
//    }


    double W = (SXX * ile) - (SX * SX);
    double Wa = (ile * SXY) - (SX * SY);
    double Wb = (SXX * SY) - (SX * SXY);
    if (W != 0)
    {
        a = Wa / W;
        b = Wb / W;
    }
    else
    {
        a = 0.0;
        b = 0.0;
    }
}

std::vector<Notowanie> wczytaj_dane()
{
    std::ifstream in(kursplik.c_str());
    if (in)
    {
        std::cerr << "Wczytywanie...\n";
        std::string TEMPstr;
        std::vector<Notowanie> dane;
        long long data = 0;
        long long ile = 0;
        char c = ' ';
        double TEMP = 0.0;
        double close = 0.0;
        getline(in, TEMPstr);
        while (in && !in.eof())
        {
            getline(in, TEMPstr);
            if (in.eof()) break;
            TEMPstr = TEMPstr.substr(iloscZnakowWnazwieSpolki);
            std::istringstream instr(TEMPstr);
            instr >> data >> c >> TEMP
                          >> c >> TEMP
                          >> c >> TEMP
                          >> c >> close
                          >> c >> TEMP;
            if (in)
            {
                dane.push_back(Notowanie(data, close));
                ile++;
            }
        }
        in.close();
        std::cerr << "Wczytywanie OK! Wczytano "<< ile << " linijek.\n" ;
        return dane;
    }
        else
        {
            std::cerr << "Błąd wczytywania danych!\n";
            return std::vector<Notowanie>();
        }
}

void zapisz_dane(std::vector<Notowanie> N, double a, double b)
{
    std::ofstream WY(trendplik.c_str());
    WY.setf(std::ios::fixed);
    WY.precision(4);
    if (WY)
    {
        for (unsigned i = 0; i < N.size(); ++i)
        {
            WY << N[i].DataN() << ';' << N[i].cenaNAkoniec() << ';'
                << N[i].DataN() * a + b << '\n';
        }
    }
    else
    {
        std::cerr << "Problem z zapisem!\n";
    }
}

void Wykonaj()
{
    std::vector<Notowanie> N;
    N = wczytaj_dane();
    double a = 0.0;
    double b = 0.0;
    if (N.empty())
    {
        std::cerr << "Wczytane dane są puste!\n";
    }
    else
    {
        std::cout.setf(std::ios::fixed);
        std::cout.precision(4);
        wylicz_trend(N, a, b);
        std::cout << "\nWspółczynnik kierunkowy funkcji liniowej to: " << a << ",\na wyraz wolny to: " << b << ".\n";
        zapisz_dane(N, a, b);
    }
}

int main(void)
{
    Wykonaj();
    return 0;
}
