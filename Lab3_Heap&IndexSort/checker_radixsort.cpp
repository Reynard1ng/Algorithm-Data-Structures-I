#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <time.h>
#include <fstream>
#include <string>
using namespace std;

int main(){
    ifstream x("output.txt");
    ifstream y("output1.txt");
    string ansx, ansy;
    for(int i = 1; i <= 1000000; i++){
        x >> ansx;
        y >> ansy;
        if(ansx != ansy) cerr << "Error in line " << i << "\n" << "> " << ansx << "\n> " << ansy << endl;
    }
}