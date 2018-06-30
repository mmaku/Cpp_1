#include <iostream>
#include <assert.h>
#include <math.h>
#include <sstream>

int GCD(int a, int b)
{
    int c;
    while ( a != 0 )
    {
        c = a;
        a = b%a;
        b = c;
    }
    return b;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Wymierna
{
    private:
        int licznik_;
        int mianownik_;

    public:
        Wymierna(int licznik = 0, int mianownik = 1)
            : licznik_(licznik), mianownik_(mianownik)
            {
                assert(mianownik != 0);
            }

        int Licznik() const;
        int Mianownik () const;
        Wymierna& operator+=(const Wymierna& W);
        Wymierna& operator-=(const Wymierna& W);
        Wymierna& operator*=(const Wymierna& W);
        Wymierna& operator/=(const Wymierna& W);
};

int Wymierna::Licznik() const
{
    int znak = 1;
    if (licznik_ * mianownik_ < 0) znak = -1;
    return znak * licznik_ / GCD(licznik_, mianownik_);
}

int Wymierna::Mianownik() const
{
    return abs(mianownik_/GCD(licznik_, mianownik_));
}

Wymierna& Wymierna::operator+=(const Wymierna& W)
{
    if (mianownik_ != W.Mianownik())
    {
        licznik_ = licznik_ * W.Mianownik() + mianownik_ * W.Licznik();
        mianownik_ = mianownik_ * W.Mianownik();
    } else {
        licznik_ += W.Licznik();
    }
    return *this;
}

Wymierna& Wymierna::operator-=(const Wymierna& W)
{
    if (mianownik_ != W.Mianownik())
    {
        licznik_ = licznik_ * W.Mianownik() - mianownik_ * W.Licznik();
        mianownik_ = mianownik_ * W.Mianownik();
    } else
        licznik_ -= W.Licznik();
    return *this;
}

Wymierna& Wymierna::operator*=(const Wymierna& W)
{
    licznik_ *= W.Licznik();
    mianownik_ *= W.Mianownik();
    return *this;
}

Wymierna& Wymierna::operator/=(const Wymierna& W)
{
    assert(W.licznik_ != 0);
    licznik_ *= W.Mianownik();
    mianownik_ *= W.Licznik();
    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Wymierna operator+(const Wymierna& W1, const Wymierna& W2)
{
    Wymierna WY(W1);
    WY+=W2;
    return WY;
}

Wymierna operator-(const Wymierna& W1, const Wymierna& W2)
{
    Wymierna WY(W1);
    WY-=W2;
    return WY;
}

Wymierna operator*(const Wymierna& W1, const Wymierna& W2)
{
    Wymierna WY(W1);
    WY*=W2;
    return WY;
}

Wymierna operator/(const Wymierna& W1, const Wymierna& W2)
{
    Wymierna WY(W1);
    WY/=W2;
    return WY;
}

bool operator==(const Wymierna& W1, const Wymierna& W2)
{
    return (W1.Licznik()==W2.Licznik() && W1.Mianownik() == W2.Mianownik());
}

std::istream& operator>>(std::istream& WE, Wymierna& W)
{
    int licznik = 0;
    int mianownik = 0;
    WE >> licznik;
    if (WE && WE.peek() == '/')
    {
        WE.get();
        if (WE && (WE.peek() == '-' || isdigit(WE.peek())))
        {
            WE >> mianownik;
            if (WE && mianownik != 0)
            {
                W = Wymierna(licznik, mianownik);
            }
        }
    }
    else if (WE)
        WE.setstate(std::ios_base::failbit);
    return WE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

auto test_Wymierna() -> void;


int main()
{
    test_Wymierna();
    return 0;
}

auto test_Wymierna(void) -> void
{
    Wymierna w1(2,-4);
    assert(w1.Licznik()==-1);
    assert(w1.Mianownik()==2);

    Wymierna w2;
    assert(w2.Licznik()==0);
    assert(w2.Mianownik()==1);

    Wymierna w3(2);
    assert(w3.Licznik()==2);
    assert(w3.Mianownik()==1);

    w1+=w3;
    assert(w1.Licznik()==3);
    assert(w1.Mianownik()==2);

    w1+=w3+=Wymierna(4,8);
    assert(w3.Licznik()==5);
    assert(w3.Mianownik()==2);
    assert(w1.Licznik()==4);
    assert(w1.Mianownik()==1);

    w1-=Wymierna(4,8);
    assert(w1.Licznik()==7);
    assert(w1.Mianownik()==2);

    w1=Wymierna(9,4);
    w1*=Wymierna(16,15);  // 9/4 * 16/15 = 3/1 * 4/5 = 12/5 = 144/60
    assert(w1.Licznik()==12);
    assert(w1.Mianownik()==5);

    w1/=Wymierna(16,15);
    assert(w1.Licznik()==9);
    assert(w1.Mianownik()==4);

    w1=3;
    assert(w1.Licznik()==3);
    assert(w1.Mianownik()==1);

    assert(w1==3);

    std::istringstream we("-6/8 10/-14");
    we >> w1 >> w2;
    assert(we);
    assert(w1==Wymierna(-3,4));
    assert(w2==Wymierna(-5,7));

    std::istringstream we2("-6 /8");
    we >> w1;
    assert(!we);

    w3=w1+w2;
    assert(w3==Wymierna(-41,28));
    w3=w1-w2;
    assert(w3==Wymierna(-1,28));
    w3=w1*w2;
    assert(w3==Wymierna(15,28));
    w3=w1/w2;
    assert(w3==Wymierna(21,20));

    std::cerr << "test_Wymierna ok\n";
}
