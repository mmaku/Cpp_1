#include <iostream>
#include <string>
#include <assert.h>
#include <cctype>

std::string wczytywanie(void)
{
    std::string napis;
    std::cout << "Podaj wyrażenie w którym chcesz zamienić separator dziesiętny z kropki na przecinek:\n";
    std::getline (std::cin,napis);
    return napis;
}

std::string zamiana(std::string napis)
{
    std::string wyjscie = napis;
    int dlugoscNapisu = (napis).size();

    for(int i=0; i!=dlugoscNapisu; i++)
    {
        if(napis[i]=='.' && isdigit(napis[i-1])!=0 && isdigit(napis[i+1])!=0) napis[i] = ',';
    }
    return napis;
}

void test()
{
    assert(zamiana("Liczba pi ma wartosc 3.14. Liczba e ma natomiast wartosc 2.71")=="Liczba pi ma wartosc 3,14. Liczba e ma natomiast wartosc 2,71");
    assert(zamiana("1.01, 1.92399, 1231,1.237.5")=="1,f01, 1,92399, 1231,1,237,5");
}


int main(void)
{
    std::cout << zamiana(wczytywanie());
    test();
    return 0;
}
