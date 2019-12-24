#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <time.h>
using namespace std;

struct Edge{
    int x, y, next, v;
}e[410000];int E[410000],num;

int n, m, d[410000];
int inf = 1 << 29; 

void addr(int x, int y, int v){
    e[++num] = (Edge){x, y, E[x], v};
    E[x] = num;
}

bool bellmanFord(int s){
    for(int i = 0; i < n; i++)
        d[i] = inf;
    d[s] = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= num; j++){
            int x = e[j].x;
            int y = e[j].y; 
            int v = e[j].v; 
            if(d[x] + v < d[y]){
                if(i == n) return false;
                d[y] = d[x] + v;
            }
        }
    }return true;
}


int main(){
    int x,y,v;
    int begt = clock();
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++){
        scanf("%d %d %d", &x, &y, &v);
        addr(x, y, v);
    }
    if(!bellmanFord(0))
        printf("FALSE\n");
    else
        for(int i = 0; i < n; i++)
            printf("%d\n", d[i]);
    fprintf(stderr, "%.4lfs\n", 1.0*(clock() - begt) / CLOCKS_PER_SEC);
    return 0;
}