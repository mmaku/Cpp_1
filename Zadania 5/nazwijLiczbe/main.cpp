#include <iostream>
#include <string>
#include <cassert>


// ZADANIE 1

std::string formaTYSIAC(int liczba)
{
    assert (liczba >= 0);
    if (liczba == 1) return("tysiąc");
    if (liczba == 0) return("");
    liczba = liczba % 100;
    if (liczba > 10 && liczba <20) return("tysięcy");
    liczba = liczba % 10;
    if (liczba > 1 && liczba < 5) return("tysiące");
    else return("tysięcy");

}

void test_formaTYSIAC()
{
    assert(formaTYSIAC(0) == "");
    assert(formaTYSIAC(1) == "tysiąc");
    assert(formaTYSIAC(422) == "tysiące");
    assert(formaTYSIAC(43) == "tysiące");
    assert(formaTYSIAC(185) == "tysięcy");
    return;
}

std::string formaELEMENTY(int liczba)
{
    assert (liczba >= 0);
    if (liczba == 1) return("element");
    liczba = liczba % 100;
    if (liczba > 10 && liczba <20) return("elementów");
    liczba = liczba % 10;
    if (liczba > 1 && liczba < 5) return("elementy");
    else return("elementów");

}

void test_formaELEMENTY()
{
    assert(formaELEMENTY(0) == "elementów");
    assert(formaELEMENTY(1) == "element");
    assert(formaELEMENTY(422) == "elementy");
    assert(formaELEMENTY(43) == "elementy");
    assert(formaELEMENTY(185) == "elementów");
    return;
}

std::string liczebnikJednosci (int liczba)
{
    assert(liczba >= 0 && liczba < 10);
    std::string wyjscie = "";
    if (liczba == 1) return "jeden";
    if (liczba == 2) return "dwa";
    if (liczba == 3) return "trzy";
    if (liczba == 4) return "cztery";
    if (liczba == 5) return "pięć";
    if (liczba == 6) return "sześć";
    if (liczba == 7) return "siedem";
    if (liczba == 8) return "osiem";
    if (liczba == 9) return "dziewięć";
    return(wyjscie);
}

void test_liczebnikJednosci()
{
    assert(liczebnikJednosci(1) == "jeden");
    assert(liczebnikJednosci(8) == "osiem");
    return;
}

std::string liczebnikDziesiatek (int liczba)
{
    assert(liczba >= 0 && liczba < 100);

    if (liczba < 10) return(liczebnikJednosci(liczba));

    else if (liczba < 20)
    {
        if (liczba == 10) return("dziesięć");
        if (liczba == 11) return("jedynaście");
        if (liczba == 12) return("dwanaście");
        if (liczba == 13) return("trzynaście");
        if (liczba == 14) return("czternaście");
        if (liczba == 15) return("piętnaście");
        if (liczba == 16) return("szesnaście");
        if (liczba == 17) return("siedemnaście");
        if (liczba == 18) return("osiemnascie");
        if (liczba == 19) return("dziewiętnaście");
    }

    else
    {
        std::string wyjscie = "";
        int dziesiatki = liczba / 10;
        int jednosci = liczba % 10;
        if (dziesiatki >= 5) wyjscie = liczebnikJednosci(liczba/10) + "dziesiąt";
        if (dziesiatki == 2) wyjscie = "dwadzieścia";
        if (dziesiatki == 3) wyjscie = "trzydzieści";
        if (dziesiatki == 4) wyjscie = "czterdzieści";
        if (jednosci != 0) wyjscie = wyjscie + " " + liczebnikJednosci(jednosci);
        return(wyjscie);
    }
    return("");
}

void test_liczebnikDziesiatek()
{
    assert(liczebnikDziesiatek(45) == "czterdzieści pięć");
    assert(liczebnikDziesiatek(10) == "dziesięć");
    assert(liczebnikDziesiatek(16) == "szesnaście");
    assert(liczebnikDziesiatek(95) == "dziewięćdziesiąt pięć");
    return;
}

std::string liczebnikSetek (int liczba)
{
    assert(liczba > 0 && liczba < 1000);

    if (liczba < 10) return(liczebnikJednosci(liczba));
    else if (liczba < 100) return(liczebnikDziesiatek(liczba));
    else
    {
        std::string wyjscie = "";
        int setki = liczba / 100;
        int dziesiatki = liczba % 100;
        if (setki == 1) wyjscie = "sto";
        else if (setki == 2) wyjscie = "dwieście";
        else if (setki == 3 || setki == 4 ) wyjscie = liczebnikJednosci(setki) + "sta";
        else wyjscie = liczebnikJednosci(setki) + "set";
        if (dziesiatki != 0) wyjscie = wyjscie + " " + liczebnikDziesiatek(dziesiatki);
        return(wyjscie);
    }
    return("");
}

void test_liczebnikSetek()
{
    assert(liczebnikSetek(145) == "sto czterdzieści pięc");
    assert(liczebnikSetek(10) == "dziesięć");
    assert(liczebnikSetek(816) == "osiemset szesnaście");
    assert(liczebnikSetek(395) == "trzysta dziewięćdziesiąt pięc");
    return;
}

std::string nazwijLiczbeElementow (int liczba)
{
    assert(liczba >= -999999 && liczba <= 999999);

    std::string wyjscie = "";
    if(liczba < 0)
    {
        liczba = liczba * -1;
        wyjscie = "minus ";
    }

    int czescDuza = liczba/1000, czescMala = liczba % 1000;

    if (czescDuza > 0)
    {
        wyjscie = wyjscie + liczebnikSetek(czescDuza) + " " + formaTYSIAC(czescDuza) + " ";
    }
    if (czescMala > 0)
    {
        wyjscie = wyjscie + liczebnikSetek(czescMala) + " " + formaELEMENTY(czescMala);
    }
    else wyjscie = wyjscie + formaELEMENTY(czescDuza);
    if (liczba == 0) wyjscie = "zero elementów";
    return(wyjscie);
}

void test_nazwijLiczbeElementow()
{
    assert(nazwijLiczbeElementow(0) == "zero elementów");
    assert(nazwijLiczbeElementow(5000) == "pięc tysiący elementów");
    assert(nazwijLiczbeElementow(135) == "sto trzydzieści pięć elementów");
    assert(nazwijLiczbeElementow(-92) == "minus dziewięćdziesiąt dwa elementy");
    assert(nazwijLiczbeElementow(-64000) == "minus sześćdziesiąt cztery tysiące elementów");
    return;
}

/*

int main()
{
    test_formaELEMENTY();
    test_formaTYSIAC();
    test_liczebnikDziesiatek();
    test_liczebnikJednosci();
    test_liczebnikSetek();
    test_nazwijLiczbeElementow();
    return(0);
}

*/


int main()
{
    int liczba = 0;
    std::cout << "Ile części jest w pudełku? ";
    std::cin >> liczba;
    while (std::cin.fail() || liczba < -999999 || liczba > 999999)
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Podana wartość nie jest liczbą całkowitą z zakresu [-999999, 999999]..."
                 << "\nPodaj liczbę jeszcze raz: ";
        std::cin >> liczba;
    }

    std::cout << "\n";
    std::cout << "W pudełku jest " << nazwijLiczbeElementow(liczba) <<  "\n";
    return(0);
}


