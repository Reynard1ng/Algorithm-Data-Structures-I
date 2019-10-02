#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <unistd.h>

using namespace std;

#define N 23333333
#define LOW_R 1000000
#define HIG_R 10000000
#define STEP_R 1000000

int RiP[N];
std::pair <int,long long> PbS[N];
std::vector <std::pair<int,long long> > PbStmp[N]; 


//ATTENTION !
//Function "rand()" generates a 31-bits integer under the Linux and Mac OS
//So function "lRand()" aims at generating a 62-bits integer
long long lRand(){
    return ( 1ll * rand() << 31 ) | rand();
}

//Generate a number in range [l, r]

int rand(int l,int r){
    return l + rand() % (r - l + 1);
}

//swap two numbers

void swap(int &x,int &y){
    int v = x;
    x = y;
    y = v;
}

//As its name QwQ

void randomizeInPlace(int n){
    for(int i = 1; i <= n; i++){
        swap(RiP[i], RiP[rand(i,n)]);
//        printf("%d ", RiP[i]);
    }
}

inline int Q0(long long x, int n){return x % n;}
inline int Q1(long long x, int n){return x / n % n;}
inline int Q2(long long x, int n){return x / n / n;}

//Mainly contains the Radix sorting process
//Pbs means Permute by Sorting
//PbS.first: raw data
//PbS.second: new value for sorting

void permuteBySorting(int n){
    int n3 = n * n * n;
    for(int i = 1; i <= n; i++) {PbS[i].second = lRand() % n3;}
    for(int i = 1; i <= n; i++) 
        PbStmp[Q0(PbS[i].second, n)].push_back(PbS[i]);
    for(int i = 0, cnt = 0; i < n; i++){
        if(!PbStmp[i].empty())
            for(std::vector<std::pair<int, long long> >::iterator j = PbStmp[i].begin(); j != PbStmp[i].end(); j++)
                PbS[++cnt] = *j;
        PbStmp[i].clear();
    }

    for(int i = 1; i <= n; i++) 
        PbStmp[Q1(PbS[i].second, n)].push_back(PbS[i]);
    for(int i = 0, cnt = 0; i < n; i++){
        if(!PbStmp[i].empty())
            for(std::vector<std::pair<int, long long> >::iterator j = PbStmp[i].begin(); j != PbStmp[i].end(); j++)
                PbS[++cnt] = *j;
        PbStmp[i].clear();
    }

    for(int i = 1; i <= n; i++) 
        PbStmp[Q2(PbS[i].second, n)].push_back(PbS[i]);
    for(int i = 0, cnt = 0; i < n; i++){
        if(!PbStmp[i].empty())
            for(std::vector<std::pair<int, long long> >::iterator j = PbStmp[i].begin(); j != PbStmp[i].end(); j++)
                PbS[++cnt] = *j;
        PbStmp[i].clear();
    }
    
}

//ONLY in Linux or Mac OS

void monteCarlo(){
    freopen("monteCarlo3.txt", "w", stdout);
    long long total_count = 0;
    long long valid_count = 0;
    while(total_count < 10000000000ll){
//        double x = rand() / 2e9;
//        double y = rand() / 2e9;
        double x = ((1ll * rand() << 31) | rand()) / 2e9;
        double y = ((1ll * rand() << 31) | rand()) / 2e9;
        if(x > 2e9 || y > 2e9) continue;
        total_count++;
        if((x-1e9) * (x-1e9) + (y-1e9) * (y-1e9) <= 1e18)
            valid_count++;
        if(total_count % 50000000 == 0){
            printf("%lld %.10lf\n",total_count, 4.0 * valid_count / total_count);
            cerr << total_count << endl;
        }
    }
}

int main(int argc, char **argv){
    srand(time(NULL));
//    freopen("randomexample.out","w",stdout);
    for(int i = 30; i <= 30; i+= 30){
        for(int j = 1; j <= i; j++) 
            RiP[j] = PbS[j].first = j;
        int t1 = clock();
        cerr << "ok" << endl;
        randomizeInPlace(i);
        int t2 = clock();
        permuteBySorting(i);
        int t3 = clock();
        printf("%d,%d,%d\n",i,t2-t1,t3-t2);
        for(int j = 1; j <= i; j++)
            printf("%d ",RiP[j]);
        printf("\n");
        for(int j = 1; j <= i; j++)
            printf("%d ",PbS[j].first);
        printf("\n");
    }
    monteCarlo();
}

//Attention:
//Two lab are contained in one file
//If you wanna run this, please remember to deal with the conflict between two output stream in Line 117 and 96