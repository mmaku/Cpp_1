#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>

int CollatzIndex(int p, int q, int k)
{
    bool czyDalej = true;
    std::vector<int> ciag{k};
    int wy = 0;

    while(czyDalej)
    {
        ((k%2) ? k = p*k+q : k/=2); : ((k%2) ? k = p*k+q : k/=2);

        ciag.push_back(k);

        for (unsigned int i = 0; 1+i < ciag.size(); i++)
        {
            std::cerr << i << ' '<< ciag.size() << ' '<< wy << ' '<< ciag[i] << ' '<< k <<'\n';
            if (ciag[i] == k)
            {
                czyDalej = false;
                wy = i;
                std::cerr << wy;
                break;
            }
        }
    }
    return wy+3;
}

void test_CollatzIndex();

int main()
{
    test_CollatzIndex();
    return 0;
}

void test_CollatzIndex()
  {
assert(CollatzIndex(3,1,27)==112);
  assert(CollatzIndex(3,1,1)==3);
  assert(CollatzIndex(3,1,6)==9);
  assert(CollatzIndex(3,1,11)==15);
  assert(CollatzIndex(3,1,-5)==5);
  assert(CollatzIndex(3,7,1)==7);
  assert(CollatzIndex(3,7,7)==3);
  }
