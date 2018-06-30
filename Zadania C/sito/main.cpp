#include <iostream>
#include <vector>
#include <cassert>

bool czyDopisac(int WE)
{
    assert(2 <= WE);
    bool WY = true;
    for(int i = WE/2; i >= 2; i--)
    {
        WY &= (WE%i != 0);
    }
    return WY;
}

std::vector<unsigned long long int> SitoV1(unsigned long long int WE)
{
    assert(WE >= 2);
    std::vector<unsigned long long int> WY;
    for(unsigned long long int i = 2; i <= WE; i++)
    {
        if(czyDopisac(i))
        {
            WY.push_back(i);
        }
    }
    return WY;
}

std::vector<unsigned long long int> SitoV2(unsigned long long int N)
{
      std::vector<bool> czy_pierwsza(N + 1, true); // nasze sito
      std::vector<unsigned long long int> WY; // lista liczb pierwszych
      czy_pierwsza[0] = czy_pierwsza[1] = false;

      for (unsigned long long int i = 2; i <= N; ++i)
      {
            if (czy_pierwsza[i])
            {
                    WY.push_back(i);
                    for(unsigned long long j = i; i * j <= N; ++j)
                    {
                        czy_pierwsza[i*j] = false;
                    }
            }
      }
      return WY;
}

template<typename T>
void WypiszVector(std::vector<T>/*&*/ WE)
{
    for(auto& EL : WE)
    {
        std::cout << EL << ' ';
    }
}

void test_sito();


int main()
{
 //   WypiszVector(SitoV1(50000));
 //   WypiszVector(SitoV2(50000));
    test_sito();
    return 0;
}

void test_sito()
{
  std::vector<unsigned long long> P0 = SitoV2(30);
  std::vector<unsigned long long> P1{2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
  assert(P0 == P1);
  std::cerr << "testy ok!";
}
