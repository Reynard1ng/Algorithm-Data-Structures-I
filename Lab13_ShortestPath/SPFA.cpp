#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <time.h>
using namespace std;

struct Edge{
    int x, y, next, v;
}e[410000];int E[410000],num;

int n, m, d[410000], inq[410000], inqt[410000];
queue<int>Q;
int inf = 1 << 29; 

void addr(int x, int y, int v){
    e[++num] = (Edge){x, y, E[x], v};
    E[x] = num;
}

int SPFA(int s){
    for(int i = 0; i < n; i++)  d[i] = inf, inq[i] = 0, inqt[i] = 0;
    Q.push(s);                  d[s] = 0,   inq[s] = 1, inqt[s] = 1;
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();inq[u] = 0;
        for(int i = E[u]; i; i=e[i].next){
            int v = e[i].y;
            if(d[v] > d[u] + e[i].v){
                d[v] = d[u] + e[i].v;
                if(!inq[v]){
                    Q.push(v);
                    inq[v] = 1;
                    inqt[v] ++;
                    if(inqt[v] > n) 
                        return 1;
                }
            }
        }
    }return 0;
}

int main(){
    int x, y, v;
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++){
        scanf("%d %d %d", &x, &y, &v);
        addr(x, y, v);
    }
    int begt = clock();
    if(SPFA(0))
        fprintf(stderr, "FALSE\n");
    else
        for(int i = 0; i < n; i++)
            printf("%d\n", d[i]);
    fprintf(stderr, "%.4lfs\n", 1.0*(clock() - begt) / CLOCKS_PER_SEC);
    return 0;
}