#include <iostream>
#include <sstream>
#include <assert.h>


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

std::string nazywajMiesiac(data D)
{
    std::string wyjscie;
    switch(D.miesiac)
    {
    case 1:
        wyjscie= " stycznia ";
        break;
    case 2:
        wyjscie= " lutego ";
        break;
    case 3:
        wyjscie= " marca ";
        break;
    case 4:
        wyjscie= " kwietnia ";
        break;
    case 5:
        wyjscie= " maja ";
        break;
    case 6:
        wyjscie= " czerwca ";
        break;
    case 7:
        wyjscie= " lipca ";
        break;
    case 8:
        wyjscie= " sierpnia ";
        break;
    case 9:
        wyjscie= " września ";
        break;
    case 10:
        wyjscie= " października ";
        break;
    case 11:
        wyjscie= " listopada ";
        break;
    case 12:
        wyjscie= " grudnia ";
        break;
    }
    return(wyjscie);
}

std::ostream& operator<<(std::ostream& wy, data D)
{
    wy << D.dzien << nazywajMiesiac(D) << D.rok << "r.";
    return wy;
}

std::istream& operator>>(std::istream& we, data &D)
{
    int dzien, miesiac, rok;
    we >> dzien >> miesiac >> rok;
    if (we)
    {
        if(sensownaData(dzien, miesiac, rok))
            D = data(dzien, miesiac, rok);
        else
            we.setstate(std::ios_base::failbit);
    }
    else
        we.setstate(std::ios_base::failbit);
    return we;
}

data pobieranieData(std::string polecenie)
{
    std::string wejscie;
    data wyjscie(1, 1, 1);

    std::cout << polecenie;
    std::getline(std::cin, wejscie);
    std::istringstream strumien(wejscie);
    strumien >> std::skipws >> wyjscie;

    while (!strumien)
    {
        strumien.ignore(1000, '\n');
        strumien.clear();
        std::cout << "Coś poszło nie tak, podaj date jeszcze raz (format DD MM YYYY): ";
        std::cin.clear();
        std::getline(std::cin, wejscie);
        strumien.str (wejscie);
        strumien >> std::skipws >> wyjscie;
    }

    return(wyjscie);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zamianaDat(data& pierwszaData, data& drugaData)
{
    if (drugaData.rok > pierwszaData.rok)
    {
        data POM = drugaData;
        drugaData = pierwszaData;
        pierwszaData = POM;
    }
    if (drugaData.rok == pierwszaData.rok && drugaData.miesiac > pierwszaData.miesiac)
    {
        data POM = drugaData;
        drugaData = pierwszaData;
        pierwszaData = POM;
    }
    if (drugaData.rok == pierwszaData.rok && drugaData.miesiac == pierwszaData.miesiac && drugaData.dzien > pierwszaData.dzien)
    {
        data POM = drugaData;
        drugaData = pierwszaData;
        pierwszaData = POM;
    }
}

int dzienWroku (data wejscie)
{
    int suma = wejscie.dzien;

    for (int i = 1; i < wejscie.miesiac; i++)
    {
        if(czyPrzestepny(wejscie.rok) && i == 2) suma += 29;
        else if (!czyPrzestepny(wejscie.rok) && i == 2) suma += 28;
        else if((i % 2 == 1 && i <= 7)
                || (i % 2 == 0 && i >= 8)) suma += 31;
        else suma += 30;
    }
    return(suma);
}


int iloscDni (data A, data B)
{
    zamianaDat(B, A);           // A <= B
    int suma = 0, ktoryDzienA = dzienWroku(A), ktoryDzienB = dzienWroku(B);

    if(A.rok == B.rok) suma = ktoryDzienB-ktoryDzienA;
    else suma = (365+czyPrzestepny(A.rok))-ktoryDzienA+ktoryDzienB;

    for (int i = A.rok+1; i < B.rok; i++)
    {
        if(czyPrzestepny(i)) suma += 366;
        else suma += 365;
    }
    return(suma);
}

int operator-(const data& D1, const data& D2)
{
    return iloscDni(D1, D2);
}

void test_operator()
{
    assert(data(11,11, 2012)-data(11,11, 2012)==0);
    assert(data(12,11, 2012)-data(11,11, 2012)==1);
    assert(data(12,12, 2012)-data(11,11, 2012)==31);
    assert(data(24,12, 1998)-data(12,04, 2014)==5588);
    assert(data(24,12, 1998)-data(12,04, 2012)==4858);
    assert(data(12,04, 1714)-data(21,12, 2012)==109096);
}

void PROCEDURA()
{
    std::string formaDni = " dni.\n";
    data A = pobieranieData("Podaj pierwszą datę w formacie \"DD MM RRRR\": ");
    data B = pobieranieData("Podaj drugą datę w formacie \"DD MM RRRR\": ");
    int roznica;
    roznica = A-B;
    if(roznica == 1) formaDni = " dzień.\n";
    std::cout << "\nPodane przez Ciebie daty to:\n"
              << A << " oraz " << B
              << "\nPomiędzy nimi mija " << roznica << formaDni;
}

int main()
{
    test_operator();
    PROCEDURA();
    return(0);
}
