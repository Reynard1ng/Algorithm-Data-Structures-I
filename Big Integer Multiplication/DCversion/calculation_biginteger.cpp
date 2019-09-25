#include "biginteger.h"
//Divided Multiplication

BigInteger operator + (BigInteger x,BigInteger y){
    while(x.data.size() < y.data.size()) x.data.push_back(0);
    while(x.data.size() > y.data.size()) y.data.push_back(0);
    int length = x.data.size();
    for(int i = 0; i < length; i++)
        x.data[i] += y.data[i];
    for(int i = 0; i < length - 1; i++){
        x.data[i + 1] += x.data[i] / 10;
        x.data[i] %= 10;
    }
    if(x.data[length - 1] >= 10){
        x.data.push_back(0);
        x.data[length] += x.data[length - 1] / 10;
        x.data[length - 1] %= 10;
    }return x;
}

BigInteger operator - (BigInteger x,BigInteger y){
    int length = std::min(x.data.size(), y.data.size());
    for(int i = 0; i < length; i++)
        x.data[i] -= y.data[i];
    for(int i = 0; i < x.data.size() - 1; i++)
        if(x.data[i] < 0){
            x.data[i] += 10;
            x.data[i+1]--;
        }
    return x;
}

BigInteger pow10Multiplication (BigInteger x, int y){
    BigInteger ans;
    while(y--) ans.data.push_back(0);
    copy(x, ans, 0, x.data.size());
    return ans;
}

void dividedMultiplication(BigInteger &x,BigInteger &y,BigInteger &ans){
    while(x.data.size()<y.data.size()) x.data.push_back(0);
    while(y.data.size()<x.data.size()) y.data.push_back(0);
    ans.data.clear();
    if(x.data.size()==1){
        ans.data.push_back(x.data[0]*y.data[0]);
        if(ans.data[0] >= 10){
            ans.data.push_back(ans.data[0] / 10);
            ans.data[0] %= 10;
        }
    }
    else{
        int length = x.data.size();
        int lower = length / 2;
        int upper = length - lower;
        BigInteger A,B,C,D,AC,BD,AplusB,CplusD,combined;
        copy(x, B, 0, length / 2);
        copy(x, A, length/2, length);
        copy(y, D, 0, length / 2);
        copy(y, C, length/2, length);
        AplusB = A+B;
        CplusD = C+D;
        dividedMultiplication(A, C, AC);
        dividedMultiplication(B, D, BD);
        dividedMultiplication(AplusB, CplusD, combined);
        ans = pow10Multiplication(AC, lower << 1) + pow10Multiplication(combined - AC - BD, lower) + BD;
    }
    while(ans.data.size() > 1 && ans.data[ans.data.size() - 1] == 0)
        ans.data.pop_back();
}
