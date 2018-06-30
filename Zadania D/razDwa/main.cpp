#include <iostream>
#include <cassert>

void RazyDwa(int* start, int* koniec, int* c)
{
    assert(start && koniec && c);
    if (koniec <= start);

    if (start < koniec)
    {
        int i = 0;
        int* d = start;
        do
        {
            i = i+1;
            d = d+1;
        }
        while (d < koniec);

        for(int j = 0; j < i; j++)
        {
            *(c+j) = 2*(*(start+j));
        }
    }
}

auto test_RazyDwa() -> void;

int main(void)
{
    test_RazyDwa();
    return 0;
}

auto test_RazyDwa() -> void
{
    int r[] ={1,2,3,4,5,6,7};
    int t[] ={1,2,3,4,5,6,7};
    int w1[]={0,0,0,0,0,0,0};
    int w2[]={0,0,0};
    int w3[]={0,0,0,0,0};
    RazyDwa(t,t+7,w1);      // obliczenia dla ca³ego t, wyniki do w1 od pocz¹tku
    for(int i=0; i<7; ++i)
    {
        assert( r[i]==t[i]);
        assert(w1[i]==t[i]*2);
    }

    RazyDwa(t+2,t+5,w2);    // obliczenia dla podci¹gu o indeksach 2,3,4
                            // wyniki do w2 od pocz¹tku
    for(int i=2; i<5; ++i)
    {
        assert( r[i]==t[i]);
        assert(w2[i-2]==t[i]*2);
    }

    RazyDwa(t+2,t+5,w3+1);  // obliczenia dla podci¹gu o indeksach 2,3,4
                            // wyniki do w3 od indeksu 1, w takim razie
                            // wartoœci w3[0] i w3[4] niezmieniane
    assert(w3[0]==0);
    assert(w3[4]==0);
    for(int i=2; i<5; ++i)
    {
        assert( r[i]==t[i]);
        assert(w3[i-1]==t[i]*2);
    }

    RazyDwa(t+2,t+5,t+2);   // obliczenia dla podci¹gu o indeksach 2,3,4
                            // wyniki z powrotem do t na miejsca, sk¹d by³y
                            // brane liczby do obliczeñ
    assert(t[0]==1);
    assert(t[1]==2);
    assert(t[2]==6);
    assert(t[3]==8);
    assert(t[4]==10);
    assert(t[5]==6);
    assert(t[6]==7);

    std::cerr<<"test_RazyDwa ok\n";
}
