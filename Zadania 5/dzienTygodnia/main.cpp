#include <iostream>
#include <string>
#include <cassert>

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


 void test_dzieWskaznik ()
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
    if (wskaznik == 0) return("niedziela");
    if (wskaznik == 1) return("poniedziałek");
    if (wskaznik == 2) return("wtorek");
    if (wskaznik == 3) return("środa");
    if (wskaznik == 4) return("czwartek");
    if (wskaznik == 5) return("piątek");
    if (wskaznik == 6) return("sobota");
 }

  std::string nazwaMiesiac (int wskaznik)
 {
    assert(wskaznik >= 1 && wskaznik <= 12);
    if (wskaznik == 1) return("styczeń");
    if (wskaznik == 2) return("luty");
    if (wskaznik == 3) return("marzec");
    if (wskaznik == 4) return("kwieceiń");
    if (wskaznik == 5) return("maj");
    if (wskaznik == 6) return("czerwiec");
    if (wskaznik == 7) return("lipiec");
    if (wskaznik == 8) return("sierpień");
    if (wskaznik == 9) return("wrzesień");
    if (wskaznik == 10) return("październik");
    if (wskaznik == 11) return("listopad");
    if (wskaznik == 12) return("grudzień");
 }

 void test_nazwaMIesiac()
 {
    assert(nazwaMiesiac(1) == "styczeń");
    assert(nazwaMiesiac(2) == "luty");
    assert(nazwaMiesiac(3) == "marzec");
    assert(nazwaMiesiac(5) == "maj");
    assert(nazwaMiesiac(7) == "lipiec");
    assert(nazwaMiesiac(8) == "sierpień");
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


void test ()
{
    test_nazwaMIesiac();
    test_dzieWskaznik();
}



int main()
{
    int dzien = 0, miesiac = 0, rok =0;
    rok = pobieranieZmiennych("Podaj rok: ", 0, 9999, "Kalendarz obsługuje lata od 0 do 9999\n");
    miesiac = pobieranieZmiennych("Podaj miesiąc: ", 1, 12);
    if (miesiac == 2 && ((rok%4 == 0 && rok%100 != 0) || rok%400 == 0)) dzien = pobieranieZmiennych("Podaj dzien: ", 1, 29);
    else if (miesiac == 2 && !((rok%4 == 0 && rok%100 != 0) || rok%400 == 0)) dzien = pobieranieZmiennych("Podaj dzien: ", 1, 28);
    else if ((miesiac % 2 == 1 && miesiac <= 7) || (miesiac % 2 ==0 && miesiac >= 8)) dzien = pobieranieZmiennych("Podaj dzien: ", 1, 31);
    else dzien = pobieranieZmiennych("Podaj dzien: ", 1, 30);
    std::cout << "\nPodana przez Ciebie data to: " << dzienTygodnia(dzienWskaznik(dzien, miesiac, rok))
              << ", " << dzien << " " << nazwaMiesiac(miesiac) << " " << rok << "\n";
    return(0);
}
