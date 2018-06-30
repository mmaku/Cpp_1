#include <iostream>
#include <string>
#include <cassert>
#include <sstream>

void lista_znakow_minus128_plus128()
{
    for(int numer_znaku =- 128; numer_znaku < 128; numer_znaku++)
    {
        std::cout << "\n" << numer_znaku << " " << char(numer_znaku);
    }
}

std::string usuwanieSpacji(std::string wejscie)
{
    if (!wejscie.empty())
    {
        while(wejscie.back() == ' ')
            wejscie.pop_back();

        for (unsigned int i=0; i < wejscie.length(); i++)
        {
            if (wejscie[i] == ' ') wejscie[i] = '\0';
            else i = wejscie.length();
        }

        for (unsigned int i=0; i < wejscie.length(); i++)
            if (wejscie[i] == ' ' && wejscie[i+1] == ' ') wejscie[i] = '\0';
    }
    return (wejscie);
}


void test_usuwanieSpacji()
{
    assert(usuwanieSpacji("   dsdas    ads       asd ") == "dsdas ads asd");
    assert(usuwanieSpacji("Michał  Łukasz") == "Michał Łukasz");
    assert(usuwanieSpacji("  dwa słowa    ") == "dwa słowa");
    assert(usuwanieSpacji("  więcej znaków łł  ") == "więcej znaków łł");
    assert(usuwanieSpacji("Michał") == "Michał");
}

std::string ostatniWyraz(std::string wejscie, bool usuwanie)
{
    wejscie = usuwanieSpacji(wejscie);
    int i = wejscie.length(), dlugoscNazwiska = 0;

    while(!(wejscie[i] == ' ' || i == 0))
    {
        dlugoscNazwiska++;
        i--;
    }

//  std::cout << "Długość: " << dlugoscNazwiska << "\ni :" << i << '\n';        // kontrola

    if (usuwanie) wejscie.assign(wejscie.begin(), wejscie.end()-dlugoscNazwiska);
    else wejscie.erase(wejscie.begin(), wejscie.end()-dlugoscNazwiska);

    return(wejscie);
}

void test_ostatniWyraz()
{
    assert(ostatniWyraz("   dsdas    ads       asd ", 0) == " asd");
    assert(ostatniWyraz("test 1 2 3", 0) == " 3");
    assert(ostatniWyraz("  dwa słowa    ", 1) == "dwa");
    assert(ostatniWyraz("  więcej znaków łł  ", 0) == " łł");
    assert(ostatniWyraz("Michał Makowski", 1) == "Michał");
}

bool sprawdzZnak (char znak)                            // sprawdzam, czy char, to 'zwykla' litera
{
    if (( 65 <= znak && znak <= 90) ||
        ( 97 <= znak && znak <= 122 )) return(true);
    return(false);
}

std::string tworzenieInicjalow (std::string imiona)
{
    int dlugoscWejscia = imiona.length()-1;
    for(int i=dlugoscWejscia; i > 0 ; i--)     // można użyć funkcji find_last_of
    {
        if(i == dlugoscWejscia
         && imiona.at(i-1) == ' '
         && sprawdzZnak(imiona.at(i)))
         {
            imiona.push_back('.');
            i--;
         }

        else if(i == dlugoscWejscia
             && imiona.at(i-2) == ' '
             && !sprawdzZnak(imiona.at(i-1)))
        {
            imiona.push_back('.');
            i--;
        }

        else if(imiona.at(i-1) == '.' );
        else if(sprawdzZnak(imiona.at(i-1)))
        {
            if((imiona[i-2] == ' ' && imiona[i] == ' ') || (i == 1 && imiona[i] == ' '))
            {
                imiona.insert(i, ".");
                i = i-1;
            }
            else if(imiona[i-2] == ' ' || i == 1)
            {
                imiona[i] = '.';
                i = i-1;
            }
            else if(imiona[i] == ' ');
            else imiona[i] = '\0';
        }

        else
        {
            if((imiona[i-3] == ' ' && imiona[i] == ' ') || (i == 2 && imiona[i] == ' '))
            {
                imiona.insert(i, ".");
                i = i-2;
            }
            else if(imiona[i-3] == ' ' || i == 2)
            {
                imiona[i] = '.';
                i = i-2;
            }
            else if(imiona[i] == ' ')
            {
                imiona[i-1] = '\0';
                i--;
                imiona[i-1] = '\0';
            }
            else
            {
                imiona[i] = '\0';
                i--;
                imiona[i] = '\0';
            }

        }

    }
    return(imiona);
}

void test_tworzenieInicjalow()
{
    assert(tworzenieInicjalow("Jakub GG") == "J. G.");
    assert(tworzenieInicjalow("H. S.") == "H. S.");
    assert(tworzenieInicjalow("M. Makowski") == "M. M.");
    assert(tworzenieInicjalow("Michał Makowski") == "M. M.");
}

std::string konwersja (std::string wejscie)
{
    std::string nazwisko = ostatniWyraz(wejscie, 0),
                inicjaly = tworzenieInicjalow(ostatniWyraz(wejscie, 1));
    return(inicjaly + nazwisko);
}

void test_Konwersja()
{
    assert(tworzenieInicjalow("Jakub GG") == "J. GG");
    assert(tworzenieInicjalow("H. Sienkiewicz") == "H. Sienkiewicz");
    assert(tworzenieInicjalow("M. Makowski") == "M. Makowski");
    assert(tworzenieInicjalow("Michał Makowski") == "M. Makowski");
}

void TEST()
{
    test_Konwersja();
    test_ostatniWyraz();
    test_tworzenieInicjalow();
    test_usuwanieSpacji();
}

int main()
{
//    TEST();
//    lista_znakow_minus128_plus128();
    std::string wejscie;
    std::cout << "Podaj imię (imiona) i nazwisko, które chcesz skrócić: ";
    std::getline(std::cin, wejscie);
    std::cout << konwersja(wejscie);
    return 0;
}
