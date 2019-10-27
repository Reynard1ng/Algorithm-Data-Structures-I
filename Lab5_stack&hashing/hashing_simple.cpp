#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
using namespace std;

#define M 9999983
#define SUCCESS 1
#define ERROR 0
#define EMPTY 0
#define REMOVED -1

double alpha,alpha_top,alpha_bottom;

class LinearProbing{
    private:
        int hashtable[M];
        int h_(int k){
            return k % M;
        }
        int h(int k,int i){
            return (h_(k) + i) % M;
        }
    public:
        LinearProbing(){
            memset(hashtable,0,sizeof(hashtable));
        }
        int insert(int val){
            for(int i = 0; i < M; i++){
                int j = h(val, i);
                if(hashtable[j] == EMPTY || hashtable[j] == REMOVED){
                    hashtable[j] = val;
                    return SUCCESS;
                }
            }return ERROR;
        }
        int search(int val){
            for(int i = 0; i < M; i++){
                int j = h(val, i);
                if(hashtable[j] == val)
                    return val; // this place should be the data whose key value is "val", return val instead.
                if(hashtable[j] == EMPTY)
                    return ERROR;
            }return ERROR;
        }
        int remove(int val){
            for(int i = 0; i < M; i++){
                int j = h(val, i);
                if(hashtable[j] == val){
                    hashtable[j] = REMOVED;
                    return SUCCESS;
                }
                if(hashtable[j] == EMPTY){
                    return ERROR;
                }
            }return ERROR;
        }
}box1;

class QuadraticProbing{
    private:
        int size;
        int hashtable[M];
        int c1;
        int c2;
        int h_(int k){
            return k % M;
        }
        int h(int k,int i){
            return (h_(k) + 1ll * c1 * i + 1ll * c2 * i * i) % M;
        }
    public:
        QuadraticProbing(){
            memset(hashtable,0,sizeof(hashtable));
            size = 0;
            c1 = 45337;
            c2 = 23333;//two primes choosed by hand randomly
        }
        int insert(int val){
            for(int i = 0; i < M; i++){
                int j = h(val, i);
                if(hashtable[j] == EMPTY || hashtable[j] == REMOVED){
                    hashtable[j] = val;
                    return SUCCESS;
                }
            }return ERROR;
        }
        int search(int val){
            for(int i = 0; i < M; i++){
                int j = h(val, i);
                if(hashtable[j] == val)
                    return val; // this place should be the data whose key value is "val", return val instead.
                if(hashtable[j] == EMPTY)
                    return ERROR;
            }return ERROR;
        }
        int remove(int val){
            for(int i = 0; i < M; i++){
                int j = h(val, i);
                if(hashtable[j] == val){
                    hashtable[j] = REMOVED;
                    return SUCCESS;
                }
                if(hashtable[j] == EMPTY){
                    return ERROR;
                }
            }return ERROR;
        }
}box2;

class DoubleHashing{
    private:
        int size;
        int hashtable[M];
        double A ;
        int h1(int k){
            return k % M;
        }
        int h2(int k){
            return M * (k * A - (int)(k * A));
        }
        int h(int k,int i){
            return (h1(k) + 1ll * i * h2(k)) % M;
        }
    public:
        DoubleHashing(){
            memset(hashtable,0,sizeof(hashtable));
            size = 0;
            A = (sqrt(5) - 1) / 2;
        }
        int insert(int val){
            for(int i = 0; i < M; i++){
                int j = h(val, i);
                if(hashtable[j] == EMPTY || hashtable[j] == REMOVED){
                    hashtable[j] = val;
                    return SUCCESS;
                }
            }return ERROR;
        }
        int search(int val){
            for(int i = 0; i < M; i++){
                int j = h(val, i);
                if(hashtable[j] == val)
                    return val; // this place should be the data whose key value is "val", return val instead.
                if(hashtable[j] == EMPTY)
                    return ERROR;
            }return ERROR;
        }
        int remove(int val){
            for(int i = 0; i < M; i++){
                int j = h(val, i);
                if(hashtable[j] == val){
                    hashtable[j] = REMOVED;
                    return SUCCESS;
                }
                if(hashtable[j] == EMPTY){
                    return ERROR;
                }
            }return ERROR;
        }
}box3;

void testLinearProbing(){
    vector<int>exi;
    for(int i = 1, e_ = alpha * M; i <= e_; i++){
        int x = rand();
        exi.push_back(x);
        box1.insert(x);
    }
    int cnt = alpha * M;
    for(int i = 1, e_ = M * 2; i <= e_; ){
        int ope = rand() % 3;
        if(ope == 1){
            if(cnt > alpha_top * M)continue;
            int x = rand();
            exi.push_back(x);
            box1.insert(x);
            cnt++;
        }
        if(ope == 2){
            if(cnt < alpha_bottom * M) continue;
            int x = rand() % exi.size();
            box1.remove(exi[x]);
            cnt --;
        }
        if(ope == 3){
            int x = rand() % 10;
            if(x <= 1) box1.search(rand());
            else box1.search(exi[rand()%exi.size()]);
        }
        i++;
    }
}

void testQuadraticProbing(){
    vector<int>exi;
    for(int i = 1, e_ = alpha * M; i <= e_; i++){
        int x = rand();
        exi.push_back(x);
        box2.insert(x);
    }
    int cnt = alpha * M;
    for(int i = 1, e_ = M * 2; i <= e_; ){
        int ope = rand() % 3;
        if(ope == 1){
            if(cnt > alpha_top * M)continue;
            int x = rand();
            exi.push_back(x);
            box2.insert(x);
            cnt++;
        }
        if(ope == 2){
            if(cnt < alpha_bottom * M) continue;
            int x = rand() % exi.size();
            box2.remove(exi[x]);
            cnt --;
        }
        if(ope == 3){
            int x = rand() % 10;
            if(x <= 1) box2.search(rand());
            else box2.search(exi[rand()%exi.size()]);
        }
        i++;
    }
}

void testDoubleHashing(){
    vector<int>exi;
    for(int i = 1, e_ = alpha * M; i <= e_; i++){
        int x = rand();
        exi.push_back(x);
        box3.insert(x);
    }
    int cnt = alpha * M;
    for(int i = 1, e_ = M * 2; i <= e_; ){
        int ope = rand() % 3;
        if(ope == 1){
            if(cnt > alpha_top * M)continue;
            int x = rand();
            exi.push_back(x);
            box3.insert(x);
            cnt++;
        }
        if(ope == 2){
            if(cnt < alpha_bottom * M) continue;
            int x = rand() % exi.size();
            box3.remove(exi[x]);
            cnt --;
        }
        if(ope == 3){
            int x = rand() % 10;
            if(x <= 1) box3.search(rand());
            else box3.search(exi[rand()%exi.size()]);
        }
        i++;
    }
}

void testCommonTime(){
    vector<int>exi;
    for(int i = 1, e_ = alpha * M; i <= e_; i++){
        int x = rand();
        exi.push_back(x);
//        box.insert(x);
    }
    int cnt = alpha * M;
    for(int i = 1, e_ = M * 2; i <= e_; ){
        int ope = rand() % 3;
        if(ope == 1){
            if(cnt > alpha_top * M)continue;
            int x = rand();
            exi.push_back(x);
//            box.insert(x);
            cnt++;
        }
        if(ope == 2){
            if(cnt < alpha_bottom * M) continue;
            int x = rand() % exi.size();
 //           box.remove(exi[x]);
            cnt --;
        }
        if(ope == 3){
            int x = rand() % 10;
//            if(x <= 1) box3.search(rand());
 //           else box3.search(exi[rand()%exi.size()]);
        }
        i++;
    }
}

int main(){
    srand(time(NULL));
    cout << "Please input the \"load factor\" (less than 0.9) ."<< endl;
    cin >> alpha;
    alpha_top = 1.1 * alpha;
    alpha_bottom = 0.9 * alpha;
    testCommonTime();
    double t = clock();
    testLinearProbing();
    double t1 = clock();
    cerr << 1.0 * (t1 - t - t)/CLOCKS_PER_SEC << endl;
    testQuadraticProbing();
    double t2 = clock();
    cerr << 1.0 * (t2 - t1 - t)/CLOCKS_PER_SEC << endl;
    testDoubleHashing();
    double t3 = clock();
    cerr << 1.0 * (t3 - t2 - t)/CLOCKS_PER_SEC << endl;
    return 0;
}