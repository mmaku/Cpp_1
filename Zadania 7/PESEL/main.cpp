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

bool liczbaKontrolna(std::string P)
{
    int liczba = char2int(P[0])
               + 3*char2int(P[1])
               + 7*char2int(P[2])
               + 9*char2int(P[3])
               + 1*char2int(P[4])
               + 3*char2int(P[5])
               + 7*char2int(P[6])
               + 9*char2int(P[7])
               + 1*char2int(P[8])
               + 3*char2int(P[9]);

    liczba %= 10;
    liczba = (10-liczba)%10;
    return(liczba == char2int(P[10]));
}

void test_liczbaKontrolna()
{
    assert(liczbaKontrolna("44051401358") == false);
    assert(liczbaKontrolna("93051008752"));
    assert(liczbaKontrolna("95050502585") == false);
    assert(liczbaKontrolna("95050502589"));
    assert(liczbaKontrolna("65021408936") == false);
    assert(liczbaKontrolna("65021408938"));
    assert(liczbaKontrolna("65421408938") == false);
    assert(liczbaKontrolna("65421408930"));
    assert(liczbaKontrolna("95634816198") == false);
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

    if(czyDalej) czyDalej &= liczbaKontrolna(P);

    return(czyDalej);
}

void test_sensownyPESEL()
{
    assert(sensownyPESEL("44051401358") == false);
    assert(sensownyPESEL("93051008752"));
    assert(sensownyPESEL("95050502585") == false);
    assert(sensownyPESEL("95050502589"));
    assert(sensownyPESEL("65021408936") == false);
    assert(sensownyPESEL("65021408938"));
    assert(sensownyPESEL("65421408936") == false);
    assert(sensownyPESEL("65421408930"));
    assert(sensownyPESEL("168468468468468464") == false);
    assert(sensownyPESEL("asdsadasdasdasdsadas") == false);
}

struct PESEL
{
    char a, b, c, d, e ,f , g, h, i, j, k;

    PESEL (std::string wejscie): a(wejscie[0]),
                                 b(wejscie[1]),
                                 c(wejscie[2]),
                                 d(wejscie[3]),
                                 e(wejscie[4]),
                                 f(wejscie[5]),
                                 g(wejscie[6]),
                                 h(wejscie[7]),
                                 i(wejscie[8]),
                                 j(wejscie[9]),
                                 k(wejscie[10])
        {
        }
};

std::ostream& operator<<(std::ostream& wy, PESEL P)
{
    wy << P.a << P.b << P.c << P.d << P.e << P.f
       << P.g << P.h << P.i << P.j << P.k;
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
    else
        we.setstate(std::ios_base::failbit);
    return we;
}

 PESEL pobieraniePESEL(std::string polecenie)
 {
    std::string wejscie;
    PESEL wyjscie("93051008752");

    std::cout << polecenie;
    std::getline(std::cin, wejscie);
    std::istringstream strumien(wejscie);
    strumien >> std::skipws >> wyjscie;

    while (!strumien)
    {
        strumien.ignore(1000, '\n');
        strumien.clear();
        std::cout << "Coś poszło nie tak, podaj date jeszcze raz (format YYMMDDXXXXK): ";
        std::cin.clear();
        std::getline(std::cin, wejscie);
        strumien.str (wejscie);
        strumien >> std::skipws >> wyjscie;
    }

    return(wyjscie);
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

data dataZpesel(PESEL P)
{
    int dzien = 0, miesiac = 0, rok = 0;
    switch(char2int(P.c))
    {
        case 0 :;
        case 1 : {miesiac = char2int(P.c)*10 + char2int(P.d); rok = 1900; break;}
        case 2 :;
        case 3 : {miesiac = char2int(P.c)*10 + char2int(P.d) - 20; rok = 2000; break;};
        case 4 :;
        case 5 : {miesiac = char2int(P.c)*10 + char2int(P.d) - 40; rok = 2100; break;};
        case 6 :;
        case 7 : {miesiac = char2int(P.c)*10 + char2int(P.d) - 60; rok = 2200; break;};
        case 8 :;
        case 9 : {miesiac = char2int(P.c)*10 + char2int(P.d) - 80; rok = 2300; break;};
    }

    dzien = char2int(P.e)*10 + char2int(P.f);
    rok += char2int(P.a)*10 + char2int(P.b);
    return(data(dzien, miesiac, rok));
}

void test_dataZpesel()
{
    assert(dataZpesel(PESEL("93051008752")) == data(10, 05, 1993));
    assert(dataZpesel(PESEL("95050502589")) == data(05, 05, 1995));
    assert(dataZpesel(PESEL("65021408938")) == data(14, 02, 1965));
    assert(dataZpesel(PESEL("65421408930")) == data(14, 02, 2165));
}

void PROCEDURA()
{
    std::string forma = " mężczyzny\nurodzonego ";
    PESEL A = pobieraniePESEL("Podajnumer pesel do rozkodowania, format YYMMDDXXXXK: ");
    if(char2int(A.j)%2 == 0) forma = " kobiety\nurodzonej";
    std::cout << "\nPodane przez Ciebie pesel " << A << " należy do" << forma
              << dataZpesel(A) << '\n';
}

void test()
{
    test_dataZpesel();
    test_liczbaKontrolna();
    test_sensownyPESEL();
}

int main()
{
    test();
    PROCEDURA();
    return(0);
}
