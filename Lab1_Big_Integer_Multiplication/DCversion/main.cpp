#include "biginteger.h"
#include <stdio.h>
#include <iostream>
#include <fstream>

int main(){
    std::ifstream fin("input.txt");
    std::ofstream fout("output_.txt");
    std::string x,y;
    fin >> x;
    fin >> y;
    BigInteger numberx(x),numbery(y),ans;
    dividedMultiplication(numberx,numbery,ans);
    fout << ans << std::endl;
}