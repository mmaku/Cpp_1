#include <iostream>
#include <math.h>
#include <assert.h>


// ZADANIE 3


double ExpMkw(double x)
{
    return (pow(1/M_E,x*x));            // funkcja pow z biblioteki math.h pozwalająca na podnoszenie liczb do niecałkowitych potęg
}

double poleTrapezu(double leweOgraniczenie, double praweOgraniczenie)
{
    return((ExpMkw(leweOgraniczenie)+ExpMkw(praweOgraniczenie))*(praweOgraniczenie-leweOgraniczenie)/2);
}

double polePodWykresem(double zakres, double liczbaWezlow)
{
    assert(liczbaWezlow > 1);
    assert(zakres >= 0);
    double suma=0, dlugoscPododcinka=zakres/(liczbaWezlow-1), leweOgraniczenie=0;
    for (int i=1; i < liczbaWezlow; i++)
    {
        suma=suma+poleTrapezu(leweOgraniczenie, leweOgraniczenie+dlugoscPododcinka);
        leweOgraniczenie=leweOgraniczenie+dlugoscPododcinka;
    }
    return(suma);
}

int main()
{
    double zakres = -1.0, liczbaWezlow = -1.0;

    std::cout << "Podaj ograniczenie całki z e^-(x^2), od 0, do: ";
    std::cin >> zakres;
    while (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Podana wartość nie jest liczbą ...\nPodaj ograniczenie jeszcze raz: ";
        std::cin >> zakres;
    }
    zakres = fabs(zakres);


    std::cout << "\n";
    std::cout << "Podaj liczbę węzłów (n>1) do numerycznego obliczenia całki \n(przy podaniu liczby niecałkowitej zostanie ona zaokrąglona w dół): ";
    std::cin >> liczbaWezlow;
    while (std::cin.fail() || liczbaWezlow < 2.0 )
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Podana wartość nie jest liczbą dodatnią...\nPodaj liczbę jeszcze raz: ";
        std::cin >> liczbaWezlow;
    }
    liczbaWezlow=floor(liczbaWezlow);


    std::cout << "\n";
    std::cout << "Całka z funkcji e^-(x^2) od 0 do " << zakres << " jest równa " << polePodWykresem(zakres, liczbaWezlow) << "\n";
    return(0);
}
