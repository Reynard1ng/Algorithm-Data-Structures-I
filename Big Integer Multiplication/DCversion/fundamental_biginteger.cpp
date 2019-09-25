#include <string>
#include "biginteger.h"

BigInteger::BigInteger(std::string x){
    for(int i = x.size() - 1; i >= 0; i--)
        data.push_back(x[i] - '0');
}

std::string BigInteger::acquireData() const {
    std::string res;
    for(int i = data.size() - 1; i >= 0; i--){
        res += data[i] + '0';
    }return res;
}

std::ostream & operator << (std::ostream &out, BigInteger x){
    out << x.acquireData();
    return out;
}

void copy(BigInteger &x, BigInteger &y, int l, int r){
    for(int i = l; i < r; i++){
        y.data.push_back(x.data[i]);
    }
}
