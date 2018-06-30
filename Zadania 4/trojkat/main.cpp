#include <iostream>
#include <math.h>
#include <assert.h>



/* ZADANIE 1



        |\ <- beta
        | \
        |  \
        |   \
      a |    \ c
        |     \
        |      \
        |_______\<- alfa
            b

*/

double deg2rad (double deg)
{
    return((deg/180.0) * M_PI);
}

int obliczTrojkatProsto(double bokA, double katAlfa)
{
    assert(bokA > 0 && katAlfa > 0 && katAlfa < 90);
    double bokB, bokC, katBeta;

    bokB = bokA * 1.0/(tan(deg2rad(katAlfa)));
    bokC = bokA* 1.0/(sin (deg2rad(katAlfa)));
    katBeta = 90.0 - katAlfa;

    if (katAlfa != 45.0)
    {
        std::cout << "Pierwsza z przyprostokątnych ma długość: " << bokA << ",\ndruga z przyprostokątnych ma długość: " << bokB << ",\na przeciwprostakątna ma długość: " << bokC << ".\n\n";
        std::cout << "Kąt naprzeciw boku o dł. " << bokA << " ma wartość " << katAlfa << " stopni,\na kąt naprzciw boku o dł. " << bokB << " ma wartość " << katBeta << " stopni.\n";
    }
    else std::cout << "Boki przy kącie prostym mają długość: " << bokA << ",\na oba kąty ostre mają wartość 45 stopni.\n";
    return(0);
}

int main()
{
    double bokA = -1.0, katAlfa = -1.0;

    std::cout << "Podaj długość jednego z boków trójkąta: ";
    std::cin >> bokA;
    while (std::cin.fail() || bokA <= 0.0)
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Podana wartość nie jest liczbą dodatnią...\nPodaj liczbę jeszcze raz: ";
        std::cin >> bokA;
    }

    std::cout << "Podaj miarę jednego z kątów trójkąta (w stopniach): ";
    std::cin >> katAlfa;
    while (std::cin.fail() || katAlfa <= 0.0 || katAlfa >= 90.0)
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Podana wartość nie jest liczbą wartością z zakresu (0,90)...\nPodaj liczbę jeszcze raz: ";
        std::cin >> katAlfa;
    }
    std::cout << "\n";
    obliczTrojkatProsto(bokA, katAlfa);
    return(0);
}
