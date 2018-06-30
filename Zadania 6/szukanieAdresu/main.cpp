#include <iostream>
#include <sstream>
#include <string>
#include <assert.h>

std::string wczytywanie(void)
{
    std::string napis;
    std::cout << "Podaj wyrażenie w którym chcesz znaleźć adres e-mail\n";
    std::getline (std::cin, napis);
    return napis;
}

std::string znajdzAdres(std::string napis)
{
    int gdzieMalpa = 0;
    int dlugoscNapisu = napis.size();

    std::ostringstream EMAIL;
    std::string adresEMAIL;


    for(int i=0; (i!=dlugoscNapisu || napis[i]=='@'); i++) // sprawdzam czy jest malpa
    {
        if(napis[i] == '@') gdzieMalpa=i+1;
    }

    if(gdzieMalpa!=0)
    {
        int poczatekAdresu = gdzieMalpa;

        do                                                 // znajduje poczatek adresu
        {
            poczatekAdresu=poczatekAdresu-1;
        } while(poczatekAdresu!=0 && napis[poczatekAdresu]!=' ');

        int koniecAdresu=0;
        if(poczatekAdresu!=0) koniecAdresu=poczatekAdresu+1;

        do                                                 // zczytuje od spacji do spacji
        {
            EMAIL << napis[koniecAdresu];
            koniecAdresu++;
        } while(koniecAdresu!=dlugoscNapisu && napis[koniecAdresu]!=' ');

    adresEMAIL=EMAIL.str();
    }

    return adresEMAIL;
}

void test()
{
    assert(znajdzAdres("asd@asjdg")=="asd@asjdg");
    assert(znajdzAdres("qqqq 0987 asd@asjdg")=="asd@asjdg");
    assert(znajdzAdres("111 1234 123@ 456@gmail.com")=="456@gmail.com");

}


int main(void)
{

    std::cout << "\n" << znajdzAdres(wczytywanie());
    test();
    std::cout<< '\n';
    return 0;
}
