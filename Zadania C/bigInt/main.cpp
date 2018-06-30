#include <iostream>
#include <vector>
#include <stdlib.h>     /* atoi */

const long long int dwa_32 = 4294967295; // 2^32-1

class BigInt
{
    private:
        std::vector<unsigned int> liczba_;
        bool dodatnia = true;

    public:
        BigInt(long long int liczba);
        BigInt(std::string liczbaJakoNapis);

        int size() const;
        unsigned int operator[](int WE) const;
        unsigned int& operator[](int WE);
        bool czyDodatnia() const;
        void zmienZnak();

        bool operator<(const BigInt& A) const;
        bool operator>(const BigInt& A) const;
        bool operator>=(const BigInt& A) const;
        bool operator<=(const BigInt& A) const;
        bool operator==(const BigInt& A) const;
        bool operator!=(const BigInt& A) const;

        BigInt operator+() const;
        BigInt operator-() const;
        BigInt operator+=(const BigInt& B);
        BigInt operator-=(const BigInt& B);
};

BigInt::BigInt(long long int liczba = 0)
{
    dodatnia = (liczba >= 0);
    liczba = llabs(liczba);
    if(liczba > dwa_32)
    {
        for(long long int i = 1; i <= liczba/dwa_32; i++)
        {
            liczba_.push_back(dwa_32);
        }
        liczba_.push_back(liczba % dwa_32);

    }
    liczba_.push_back(liczba);
}

BigInt::BigInt(std::string liczbaJakoNapis)
{
    std::string TEMPstr;
    long long int TEMPllint1 = 0, TEMPllint2 = 0;
    int ileDOkonca = liczbaJakoNapis.size();

    while(liczbaJakoNapis.empty())
    {
    TEMPstr = liczbaJakoNapis.substr(std::max(0, ileDOkonca));

    TEMPllint2 = atoll(TEMPstr.c_str());
    TEMPllint1 += TEMPllint2;

    if(TEMPllint1 <= dwa_32)
    {
        liczba_.push_back(TEMPllint1);
        TEMPllint1 = 0;
    }
    else if(TEMPllint1 <= 2*dwa_32)
    {
        TEMPllint1 -= dwa_32;
        liczba_.push_back(dwa_32);
    }
    else
    {
        TEMPllint1 -= 2 * dwa_32;
        liczba_.push_back(dwa_32);
        liczba_.push_back(dwa_32);
    }

    ileDOkonca -=10;
    liczbaJakoNapis.resize(liczbaJakoNapis.size()-10);

    }
}

int BigInt::size() const
{
    return liczba_.size();
}

unsigned int BigInt::operator[](int WE) const
{
    return liczba_[WE];
}


unsigned int& BigInt::operator[](int WE)
{
    return liczba_[WE];
}

bool BigInt::czyDodatnia() const
{
    return dodatnia;
}

void BigInt::zmienZnak()
{
    dodatnia = !dodatnia;
}

bool BigInt::operator<(const BigInt& A) const
{
    bool WY = true;
    if(A.czyDodatnia() != czyDodatnia())
    {
        WY = czyDodatnia();
    }
    else if(A.size() > liczba_.size())
    {
        WY = false;
    }
    else if(A.size() == liczba_.size())
    {
        if(!A.czyDodatnia())
        {
            WY = (liczba_[size()-1] < A[A.size()-1]);
        }
        else
        {
            WY = (liczba_[size()-1] < A[A.size()-1]);
        }
    }
    return WY;
}

bool BigInt::operator>(const BigInt& A) const
{
    return (*this < A);
}

bool BigInt::operator>=(const BigInt& A) const
{
    return !(A < *this);
}

bool BigInt::operator<=(const BigInt& A) const
{
    return !(A > *this);
}

bool BigInt::operator==(const BigInt& A) const
{
    return (A <= *this) && (A >= *this);
}

bool BigInt::operator!=(const BigInt& A) const
{
    return !(A == *this);
}

BigInt BigInt::operator+=(const BigInt& B)
{
    long long int TEMPllint1 = 0;
    bool czyKoniec = false;
    int i = 0;

    while(czyKoniec)
    {
        TEMPllint1 += liczba_[i]+B[i];
        if(TEMPllint1 <= dwa_32)
        {
            liczba_.push_back(TEMPllint1);
            TEMPllint1 = 0;
        }
        else if(TEMPllint1 < 2 * dwa_32)
        {
            TEMPllint1 -= dwa_32;
            liczba_.push_back(dwa_32);
        }
        else
        {
            TEMPllint1 -= 2 * dwa_32;
            liczba_.push_back(dwa_32);
            liczba_.push_back(dwa_32);
        }

        if(i == std::min(size(), B.size()) - 1)
        {
            int koniec = (std::max(size(), B.size()) - std::min(size(), B.size()));
            for(int j = 1; j < koniec; )

        }

    }
}


int main()
{
    return 0;
}
