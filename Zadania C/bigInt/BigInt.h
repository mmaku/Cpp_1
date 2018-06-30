#ifndef BIGINT_H
#define BIGINT_H
#include <vector>

const long long int dwa_32 = 4294967295;

class BigInt
{
    private:
        std::vector<unsigned int> liczba_;
        bool dodatnia = true;

    public:
        BigInt(int liczba);
        BigInt(std::string liczbaJakoNapis);

        int size() const;
        unsigned int operator[](int WE);
        bool znak();
        BigInt& operator+=(const BigInt& B);
        BigInt& operator+=(const BigInt& B);
        BigInt& operator-=(const BigInt& B);
};
#endif // BIGINT_H
