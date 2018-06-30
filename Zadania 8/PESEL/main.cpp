#include <iostream>
#include <sstream>
#include <assert.h>
#include <string>

bool czyPrzestepny (int R)
{
    return((R%4 == 0 && R%100 != 0) || R%400 == 0);
}

bool sensownaData(int D, int M, int R)
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

struct data
{
    int dzien, miesiac, rok;
    data (int D = 0, int M = 0, int R = 0): dzien(D), miesiac(M), rok(R)
        {
        }
};

bool operator==(const data& D1, const data& D2)
{ return (D1.dzien == D2.dzien && D1.miesiac == D2.miesiac && D1.rok == D2.rok); }

std::string nazywajMiesiac(data D)
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

std::ostream& operator<<(std::ostream& wy, data D)
{
    wy << D.dzien << nazywajMiesiac(D) << D.rok << "r.";
    return wy;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int char2int (char a)
{
    int wyjscie = 0;
    switch(a)
    {
        case '1' : wyjscie = 1; break;
        case '2' : wyjscie = 2; break;
        case '3' : wyjscie = 3; break;
        case '4' : wyjscie = 4; break;
        case '5' : wyjscie = 5; break;
        case '6' : wyjscie = 6; break;
        case '7' : wyjscie = 7; break;
        case '8' : wyjscie = 8; break;
        case '9' : wyjscie = 9; break;
    }
    return(wyjscie);
}

bool sensownyPESEL(std::string P)
{
    bool czyDalej = true;
    int dzien = 0, miesiac = 0, rok = 0;

    czyDalej &= (P.size() == 11);


    if(czyDalej)
    {
        for(int i=0; i < 11; i++)
            {
                if(0 <= char2int(P[i]) && char2int(P[i]) <= 9);
                else czyDalej = false;
            }
    }

    if(czyDalej)
    {
        switch(char2int(P[2]))
        {
            case 0:;
            case 1: {miesiac = char2int(P[2])*10 + char2int(P[3]); rok = 1900; break;}
            case 2:;
            case 3: {miesiac = char2int(P[2])*10 + char2int(P[3]) - 20; rok = 2000; break;};
            case 4:;
            case 5: {miesiac = char2int(P[2])*10 + char2int(P[3]) - 40; rok = 2100; break;};
            case 6:;
            case 7: {miesiac = char2int(P[2])*10 + char2int(P[3]) - 60; rok = 2200; break;};
            case 8:;
            case 9: {miesiac = char2int(P[2])*10 + char2int(P[3]) - 80; rok = 2300; break;};
        }

        dzien = char2int(P[4])*10 + char2int(P[5]);
        rok += char2int(P[0])*10 + char2int(P[1]);
        czyDalej &= sensownaData(dzien, miesiac, rok);
    }

    return(czyDalej);
}



class PESEL
{
    private:
        char a_, b_, c_, d_, e_ ,f_ , g_, h_, i_, j_, k_;

    public:
        PESEL (std::string wejscie): a_(wejscie[0]),
                                     b_(wejscie[1]),
                                     c_(wejscie[2]),
                                     d_(wejscie[3]),
                                     e_(wejscie[4]),
                                     f_(wejscie[5]),
                                     g_(wejscie[6]),
                                     h_(wejscie[7]),
                                     i_(wejscie[8]),
                                     j_(wejscie[9]),
                                     k_(wejscie[10])
            {
            }
        char a() {return a_;}
        char b() {return b_;}
        char c() {return c_;}
        char d() {return d_;}
        char e() {return e_;}
        char f() {return f_;}
        char g() {return g_;}
        char h() {return h_;}
        char i() {return i_;}
        char j() {return j_;}
        char k() {return k_;}

        std::string napis();
        data dataUrodzenia();
        bool czyKobieta();
        bool czyPoprawnaKontrolna();

};

std::string PESEL::napis()
{
    std::string wyjscie;
    std::ostringstream wy;
    wy << a_ << b_ << c_ << d_ << e_ << f_ << g_ << h_ << i_ << j_ << k_;
    return(wy.str());
}

data PESEL::dataUrodzenia()
{
    int dzien = 0, miesiac = 0, rok = 0;
    switch(char2int(c_))
    {
        case 0 :;
        case 1 : {miesiac = char2int(c_)*10 + char2int(d_); rok = 1900; break;}
        case 2 :;
        case 3 : {miesiac = char2int(c_)*10 + char2int(d_) - 20; rok = 2000; break;};
        case 4 :;
        case 5 : {miesiac = char2int(c_)*10 + char2int(d_) - 40; rok = 2100; break;};
        case 6 :;
        case 7 : {miesiac = char2int(c_)*10 + char2int(d_) - 60; rok = 2200; break;};
        case 8 :;
        case 9 : {miesiac = char2int(c_)*10 + char2int(d_) - 80; rok = 2300; break;};
    }

    dzien = char2int(e_)*10 + char2int(f_);
    rok += char2int(a_)*10 + char2int(b_);
    return(data(dzien, miesiac, rok));
}

bool PESEL::czyKobieta()
{
    return(char2int(j_)%2 == 0);
}

bool PESEL::czyPoprawnaKontrolna()
{
    int liczba = char2int(a_)
               + 3*char2int(b_)
               + 7*char2int(c_)
               + 9*char2int(d_)
               + 1*char2int(e_)
               + 3*char2int(f_)
               + 7*char2int(g_)
               + 9*char2int(h_)
               + 1*char2int(i_)
               + 3*char2int(j_);

    liczba %= 10;
    liczba = (10-liczba)%10;
    return(liczba == char2int(k_));
}

std::ostream& operator<<(std::ostream& wy, PESEL P)
{
    wy << P.napis();
    return wy;
}

std::istream& operator>>(std::istream& we, PESEL &P)
{
    std::string wejscie;
    we >> wejscie;

    if (we)
    {
        if(sensownyPESEL(wejscie))
            P = PESEL(wejscie);
        else
            we.setstate(std::ios_base::failbit);
    }
    return we;
}

int upewnij(std::istringstream& strumien)
{
    char odp;
    std::cout << "Podany pesel ma niepoprawną cyfrę kontrolną,\nczy chcesz podać PESEL jeszcze raz? (t/n): ";
    std::cin >> odp;
    while (!(odp == 't' || odp == 'T' || odp == 'n'|| odp == 'N'))
    {
        std::cout << "Podana wartość nie jest odpowiedzią..."
                  << "\nPodaj odpowiedź jeszcze raz: ";
        std::cin >> odp;
    }

    if(odp == 't' || odp == 'T')
        strumien.setstate(std::ios_base::failbit);

    return 0;
}

 PESEL pobieraniePESEL()
 {
    std::string wejscie;
    PESEL wyjscie("93051008752");

    std::cout << "Podaj numer pesel do rozkodowania, format YYMMDDXXXXK: ";
    std::getline(std::cin, wejscie);
    std::istringstream strumien(wejscie);
    strumien >> std::skipws >> wyjscie;

    if(!wyjscie.czyPoprawnaKontrolna())
        upewnij(strumien);
    std::cin.ignore(1000, '\n');

    while (!strumien)
    {
        strumien.ignore(1000, '\n');
        strumien.clear();
        std::cout << "Podaj pesel jeszcze raz (format YYMMDDXXXXK): ";
        std::cin.clear();
        std::getline(std::cin, wejscie);
        strumien.str (wejscie);
        strumien >> std::skipws >> wyjscie;

        if(!wyjscie.czyPoprawnaKontrolna())
            upewnij(strumien);
        std::cin.ignore(1000, '\n');
    }

    return(wyjscie);
 }

////////////////////////////////////////////////////////////////////TESTY/////////////////////////////////////////////////////////////////////////////








void test_sensownyPESEL()
{
    assert(sensownyPESEL("44051401358"));
    assert(sensownyPESEL("93051008752"));
    assert(sensownyPESEL("95990502585") == false);
    assert(sensownyPESEL("95050502589"));
    assert(sensownyPESEL("65161408936") == false);
    assert(sensownyPESEL("65021408938"));
    assert(sensownyPESEL("65424008936") == false);
    assert(sensownyPESEL("65421408930"));
    assert(sensownyPESEL("168468468468468464") == false);
    assert(sensownyPESEL("asdsadasdasdasdsadas") == false);
}

void test_czyPoprawny()
{
    assert(PESEL("44051401358").czyPoprawnaKontrolna() == false);
    assert(PESEL("93051008752").czyPoprawnaKontrolna());
    assert(PESEL("95050502585").czyPoprawnaKontrolna() == false);
    assert(PESEL("95050502589").czyPoprawnaKontrolna());
    assert(PESEL("65021408936").czyPoprawnaKontrolna() == false);
    assert(PESEL("65021408938").czyPoprawnaKontrolna());
    assert(PESEL("65421408938").czyPoprawnaKontrolna() == false);
    assert(PESEL("65421408930").czyPoprawnaKontrolna());
}

void test_napis()
{
    assert(PESEL("44051401358").napis() == "44051401358");
    assert(PESEL("95050502585").napis() == "95050502585");
    assert(PESEL("65021408936").napis() == "65021408936");
    assert(PESEL("65421408938").napis() == "65421408938");
}

void test_dataUrodzenia()
{
    assert(PESEL("93051008752").dataUrodzenia() == data(10, 05, 1993));
    assert(PESEL("95050502589").dataUrodzenia() == data(05, 05, 1995));
    assert(PESEL("65021408938").dataUrodzenia() == data(14, 02, 1965));
    assert(PESEL("65421408930").dataUrodzenia() == data(14, 02, 2165));
}

void test()
{
    test_napis();
    test_dataUrodzenia();
    test_czyPoprawny();
    test_sensownyPESEL();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PROCEDURA()
{
    std::string forma = " mężczyzny\nurodzonego ";
    PESEL A = pobieraniePESEL();
    if(A.czyKobieta()) forma = " kobiety\nurodzonej";
    std::cout << "\nPodane przez Ciebie pesel " << A << " należy do" << forma
              << A.dataUrodzenia() << '\n';
}

int main()
{
    test();
    PROCEDURA();
    return(0);
}
