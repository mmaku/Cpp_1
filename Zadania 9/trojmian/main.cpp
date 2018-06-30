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

    double Wspolczynnik(int WE) const;
    Trojmian& operator+=(const Trojmian& T);
    Trojmian& operator-=(const Trojmian& T);
    double operator()(double WE) const;
};

double Trojmian::Wspolczynnik(int WE) const
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

double Trojmian::operator()(const double WE) const
{
  return (WE * (a_ * WE + b_) + c_);
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

std::istream& operator>>(std::istream& WE, Trojmian &T)
{
  double c = 0.0, b = 0.0, a = 0.0;
  while (WE && WE.peek() == ' ') WE.get();
  if (WE && WE.peek() == '[') {
    WE.get();
    WE >> c;
    if (WE && WE.peek() == ',') {
      WE.get();
      if (WE && (isdigit(WE.peek()) || (WE.peek() == '-'))) {
        WE >> b;
        if (WE && WE.peek() == ',') {
          WE.get();
          if (WE && (isdigit(WE.peek()) || WE.peek() == '-')) {
            WE >> a;
            if (WE && WE.peek() == ']') {
              WE.get();
              T = Trojmian(c, b, a);
            }
          }
        }
      }
    }
  }
  else if (WE)
    WE.setstate(std::ios_base::failbit);
  return WE;
}

bool MniejWiecej(const Trojmian& T1, const Trojmian& T2)
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
    std::cerr << "test_Trojmian ok\n";
}
