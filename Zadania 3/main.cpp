#include <iostream>


// ZADANIE 1


 bool czyPrzestepnyProsto(int rok)
 {
    return((rok%4 == 0 && rok%100 != 0) || rok%400 == 0);            /* zgodnie z definicją z wikipedii: rok prestępny jest podzielny przez 49-*
                                                                      i nie jest podzielny przez 100 lub jest podzielny przez 400 */
 }

int czyPrzestepny()
   {                                                                                        // to samo, ale zrobione z prostym interfejsem
    std::string wynik;
    int rok;
    std::cout << "Podaj rok: ";
    std::cin >> rok;
    if((rok%4 == 0 && rok%100 != 0) || rok%400 == 0) wynik=" jest przestepny.";
    else wynik=" nie jest przestepny.";
    std::cout << "Rok " << rok << wynik << "\n\n";
    return 0;
   }


// ZADANIE 2


 unsigned int najwiekszaPotegaProsto(unsigned int liczba)
 {
    unsigned int podstawa=liczba, wskaznik=liczba;
    do
    {
    wskaznik=wskaznik/2;
    if ((podstawa-1)*(podstawa-1)<=liczba && (podstawa)*(podstawa)>liczba) podstawa=podstawa-1;           // ta linijka skraca algorytm, a tekze zapobiega zapetlaniu sie
    else if (podstawa*podstawa>liczba) podstawa=podstawa-wskaznik;                                       // jezeli nasz wynik jest wiekszy, to szukamy liczby mniejszej
    else podstawa=podstawa+wskaznik;                                                                    // jezli wynik jza maly, to szukamy liczby wiekszej
    } while (!(podstawa*podstawa<=liczba && (podstawa+1)*(podstawa+1)>liczba));                        // i robimy to tak dlugo, poki nie zajdzie warunek, ktora nasza liczba ma spelnic
    return(podstawa);
 }

int najwiekszaPotega()
   {                                                                                                     // prosty interfejs
    int wynik;
    unsigned int liczba;
    std::cout << "Dla podanej liczby program znajdzie najwieszka liczbe, \nktorej potega jest mniejsza rowna podanej\n";                           // pobieramy liczbe
    std::cout << "Podaj liczbe: ";
    std::cin >> liczba;
    if (liczba >= 0)
    {
        wynik = najwiekszaPotegaProsto(liczba);
        std::cout << "Najwieksza liczba, ktorej potega jest mniejsza lub rowna " << liczba << " to " << wynik << "\n\n";
    }
    else std::cout << "Podany znak nie jest liczba dodatnia";
    return (0);
   }


   // ZADANIE 3


   unsigned int pozycyjny(unsigned int liczba, unsigned int podstawa, unsigned int wykladnik)        // wykorzystamy algorytm z poprzedniej listy
{                                                                                                   // został on omowiony na ostatnich cwiczeniach
    unsigned int wartosc=0, iteracja=0;
    while(iteracja!=wykladnik)
    {
        liczba=liczba/podstawa;
        iteracja++;
    }
    wartosc=liczba%podstawa;
    return wartosc;
}

bool pytanie()                                                              // funkcja która pomocnicza do zadawania pytan
{                                                                          // zwraca True gdy uzytkownik odpowie T lub t
    std::string odpowiedz;
    std::cout << "Czy chcesz wyświetlic kolejna liczbe? (t/n) : ";
    std::cin >> odpowiedz;
    if (odpowiedz == "t" || odpowiedz == "T") return(true);
    else return (false);
}

unsigned int dlugoscLiczbyWsystemie(unsigned int liczba, unsigned int podstawa)     // prosta funkcja która dla zadanej liczby i pewnej podstawy policzy maksymalna
{                                                                                  // ilosc cyfr dla danej liczby (w systemie 10) po konwersji na inny system system
    unsigned int dlugosc=0;                                                       // na poczatku zakladamy, ze nasza liczba ma 0 cyfr,
    while (liczba != 0)
    {                                                                           // sprawdzamy jaka maksymalna potega podstawy "siedzi' w naszej liczbie w systemie 10
        liczba=liczba/podstawa;                                                // zmiejszamy nasza liczbe o jeden rzad wartosc
        dlugosc++;                                                            // dodajemy do jedna cyfre do licznika
    }
    return(dlugosc);                                                        // zwracamy dlugosc, czyli wartosc naszego licznika
}

int proceduraPodstawa()                                                                    // calosc sklejona
{
    int liczba, podstawa, dlugosc;
    bool zgoda=true;
    std::cout << "Program dla podanej liczby i podstawy systemu liczenia \nbedzie wyswietlal kolejne cyfry tej liczby \npo konwersji na inny system liczbowy \n";
    std::cout << "Podaj liczbę: ";              // pobieramy liczbe
    std::cin >> liczba;
    if (liczba >= 0)                          //  zapobiega podaniu przez uzytkownika liczby ujemnej (nie potrafie zrobic tego np. dla liter)
    {
        std::cout << "Podaj podstawe: ";    // oraz podstawe systemu liczbowego
        std::cin >> podstawa;
        if (podstawa >= 0)                //  zapobiega podaniu przez uzytkownika liczby ujemnej (nie potrafie zrobic tego np. dla liter)
        {
            dlugosc=dlugoscLiczbyWsystemie(liczba, podstawa);
            for (int i=dlugosc; i>=0; i--)
            {
                if (!(i==dlugosc && pozycyjny(liczba, podstawa, dlugosc)==0))          // w przypadku, gdy pierwsza cyfra w zadanym systemie jest równa 0, to pomijamy jej wyswietlenie
                {
                    if(zgoda ) std::cout << pozycyjny(liczba, podstawa, i) << "\n";  // jesli uzytkownik potwierdil, to petla sie wykona
                    else                                                            //
                    {                                                              //
                        i=-1;                                                     // jezeli uzytkownik poda cos innego niz t lub T
                        std::cout << "Dziekuje";                                 // to program podziekuje
                    }
                    if(i>0) zgoda = pytanie();                                 // zadajemy pytanie (instrukcja if zapobiega zadaniu go podczas ostatniego wywolania petli)
                }
            }
        }
    }
    else std::cout << "Podany znak nie jest liczba dodatnia";
    return(0);
}


    // ZADANIE 4


unsigned int dlugoscLiczby(unsigned int liczba)              // prosta funkcja która dla zadanej liczby policzy ilosc jej cyfr
{
    int dlugosc=0;                                         // na poczatku zakladamy, ze nasza liczba ma 0 cyfr,
    while (liczba != 0)
    {                                                    // dopuki nie policzymy kadzej cyfry w naszej liczbie to
        liczba=liczba/10;                               // zmiejszamy nasza liczbe o jeden rzad wartosc
        dlugosc++;                                     // dodajemy do jedna cyfre do licznika dlugosci
    }
    return(dlugosc);                                 // zwracamy dlugosc, czyli wartosc naszego licznika
}

unsigned int wyswietlanieWsystemie (unsigned int a, unsigned int podstawa)      // funkcja pozwalajaca na wyswietlenie pewnej liczby w
{                                                                              // systemie liczbowym o danej podstawie
    unsigned int dlugosc=dlugoscLiczbyWsystemie(a, podstawa), wynik=0;
    for (int i=dlugosc; i>=0; i--)
    {
        int c=pozycyjny(a, podstawa, i);                                   // wykorzystujemy nasza funkcje do wyswietlania kolejnych cyfra pewnej liczby w zadanym systemie
        wynik=wynik*10+c;                                                 // z kazdym wykonaniem petli przesuwamy juz otrzymany wynik o jedna pozycje w lewo
    }
    return(wynik);
}

void odstep (unsigned int dlugosc, int iloscSpacji)                                   // funkcja ktora pozwoli nam na zachowanie rownych odstepow pomiedzy kolumnami
{                                                                                    // przy ustalonej maksymalnej odleglosci i dlugosci liczby
    for (int i=dlugosc; i<iloscSpacji; i++) std::cout << " ";
}

int tabliczkaProsto(unsigned int podstawa)                               // tabliczka mnozenia w systemie liczbowym o podanej podstawie
{
    std::cout << "  ";                                                // dwie spacje do wyrównania wyjscia w pierwszym wierszu

    for (unsigned int i=1; i<=podstawa; i++)
    {
    odstep(dlugoscLiczbyWsystemie(i, podstawa),5);                 // wykorzystuje funkcje "odstep" i dlugosc liczby aby zachowac rowne odtsepy pomiedzy kolumnami
    std::cout << wyswietlanieWsystemie(i,podstawa);               // tutaj wykonywana jest praktycznie ta sama petla, ktora byla zrobiona na poprzedniej liscie
    }                                                            // dodalem tylko funckje odstep zamaist zwyklych spacji, a liczb nie wyswietlam wprost, tylko wykorzystujac
                                                                // funkcje wyswietlania w systemie liczbowym o danej podstawie
    std::cout << "\n";
    for (unsigned int pierwsza=1; pierwsza<=podstawa; pierwsza++)
    {
        odstep(dlugoscLiczbyWsystemie(pierwsza, podstawa),2);
        std::cout << wyswietlanieWsystemie(pierwsza,podstawa);
        for (unsigned int druga=1; druga<=podstawa; druga++)
        {
            odstep(dlugoscLiczby(wyswietlanieWsystemie(pierwsza*druga, podstawa)),5);
            std::cout << wyswietlanieWsystemie(pierwsza*druga, podstawa);
        }
        std::cout << "\n";
    }
    return(0);
}

int Tabliczka()
{
    unsigned int odp;
    std::cout << "Podaj liczbe calkowita z przedzialu [2,10], \ndla ktorej wyswietlic tabliczke mnozenia: ";
    std::cin >> odp;
    std::cout << "\n";
    if (odp >= 2 && odp <= 10)tabliczkaProsto(odp);
    else std::cout << "Podany znak nie jest liczba z wymaganego zakresu";
    return 0;
}


// wszystkie zadania w jednej komendzie


int main()
{
    int odpowiedz;
    std::cout << "Które zadanie zaprezentować? \n";
    std::cin >> odpowiedz;
    std::cout << "\n";
    if (odpowiedz==1) czyPrzestepny();
    else if (odpowiedz==2) najwiekszaPotega();
    else if (odpowiedz==3) proceduraPodstawa();
    else if (odpowiedz==4) Tabliczka();
    else std::cout << "Podany znak nie jest liczba z wymaganego zakresu";
    return(0);
}

