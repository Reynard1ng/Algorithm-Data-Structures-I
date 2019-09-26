#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

#define N 2333333
#define LOW_R 10000
#define HIG_R 200000
#define STEP_R 10000

int RiP[N];
pair <int,long long> PbS[N];
vector <pair<int,long long> > PbStmp[N]; 


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

void randomizeInPlace(int n){
    for(int i = 1; i <= n; i++){
        swap(RiP[i], RiP[rand(i,n)]);
//        printf("%d ", RiP[i]);
    }
}

inline int Q0(long long x, int n){return x % n;}
inline int Q1(long long x, int n){return x / n % n;}
inline int Q2(long long x, int n){return x / n / n;}

void permuteBySorting(int n){
    int n3 = n * n * n;
    for(int i = 1; i <= n; i++) {PbS[i].second = lRand() % n3;}
    for(int i = 1; i <= n; i++) 
        PbStmp[Q0(PbS[i].second, n)].push_back(PbS[i]);
    for(int i = 0, cnt = 0; i < n; i++){
        if(!PbStmp[i].empty())
            for(auto j = PbStmp[i].begin(); j != PbStmp[i].end(); j++)
                PbS[++cnt] = *j;
        PbStmp[i].clear();
    }

    for(int i = 1; i <= n; i++) 
        PbStmp[Q1(PbS[i].second, n)].push_back(PbS[i]);
    for(int i = 0, cnt = 0; i < n; i++){
        if(!PbStmp[i].empty())
            for(auto j = PbStmp[i].begin(); j != PbStmp[i].end(); j++)
                PbS[++cnt] = *j;
        PbStmp[i].clear();
    }

    for(int i = 1; i <= n; i++) 
        PbStmp[Q2(PbS[i].second, n)].push_back(PbS[i]);
    for(int i = 0, cnt = 0; i < n; i++){
        if(!PbStmp[i].empty())
            for(auto j = PbStmp[i].begin(); j != PbStmp[i].end(); j++)
                PbS[++cnt] = *j;
        PbStmp[i].clear();
    }
    
}

void monteCarlo

int main(){
    srand(time(NULL));
    for(int i = LOW_R; i <= HIG_R; i+= STEP_R){
        for(int j = 1; j <= i; j++) 
            RiP[j] = PbS[j].first = j;
        int t1 = clock();
        randomizeInPlace(i);
        int t2 = clock();
        permuteBySorting(i);
        int t3 = clock();
        cerr << t2 - t1 << ' ' << t3 - t2 << endl;
/*        for(int j = 1; j <= i; j++)
            printf("%d ",RiP[j]);
        printf("\n");
        for(int j = 1; j <= i; j++)
            printf("%d ",PbS[j].first);
        printf("\n");
*/    }
    for(int i = LOW_M; i <= HIG_M; i+=STEP_M){
        
    }
}