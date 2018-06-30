#include <iostream>
#include <string>
#include <cassert>
#include <sstream>

// Część programu odpowiedzialna za wypisanie kwoty długu

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

std::string formaZLOTY(int liczba)
{
    assert (liczba >= 0);
    if (liczba == 1) return("złoty");
    liczba = liczba % 100;
    if (liczba > 10 && liczba <20) return("złotych");
    liczba = liczba % 10;
    if (liczba > 1 && liczba < 5) return("złote");
    else return("złotych");

}

void test_formaZLOTY()
{
    assert(formaZLOTY(0) == "złotych");
    assert(formaZLOTY(1) == "złoty");
    assert(formaZLOTY(422) == "złote");
    assert(formaZLOTY(43) == "złote");
    assert(formaZLOTY(185) == "złotych");
    return;
}

std::string formaGROSZY(int liczba)
{
    assert (liczba >= 0);
    if (liczba == 1) return("grosz");
    liczba = liczba % 100;
    if (liczba > 10 && liczba <20) return("groszy");
    liczba = liczba % 10;
    if (liczba > 1 && liczba < 5) return("grosze");
    else return("groszy");

}

void test_formaGROSZY()
{
    assert(formaGROSZY(0) == "groszy");
    assert(formaGROSZY(1) == "grosz");
    assert(formaGROSZY(422) == "grosze");
    assert(formaGROSZY(43) == "grosze");
    assert(formaGROSZY(185) == "groszy");
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

std::string dlugSlownie (double dlug)
{
    assert(dlug >= 0 && dlug <= 999999);

    int czescZlotowa, czescGroszowa;
    czescZlotowa = int(dlug);
    czescGroszowa = int(100.0 * (dlug-czescZlotowa));
    std::string wyjscie = "";

    assert(czescGroszowa >= 0 && czescGroszowa <= 99);
    assert(czescZlotowa >= 0 && czescZlotowa <= 999999);

    int czescDuza = czescZlotowa/1000, czescMala = czescZlotowa % 1000;
    if (czescDuza > 0)
    {
        wyjscie = wyjscie + liczebnikSetek(czescDuza) + " " + formaTYSIAC(czescDuza) + " ";
    }
    if (czescMala > 0)
    {
        wyjscie = wyjscie + liczebnikSetek(czescMala) + " " + formaZLOTY(czescMala);
    }
    else wyjscie = wyjscie + formaZLOTY(czescDuza);
    if (czescZlotowa == 0) wyjscie = "zero złotych";

    wyjscie = wyjscie + ", ";

    assert(czescGroszowa < 100);
    if (czescGroszowa > 0 && czescGroszowa < 100)
    {
        wyjscie = wyjscie + liczebnikDziesiatek(czescGroszowa) + " " + formaGROSZY(czescGroszowa);
    }
    else if (czescGroszowa == 0) wyjscie = wyjscie + "zero groszy";
    else wyjscie = wyjscie + formaGROSZY(czescDuza);

    return(wyjscie);
}

void dlugSlownie()
{
    assert(dlugSlownie(0) == "zero złotych, zero groszy");
    assert(dlugSlownie(5000.67) == "pięc tysiący złotych sześćdziesiąt, siedem groszy");
    assert(dlugSlownie(135) == "sto trzydzieści pięć złotych, zero groszy");
    assert(dlugSlownie(64000.05) == "sześćdziesiąt cztery tysiące złotych, pięć groszy");
    return;
}

// Część odpowiedzialna za słowny zapis daty

 int dzienWskaznik(int dzien, int miesiac, int rok)
 {
    int rokZpoprwka, korekta;
    if (miesiac < 3)
    {
        korekta = 0;
        rokZpoprwka = rok - 1;
    }
    else
    {
        korekta = 2;
        rokZpoprwka = rok;
    }

    return(((23*miesiac)/9 + dzien + 4 + rok + (rokZpoprwka/4) - (rokZpoprwka/100) + (rokZpoprwka/400) - korekta) % 7);
 }


 void test_dzienWskaznik ()
 {
    assert(dzienWskaznik(28, 3, 2014) == 5);
    assert(dzienWskaznik(27, 3, 2014) == 4);
    assert(dzienWskaznik(26, 3, 2014) == 3);
    assert(dzienWskaznik(25, 3, 2014) == 2);
    assert(dzienWskaznik(24, 3, 2014) == 1);
    assert(dzienWskaznik(23, 3, 2014) == 0);
    assert(dzienWskaznik(22, 3, 2014) == 6);
 }

 std::string dzienTygodnia (int wskaznik)
 {
    assert(wskaznik >= 0 && wskaznik <= 6);
    if (wskaznik == 0) return("niedzielę");
    if (wskaznik == 1) return("poniedziałek");
    if (wskaznik == 2) return("wtorek");
    if (wskaznik == 3) return("środę");
    if (wskaznik == 4) return("czwartek");
    if (wskaznik == 5) return("piątek");
    if (wskaznik == 6) return("sobotę");
    return("");
 }

  std::string nazwaMiesiac (int wskaznik)
 {
    assert(wskaznik >= 1 && wskaznik <= 12);
    if (wskaznik == 1) return("stycznia");
    if (wskaznik == 2) return("lutego");
    if (wskaznik == 3) return("marca");
    if (wskaznik == 4) return("kwietnia");
    if (wskaznik == 5) return("maja");
    if (wskaznik == 6) return("czerwca");
    if (wskaznik == 7) return("lipca");
    if (wskaznik == 8) return("sierpnia");
    if (wskaznik == 9) return("września");
    if (wskaznik == 10) return("października");
    if (wskaznik == 11) return("listopada");
    if (wskaznik == 12) return("grudnia");
    return("");
 }

 void test_nazwaMIesiac()
 {
    assert(nazwaMiesiac(1) == "styczenia");
    assert(nazwaMiesiac(2) == "lutego");
    assert(nazwaMiesiac(3) == "marca");
    assert(nazwaMiesiac(5) == "maja");
    assert(nazwaMiesiac(7) == "lipca");
    assert(nazwaMiesiac(8) == "sierpnia");
 }


 int pobieranieZmiennych (std::string polecenie, int dolny, int gorny, std::string poprawka = "")
 {
    int zmienna = 0;
    std::cout << polecenie;
    std::cin >> zmienna;
    while (std::cin.fail() || zmienna < dolny || zmienna > gorny)
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << poprawka
                  << "Podana wartość nie jest liczbą całkowitą z zakresu ["
                  << dolny << ", " << gorny <<  "]..."
                  << "\nPodaj liczbę jeszcze raz: ";
        std::cin >> zmienna;
    }
    return(zmienna);
 }

  double pobieranieZmiennychDOUBLE (std::string polecenie, int dolny, int gorny, std::string poprawka = "")
 {
    double zmienna = 0;
    std::cout << polecenie;
    std::cin >> zmienna;
    while (std::cin.fail() || zmienna < dolny || zmienna > gorny)
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << poprawka
                  << "Podana wartość nie jest liczbą z zakresu ["
                  << dolny << ", " << gorny <<  "]..."
                  << "\nPodaj liczbę jeszcze raz: ";
        std::cin >> zmienna;
    }
    return(zmienna);
 }


void test ()
{
    test_nazwaMIesiac();
    test_dzienWskaznik();
}

std::string dataNazwa()
{
    std::ostringstream strumien;
    int dzien = 0, miesiac = 0, rok =0;
    rok = pobieranieZmiennych("Teraz podaj termin zapłaty.\nPodaj rok: ", 0, 9999, "Program obsługuje lata od 0 do 9999\n");
    miesiac = pobieranieZmiennych("Podaj miesiąc: ", 1, 12);
    if (miesiac == 2 && ((rok%4 == 0 && rok%100 != 0) || rok%400 == 0)) dzien = pobieranieZmiennych("Podaj dzien: ", 1, 29);
    else if (miesiac == 2 && !((rok%4 == 0 && rok%100 != 0) || rok%400 == 0)) dzien = pobieranieZmiennych("Podaj dzien: ", 1, 28);
    else if ((miesiac % 2 == 1 && miesiac <= 7) || (miesiac % 2 ==0 && miesiac >= 8)) dzien = pobieranieZmiennych("Podaj dzien: ", 1, 31);
    else dzien = pobieranieZmiennych("Podaj dzien: ", 1, 30);
    strumien << dzienTygodnia(dzienWskaznik(dzien, miesiac, rok)) << ", "
             << dzien << " " << nazwaMiesiac(miesiac) << " " << rok;
    std::string wyjscie = strumien.str();
    return(wyjscie);
}

    double kwota;
    std::string plec, imieNazwisko, data, zwrot1, zwrot2, zwrot3, adres;
    bool plecB;

int main()
{
    double kwota;
    std::string plec, imieNazwisko, data, zwrot1, zwrot2, zwrot3, adres;
    bool plecB;

    std:: cout << "Nimniejszy program wygeneruje pismo wzywające do zapłaty.\n"
               << "Podaj płeć dłużnika (k - kobieta, m - mężczyzna): ";
    std::cin >> plec;
    while (!(plec == "k" || plec == "K" || plec == "m" || plec == "M"))
    {
        std::cout << "Podana wartość nie jest symbolem żadnej ze płci..."
                  << "\nPodaj płeć jeszcze raz: ";
        std::cin >> plec;
    }

    if(plec == "m" || plec == "M") plecB = true;
    else plecB = false;

    std::cout << "Podaj imię i nazwisko dłużnika: ";
    std::cin.ignore();
    std::getline(std::cin, imieNazwisko);

    std::cout << "Podaj adres dłużnika: ";
    std::getline(std::cin, adres);

    data = dataNazwa();

    kwota = pobieranieZmiennychDOUBLE("Podaj kwotę zadłużenia: ", 0, 999999);

    std::cout << kwota << "\n";

    int czescZlotowa = int(kwota);
    int czescGroszowa = int(100.0 * (kwota - int(kwota)));

    if (plecB) {
        zwrot1 = "Pan ";
        zwrot2 = "zamieszkały ";
        zwrot3 = "wzywany jest do zapłaty kwoty równej ";
    } else {
        zwrot1 = "Pani ";
        zwrot2 = "zamieszkała ";
        zwrot3 = "wzywana jest do zapłaty kwoty równej ";
    }

    std::cout << zwrot1 << imieNazwisko << ",\n"
              << zwrot2 << adres << ",\n"
              << zwrot3 << czescZlotowa << " zł " << czescGroszowa << " gr\n"
              << "(słownie: " << dlugSlownie(kwota) << ").\n"
              << "Ostateczny termin spłaty zaległości upływa w " << data << ".\n";

}
