#include <iostream>
#include <sstream>
#include <assert.h>

 struct kandydat
 {
    std::string imieNazwisko;
    double srednia;
    double dzialalnosc;
    kandydat(std::string IN, double S = 0.0, double D = 0.0): imieNazwisko(IN), srednia(S), dzialalnosc(D)
        {
        }

 };

 std::ostream& operator<<(std::ostream& wy, kandydat dane)
 {
    wy << dane.imieNazwisko << "; średnia: " << dane.srednia << "; działalność: " << dane.dzialalnosc;
    return wy;
 }

 std::istream& operator>>(std::istream& in, kandydat &dane)
 {
    std::string imie, nazwisko;
    double srednia = 0.0, dzialanosc = 0.0;
    in >> imie >> nazwisko >> srednia >> dzialanosc;
    if (in) {
        dane = kandydat(imie + " " + nazwisko, srednia, dzialanosc);
    } else {
        in.setstate(std::ios_base::failbit);
    }
    return in;
 }

 kandydat pobieranieKandydata(std::string polecenie)
 {
    std::string wejscie;
    kandydat osoba("Imie Nazwisko", 0.0, 0.0);

    std::cout << polecenie;
    std::getline(std::cin, wejscie);
    std::istringstream strumien(wejscie);
    strumien >> std::skipws >> osoba;

    while (!strumien)
    {
        strumien.ignore(1000, '\n');
        strumien.clear();
        std::cout << "Coś poszło nie tak, podaj dwa imiona, a nastepnie dwa współczynniki:\n";
        std::cin.clear();
        std::getline(std::cin, wejscie);
        strumien.str (wejscie);
        strumien >> std::skipws >> osoba;
    }

    std::cout << '\n';
    return(osoba);
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool sprawdzCzyPrzechodzi(kandydat osoba, double progSrednia, double progDzialalnosc, bool srednia, bool dzialanosc)
 {
    bool wynik = true;
    if(dzialanosc && srednia && osoba.dzialalnosc >= progDzialalnosc && osoba.srednia >= progSrednia);
    else if(dzialanosc && !srednia && osoba.dzialalnosc >= progDzialalnosc);
    else if(!dzialanosc && srednia && osoba.srednia >= progSrednia);
    else if (!(dzialanosc || srednia));
    else wynik = false;
    return(wynik);
 }

  void test_sprawdzCzyPrzechodzi()
{
  kandydat a("Jan Kowalski", 3.15, 1.13);
  assert(sprawdzCzyPrzechodzi(a, 3, 1, 1, 1));
  assert(sprawdzCzyPrzechodzi(a, 3, 1, 0, 1));
  assert(sprawdzCzyPrzechodzi(a, 3, 1, 1, 0));
  assert(sprawdzCzyPrzechodzi(a, 3, 1, 0, 0));
  assert(sprawdzCzyPrzechodzi(a, 5, 5, 1, 1) == false);
  assert(sprawdzCzyPrzechodzi(a, 5, 5, 0, 1) == false);
  assert(sprawdzCzyPrzechodzi(a, 5, 5, 1, 0) == false);
  assert(sprawdzCzyPrzechodzi(a, 5, 5, 0, 0));
  kandydat b("Jan Nowak", 1.3, 5);
  assert(sprawdzCzyPrzechodzi(b, 1, 4, 1, 1));
  assert(sprawdzCzyPrzechodzi(b, 1, 4, 0, 1));
  assert(sprawdzCzyPrzechodzi(b, 1, 4, 1, 0));
  assert(sprawdzCzyPrzechodzi(b, 1, 4, 0, 0));
  assert(sprawdzCzyPrzechodzi(b, 5, 6, 1, 1) == false);
  assert(sprawdzCzyPrzechodzi(b, 5, 6, 0, 1) == false);
  assert(sprawdzCzyPrzechodzi(b, 5, 6, 1, 0) == false);
  assert(sprawdzCzyPrzechodzi(b, 5, 6, 0, 0));
}

bool pytanie(std::string polecenie)
{
    std::string odpowiedz;
    std::cout << polecenie << " (t/n) : ";
    std::cin >> odpowiedz;
    if (odpowiedz == "t" || odpowiedz == "T") return(true);
    else return (false);
}

double pobieranieZmiennych(std::string polecenie)
 {
    std::string wejscie;
    double liczba = 0.0;

    std::cout << polecenie;
    std::cin >> wejscie;
    std::istringstream strumien(wejscie);
    strumien >> liczba;

    while (!strumien)
    {
        strumien.ignore(1000, '\n');
        strumien.clear();
        std::cout << "Podana wartość nie jest liczbą."
                  << "\nPodaj liczbę jeszcze raz: ";
        std::cin >> wejscie;
        strumien.str (wejscie);
        strumien >> liczba;
    }

    std::cout << '\n';
    return(liczba);
 }


void sprawdzCzyPrzechodziPROCEDURA(kandydat osoba)
{
    double progSrednia = 0.0, progDzialalnosc = 0.0;
    bool odpowiedzSrednia = pytanie("Czy chcesz podać próg liczbowy dla średniej?");
    if(odpowiedzSrednia)
        progSrednia = pobieranieZmiennych("Podaj ten próg: ");

    bool odpowiedzDzial = pytanie("Czy chcesz podać próg liczbowy dla wsk. działalności pozaszkolnej?");
    if(odpowiedzDzial)
        progDzialalnosc = pobieranieZmiennych("Podaj ten próg: ");

    if(sprawdzCzyPrzechodzi(osoba, progSrednia, progDzialalnosc, odpowiedzSrednia, odpowiedzDzial))
        std::cout << "Podany kandydat przechodzi wszystkie testy!\n";
    else std::cout << "Niestety, kandydat nie przechodzi testów...\n";
}

int main()
{
    test_sprawdzCzyPrzechodzi();
    kandydat A = pobieranieKandydata("Podaj dane kandydata w formacie \"Imię Nazwisko Średnie Współczynnik\":\n");
    sprawdzCzyPrzechodziPROCEDURA(A);
    return 0;
}
