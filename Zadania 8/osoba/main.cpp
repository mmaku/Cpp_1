#include <iostream>
#include <sstream>
#include <assert.h>
#include <string>

bool czyPrzestepny (int R)
{
    return((R%4 == 0 && R%100 != 0) || R%400 == 0);
}

bool sensownaData(int R, int M, int D)
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

struct Data
{
    int rok, miesiac, dzien;
    Data (int R = 0, int M = 0, int D = 0):  rok(R), miesiac(M), dzien(D)
        {
        }
};

bool operator==(const Data& D1, const Data& D2)
{ return (D1.dzien == D2.dzien && D1.miesiac == D2.miesiac && D1.rok == D2.rok); }

bool operator<=(const Data& D1, const Data& D2)
{
    bool wyjscie = true;
    if (D1.rok > D2.rok)
        wyjscie = false;
    if (D1.rok == D2.rok && D1.miesiac > D2.miesiac)
        wyjscie = false;
    if (D1.rok == D2.rok && D1.miesiac == D2.miesiac && D1.dzien > D2.dzien)
        wyjscie = false;
    return wyjscie;
}

std::string nazywajMiesiac(Data D)
{
    std::string wyjscie;
    switch(D.miesiac)
    {
        case 1: wyjscie= " stycznia "; break;
        case 2: wyjscie= " lutego "; break;
        case 3: wyjscie= " marca "; break;
        case 4: wyjscie= " kwietnia "; break;
        case 5: wyjscie= " maja "; break;
        case 6: wyjscie= " czerwca "; break;
        case 7: wyjscie= " lipca "; break;
        case 8: wyjscie= " sierpnia "; break;
        case 9: wyjscie= " września "; break;
        case 10: wyjscie= " października "; break;
        case 11: wyjscie= " listopada "; break;
        case 12: wyjscie= " grudnia "; break;
    }
    return(wyjscie);
}

std::ostream& operator<<(std::ostream& wy, Data D)
{
    wy << D.dzien << nazywajMiesiac(D) << D.rok << "r.";
    return wy;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string wielkie = "ABCDEFGHIJKLMNOPQRSTUVWXYZĄĆĘŁŃÓŚŹŻ";
std::string male = "abcdefghijklmnopqrstuvwxyząćęłńóśźż";

inline int bityPoczatkowe(int bajt)
{
    int nbity = 0, rozmiarBajtu = 128;
    while ((rozmiarBajtu > 0) && (bajt & rozmiarBajtu))
    {
        ++nbity;
        rozmiarBajtu >>= 1;
    }
    return std::max(1, nbity);
}

inline int dlugosc(std::string tekst)
{
    int litery = 0;
    for (unsigned int i = 0; i < tekst.size(); ++i)
    {
        ++litery;
        i += std::max(bityPoczatkowe(tekst[i]) - 1, 0);
    }
    return litery;
}

inline bool sensowneImie(std::string nazwa)
{
    assert(dlugosc(nazwa) >= 2);
    bool wyjscie = true;
    if (wielkie.find(nazwa.substr(0, bityPoczatkowe(nazwa[0]))) == std::string::npos)
        wyjscie = false;
    for (unsigned i = bityPoczatkowe(nazwa[0]); i < nazwa.size(); ++i)
    {
        if (male.find(nazwa.substr(i, bityPoczatkowe(nazwa[i]))) == std::string::npos)
            wyjscie = false;
        i += bityPoczatkowe(nazwa[0]) - 1;
    }
    return wyjscie;
}
class Osoba
{
    public:
        Osoba(Data DataUrodzenia, std::string nazwisko="", std::string pierwszeImie="", std::string drugieImie="")
        : DataUrodzenia_(DataUrodzenia), nazwisko_(nazwisko), pierwszeImie_(pierwszeImie), drugieImie_(drugieImie)
        {
            assert(!pierwszeImie.empty() && sensowneImie(pierwszeImie));
            assert(drugieImie.empty() || sensowneImie(drugieImie));
            inicjaly_ = pierwszeImie.substr(0, std::max(1, bityPoczatkowe(pierwszeImie[0]))) + ".";
            if (!drugieImie.empty())
                inicjaly_ += " " + drugieImie.substr(0, std::max(1, bityPoczatkowe(drugieImie[0]))) + ".";

        }
        int IleImion() const
        {
            return ((drugieImie_.empty()) ? 1 : 2);
        }
        std::string Imie() const
        {
            return pierwszeImie_;
        }
        std::string Imiona() const
        {
            return ((drugieImie_.empty()) ? pierwszeImie_ : (pierwszeImie_ + " " + drugieImie_));
        }
        std::string Nazwisko() const
        {
            return nazwisko_;
        }
        std::string ImionaINazwisko() const
        {
            return ((drugieImie_.empty()) ?
                    (pierwszeImie_ + " " + nazwisko_)
                    : (pierwszeImie_ + " " + drugieImie_ + " " + nazwisko_));
        }
        std::string InicjalyINazwisko() const
        {
            return inicjaly_ + " " + nazwisko_;
        }
        Data DataUrodzenia() const
        {
            return DataUrodzenia_;
        }
        int Wiek(Data D) const;

 private:
        Data DataUrodzenia_;
        std::string nazwisko_;
        std::string pierwszeImie_;
        std::string drugieImie_;
        std::string inicjaly_;
};

int Osoba::Wiek(Data D) const
{
    assert(DataUrodzenia_ <= D);
    int wyjscie = D.rok - DataUrodzenia_.rok;
    if(D.miesiac < DataUrodzenia_.miesiac) wyjscie--;
    else if(D.miesiac == DataUrodzenia_.miesiac && D.dzien < DataUrodzenia_.dzien) wyjscie--;
    return wyjscie;
}

void test();

int main(void)
{
    test();
    return 0;
}

void test_dlugosc()
{
    assert(dlugosc("MIchAl") == 6);
    assert(dlugosc("Jakub") == 5);
    assert(dlugosc("żążyć") == 5);
    assert(dlugosc("łów") == 3);
    assert(dlugosc("ąćęłńóśź") == 8);
    assert(dlugosc("ĄĆĘŁŚŹŻ") == 7);
    assert(dlugosc("Ż") == 1);
}

void test_sensowneImie()
{
    assert(sensowneImie("Damian"));
    assert(sensowneImie("Ćwiartka"));
    assert(sensowneImie("Gość"));
    assert(sensowneImie("Źdźbło"));
    assert(!sensowneImie("tomaszek"));
    assert(!sensowneImie("$:Janek"));
    assert(!sensowneImie("źdźbło"));
}

void test_Osoba(void)
{
    Osoba jkw(Data(1922,2,24), "Wscieklica", "Jan", "Karol");
    assert(jkw.IleImion()==2);
    assert(jkw.Imie()=="Jan");
    assert(jkw.Imiona()=="Jan Karol");
    assert(jkw.Nazwisko()=="Wscieklica");
    assert(jkw.ImionaINazwisko()=="Jan Karol Wscieklica");
    assert(jkw.InicjalyINazwisko()=="J. K. Wscieklica");
    assert(jkw.DataUrodzenia()==Data(1922,2,24));
    assert(jkw.Wiek(Data(2014,4,16))==92);

    const Osoba aa(Data(2013,4,16), "Abacki", "Adam");
    assert(aa.IleImion()==1);
    assert(aa.Imie()=="Adam");
    assert(aa.Imiona()=="Adam");
    assert(aa.Nazwisko()=="Abacki");
    assert(aa.ImionaINazwisko()=="Adam Abacki");
    assert(aa.InicjalyINazwisko()=="A. Abacki");
    assert(aa.DataUrodzenia()==Data(2013,4,16));
    assert(aa.Wiek(Data(2013,12,31))==0);
    assert(aa.Wiek(Data(2014,4,16))==1);
    std::cerr << "OK";
}

void test()
{
    test_sensowneImie();
    test_dlugosc();
    test_Osoba();
}
