#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <vector>
#include <map>
using namespace std;

#define M 999983
#define SUCCESS 1
#define ERROR 0
#define EMPTY 0
#define REMOVED -1

double alpha,alpha_top,alpha_bottom;

int isp[20000010],pri[20000010],cntp;

class PerfectHashing{
    private:
        long long size2sum;
        int Modlay1;
        int Modlay2[M];
        vector<int>storelay1;
        vector<int>storelay2[M];
        vector<int>htlay2[M];
        int h(int k, int Mod, int Modtot){
            return k % Mod % Modtot;
        }
    public:
        PerfectHashing(){
            size2sum = 0;
        }
        void insert(int x){
            storelay1.push_back(x);
        }
        void construct(){
            while(1){
                for(int i = 0; i < M; i++)
                    storelay2[i].clear();
                Modlay1 = pri[rand() % cntp];    
                for(int i = 0; i < M; i++)
                    storelay2[h(storelay1[i], Modlay1, M)].push_back(storelay1[i]);
                size2sum = 0;
                for(int i = 0; i < M; i++)
                    size2sum += 1ll * storelay2[i].size() * storelay2[i].size();
                if(size2sum <= 4 * M) break;
            }
            for(int i = 0; i < M; i++){
                while(1){
                    htlay2[i].clear();
                    for(int j = 0, e_ = storelay2[i].size() * storelay2[i].size(); j < e_; j++)
                        htlay2[i].push_back(0);
                    Modlay2[i] = pri[rand() % cntp];
                    int flag = 1;
                    for(int j = 0, e_ = storelay2[i].size(); j < e_; j++){
                        int pos = h(storelay2[i][j], Modlay2[i], e_ * e_);
                        if(htlay2[i][pos] == 0) htlay2[i][pos] = storelay2[i][j];
                        else {flag = 0; break;}
                    }if(flag) break;
                }
            }
        }
        int find(int x){
            int pos1 = h(x, Modlay1, M);
            if(htlay2[pos1].empty()) return 0;
            int pos2 = h(x, Modlay2[pos1], storelay2[pos1].size() * storelay2[pos1].size());
            if(htlay2[pos1][pos2] == x) return x;
            else return 0;
        }
}PH;

class CuckooHashing{
    private:
        int limit, cft;
        int mod[2], plus[2], mult[2];
        int hashtable[2][M];
        int h(int x, int at){
            return (1ll * mult[at] * x + plus[at]) % mod[at] % M;
        }
        void reconstruct(){
            vector<int>store;
            for(int i = 0; i < M; i++){
                if(hashtable[0][i] != 0) store.push_back(hashtable[0][i]);
                if(hashtable[1][i] != 0) store.push_back(hashtable[1][i]);
                hashtable[0][i] = hashtable[1][i] = 0;
            }
            mod[0] = pri[rand() % cntp];
            plus[0] = pri[rand() % cntp];
            mult[0] = pri[rand() % cntp];
            mod[1] = pri[rand() % cntp];
            plus[1] = pri[rand() % cntp];
            mult[1] = pri[rand() % cntp];
            for(int i = 0, e_ = store.size(); i < e_; i++){
                insert(store[i], 0, 0);
            }
        }
    public:
        CuckooHashing(){
            memset(hashtable, 0, sizeof(hashtable));
            limit = 2 * log(1.0 * M) / log(2.0);
            cft = 0;
        }
        void clear(){
            memset(hashtable, 0, sizeof(hashtable));
            limit = 2 * log(1.0 * M) / log(2.0);
            cft = 0;
            mod[0] = pri[rand() % cntp];
            plus[0] = pri[rand() % cntp];
            mult[0] = pri[rand() % cntp];
            mod[1] = pri[rand() % cntp];
            plus[1] = pri[rand() % cntp];
            mult[1] = pri[rand() % cntp];
        }
        void insert(int x, int at, int times){
            if(times > limit){
                cft ++;
                reconstruct();
                times = 0;
            }int pos = h(x, at);
            if(hashtable[at][pos] == 0) 
                hashtable[at][pos] = x;
            else{
                int tmp = hashtable[at][pos];
                hashtable[at][pos] = x;
                insert(tmp, 1 - at, times + 1);
            }
        }
        int find(int x){
            int pos0 = h(x, 0); if(hashtable[0][pos0] == x)return x;
            int pos1 = h(x, 1); if(hashtable[1][pos1] == x)return x;
            return 0;
        }
        void remove(int x){
            int pos0 = h(x, 0);
            if(hashtable[0][pos0] == x) hashtable[0][pos0] = 0;
            int pos1 = h(x, 1);
            if(hashtable[1][pos1] == x) hashtable[1][pos1] = 0;
        }
        int conflict(){
            return cft;
        }
}CH;

void primeSieve(){
    for(int i = 2; i <= 20000000; i++){
        if(!isp[i]){
            if(-2333 <= i % M - M || i % M <= 2333) 
                pri[cntp++] = i;
            for(long long j = 1ll * i * i; j <= 20000000; j += i)
                isp[j] = 1;
        }
    }
}

void testPerfectHashing(){
    map<int,int>exist;
    vector <int>exilist;
    for(int i = 0; i < M; i++){
        while(1){
            int x = rand();
            if(exist.find(x) == exist.end()){
                exist[x] = 1;
                exilist.push_back(x);
                break;
            }
        }
    }
    for(int i = 0; i < M; i++)
        PH.insert(exilist[i]);
    PH.construct();
    int res = 0;
    for(int i = 0; i < M; i++){
        int opt = rand() % 10;
        if(opt <= 1) res += PH.find(rand());
        else res += PH.find(exilist[rand() % M]) != 0;
    }cerr << "founded elements: " << res << endl;
}

void testCuckooHashing(double loadfactor){
    map<int,int>exist;
    vector <int>exilist;
    for(int i = 0, e_ = loadfactor * M; i < e_; i++){
        while(1){
            int x = rand();
            if(exist.find(x) == exist.end()){
                exist[x] = 1;
                exilist.push_back(x);
                break;
            }
        }
    }
    CH.clear();
    for(int i = 0, e_ = loadfactor * M; i < e_; i++)
        CH.insert(exilist[i], 0, 0);
    int res = 0;
    for(int i = 0; i < M; i++){
        int opt = rand() % 10;
        if(opt <= 1) res += CH.find(rand());
        else res += CH.find(exilist[rand() % (int)(M * loadfactor)]) != 0;
    }cerr << loadfactor << " finished" << endl;
}

int main(){
    srand(time(NULL));
    primeSieve();
//    int t1 = clock();
    cerr << "Prework finished" << endl;
//    testPerfectHashing();
//    int t2 = clock();
//    cerr << "time consumption: " << 1.0*(t2-t1)/CLOCKS_PER_SEC << endl; 
//    cerr << "Perfect Hashing tested." << endl;
    ofstream fout("CuckooHashing.csv");
    for(double i = 0.01; i <= 0.99; i += 0.01){
        int t1 = 0, t2 = 0, con = 0;;
        for(int j = 1; j <= 20; j++){
            t1 += clock();
            testCuckooHashing(i);
            t2 += clock();
            con += CH.conflict();
        }fout << i << "," << 1.0 * (t2-t1) / CLOCKS_PER_SEC / 20 << "," << 1.0 * con / 20 << endl;
    }
    
    cerr << "Cuckoo Hashing tested." << endl;
    return 0;
}
