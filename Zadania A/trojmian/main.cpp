#include <iostream>
#include <cassert>
#include <cmath>
#include <sstream>

const double DOKLADNOSC = 1e-6;

bool equal(double X, double Y)
{
    return fabs(X-Y) < DOKLADNOSC;
}

class Trojmian
{
    private:
        double a_, b_, c_;

    public:
        Trojmian(double c = 0.0, double b = 0.0, double a = 0.0)
            : a_(a), b_(b), c_(c)
            {

            }

    double Wspolczynnik(const int& WE) const;
    Trojmian& operator+=(const Trojmian& T);
    Trojmian& operator-=(const Trojmian& T);
    Trojmian& operator*=(const int& liczba);
    double operator()(const double& WE) const;
    auto Pierwiastki(double& Z1, double& Z2) const -> int;
};

double Trojmian::Wspolczynnik(const int& WE) const
{
    assert(0 <= WE && WE <= 3);
    double WY;

    switch(WE)
    {
        case 2: WY = a_; break;
        case 1 : WY = b_; break;
        case 0 : WY = c_; break;
    }

    return WY;
}

Trojmian& Trojmian::operator+=(const Trojmian& T)
{
    a_ += T.Wspolczynnik(2);
    b_ += T.Wspolczynnik(1);
    c_ += T.Wspolczynnik(0);
    return *this;
}

Trojmian& Trojmian::operator-=(const Trojmian& T)
{
    a_ -= T.Wspolczynnik(2);
    b_ -= T.Wspolczynnik(1);
    c_ -= T.Wspolczynnik(0);
    return *this;
}

Trojmian& Trojmian::operator*=(const int& liczba)
{
    a_ *= liczba;
    b_ *= liczba;
    c_ *= liczba;
    return *this;
}

double Trojmian::operator()(const double& WE) const
{
  return (WE * (a_ * WE + b_) + c_);
}

auto Trojmian::Pierwiastki(double& Z1, double& Z2) const -> int
{
    double WY = 0.0;
    if (a_ != 0)
    {
        double delta = b_ * b_ - 4 * a_ * c_;
        if (delta < 0)
        {
            Z1 = 0.0/0.0;
            Z2 = 0.0/0.0;
            WY = 0;
        }
        else if (delta == 0)
        {
            Z1 = Z2 = -b_ / (2 * c_);
            WY = 1;
        }
        else
        {
            if (b_ > 0)
            {
                Z1 = ((2 * c_) / (-b_ - sqrt(delta)));
                Z2 = ((-b_ - sqrt(delta)) / (2 * a_));
            }
            else
            {
                Z1 = ((-b_ + sqrt(delta)) / (2 * a_));
                Z2 = ((2 * c_) / (-b_ + sqrt(delta)));
            }
            WY = 2;
        }
    }
    else if (b_ != 0)
    {
        Z1 = Z2 = -c_ / b_;
        WY = 1;
    }
    else if (c_ != 0)
    {
        Z1 = Z2 = 0.0/0.0;
        WY = 0;
    }
    else
    {
        Z1 = Z2 = 0.0/0.0;
        WY = 1;
    }
    return WY;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Trojmian operator+(const Trojmian& T1, const Trojmian& T2)
{
    Trojmian WY(T1);
    WY+=T2;
    return WY;
}

Trojmian operator-(const Trojmian& T1, const Trojmian& T2)
{
    Trojmian WY(T1);
    WY-=T2;
    return WY;
}

Trojmian operator-(Trojmian T)
{
  return T*=(-1.0);
}

Trojmian operator+(const Trojmian& T)
{
    return T;
}

Trojmian operator*(const double& liczba, const Trojmian& T)
{
    return Trojmian(liczba*T.Wspolczynnik(0), liczba*T.Wspolczynnik(1), liczba*T.Wspolczynnik(2));
}

Trojmian operator*(const Trojmian& T, const double& liczba)
{
    return Trojmian(liczba*T.Wspolczynnik(0), liczba*T.Wspolczynnik(1), liczba*T.Wspolczynnik(2));

}

auto operator<(const Trojmian& T1, const Trojmian& T2) -> bool
{
    bool WY = false;
    if(T1.Wspolczynnik(2)<T2.Wspolczynnik(2))
        WY = true;
    else if (equal(T1.Wspolczynnik(2), T2.Wspolczynnik(2)))
    {
        if(T1.Wspolczynnik(1)<T2.Wspolczynnik(1))
            WY = true;
        else if (equal(T1.Wspolczynnik(1), T2.Wspolczynnik(1)))
        {
            WY = (T1.Wspolczynnik(0)<T2.Wspolczynnik(0));
        }
    }
    return WY;
}

auto operator>(const Trojmian& T1, const Trojmian& T2) -> bool
{
    return (T2<T1);
}

auto operator>=(const Trojmian& T1, const Trojmian& T2) -> bool
{
    return !(T1<T2);
}

auto operator<=(const Trojmian& T1, const Trojmian& T2) -> bool
{
    return !(T1>T2);
}

auto operator==(const Trojmian& T1, const Trojmian& T2) -> bool
{
    return (T1<=T2) && (T1>=T2);
}

auto operator!=(const Trojmian& T1, const Trojmian& T2) -> bool
{
    return !(T1==T2);
}

std::istream& operator>>(std::istream& WE, Trojmian& T)
{
    char P1, P2, N1, N2;
    double X0 = 0.0;
    double X1 = 0.0;
    double X2 = 0.0;
    WE >> N1 >> std::noskipws >> X0 >> P1 >> X1 >> P2 >> X2 >> N2;
    if (WE)
    {
        if (N1 == '['
         && N2 == ']'
         && P1 == ','
         && P2 == ',')
        {
            T = Trojmian(X0, X1, X2);
        }
        else
        {
            WE.setstate(std::ios_base::failbit);
        }
    }
    return WE;
}

auto MniejWiecej(const Trojmian& T1, const Trojmian& T2) -> bool
{
    return(equal(T1.Wspolczynnik(1),T2.Wspolczynnik(1))&&
           equal(T1.Wspolczynnik(2),T2.Wspolczynnik(2))&&
           equal(T1.Wspolczynnik(3),T2.Wspolczynnik(3)));
}

auto test_Trojmian() -> void;

int main()
{
    test_Trojmian();
    return 0;
}


auto test_Trojmian() -> void
{
    Trojmian t1(1.0,2.0,3.0);
    assert(t1.Wspolczynnik(0)==1.0);
    assert(t1.Wspolczynnik(1)==2.0);
    assert(t1.Wspolczynnik(2)==3.0);
    assert(t1(0)==1.0);
    assert(t1(1)==6.0);
    Trojmian t1a;
    t1a=t1+Trojmian(2.0,3.0,4.0);
    assert(t1a.Wspolczynnik(0)==3.0);
    assert(t1a.Wspolczynnik(1)==5.0);
    assert(t1a.Wspolczynnik(2)==7.0);
    assert(MniejWiecej(t1,t1a-Trojmian(2.0,3.0,4.0)));
    Trojmian t1b=t1a;
    t1b-=Trojmian(2.0,3.0,4.0);
    assert(MniejWiecej(t1,t1b));
    t1+=Trojmian(2.0,3.0,4.0);
    assert(t1.Wspolczynnik(0)==3.0);
    assert(t1.Wspolczynnik(1)==5.0);
    assert(t1.Wspolczynnik(2)==7.0);
    assert(t1(0)==3.0);
    assert(t1(1)==15.0);
    assert(MniejWiecej(t1,Trojmian(3.0,5.0,7.0)));
    assert(!(MniejWiecej(t1,Trojmian(3.5,5.5,7.5))));
    Trojmian t2;
    t2=5.0;
    assert(t2.Wspolczynnik(0)==5.0);
    assert(t2.Wspolczynnik(1)==0.0);
    assert(t2.Wspolczynnik(2)==0.0);
    std::istringstream we("[1.0,2.0,3.0][3.5,4.5,-5.5]");
    we >> t1 >> t2;
    assert(we);
    assert(MniejWiecej(t1,Trojmian(1.0,2.0,3.0)));
    assert(MniejWiecej(t2,Trojmian(3.5,4.5,-5.5)));
    t1a= +t1;
    t1b= -t1;
    assert(MniejWiecej(t1a,Trojmian(1.0,2.0,3.0)));
    assert(MniejWiecej(t1b,Trojmian(-1.0,-2.0,-3.0)));
    t1a*= 4.0;
    t1b*= -3.0;
    assert(MniejWiecej(t1a,Trojmian(4.0,8.0,12.0)));
    assert(MniejWiecej(t1b,Trojmian(3.0,6.0,9.0)));
    Trojmian t2a=t2*4;
    Trojmian t2b=-2*t2;
    assert(MniejWiecej(t2a,Trojmian(14.0,18.0,-22.0)));
    assert(MniejWiecej(t2b,Trojmian(-7.0,-9.0,11.0)));
    assert(t1a>t1b);
    assert(t1a<=t1a);
    assert(t2a==t2a);
    assert(t1a!=t2a);
    double Z1=0.0, Z2=0.0;
    t1=Trojmian(0,3.0,6.0);
    assert(t1.Pierwiastki(Z1, Z1)==2);
    assert(Z1 == -0.5 && Z2 == 0);

    std::cerr << "test_Trojmian ok\n";
}
