#include <iostream>

int tabliczka()
{
    int i=1;
    std::cout << "  1 2 3\n";
    while (i<=3)
    {
        int j=1;
        std::cout << i << " ";
        while (j<=3)
        {
            std::cout << i*j << " " ;
            j++;
        }
        std::cout << "\n";
        i++;
        j=1;
    }
return(0);
}

unsigned int cata(unsigned int i)
{
    unsigned int C=1,j=1;
    while(i>0 && j<i)
    {
        C=((4*j+2)*C)/(2+j);
        j++;
    }
   return(C);
}

unsigned int dwojka(unsigned int k)
{
     unsigned int i=0;
     unsigned int t=k;
     while(k>0)
     {
        i=10*i+(k%2);
        k=k/2;
     }
     while(0==t%2)
     {
         i=i*10;
         t=t/2;
     }
    return (i);
}


int pozycyjny(unsigned int liczba, unsigned int podstawa, unsigned int wykladnik)
{
    int wartosc=0, iteracja=0;
    while(iteracja!=wykladnik)
    {
        liczba=liczba/podstawa;
        iteracja++;
    }
    wartosc=liczba%podstawa;
    return wartosc;
}


int main()
{
    tabliczka();
    std::cout << "\n" << cata(3) << "\n\n";
    std::cout << pozycyjny(324,6,2) << "\n\n";
    return 0;

}
