#ifndef BIGINTEGER_H_INCLUDED
#define BIGINTEGER_H_INCLUDED

#include <string>
#include <iostream>
#include <vector>

class BigInteger{
    friend void copy(BigInteger &x, BigInteger &y, int l, int r);
    friend void dividedMultiplication(BigInteger &x,BigInteger &y,BigInteger &ans);
    friend BigInteger operator + (BigInteger x, BigInteger y);
    friend BigInteger operator - (BigInteger x, BigInteger y);
    friend BigInteger pow10Multiplication(BigInteger x, int y);
    private:
        std::vector<int>data;
    public:
        BigInteger(){}
        BigInteger(std::string x);
        ~BigInteger(){}
        std::string acquireData() const;
};

std::ostream & operator << (std::ostream &out, BigInteger x);
#endif