#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <time.h>
using namespace std;

int inf = 1 << 29;
int n,m;
int d[7100][7100];

int main(){
    int x,y,v;
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(i == j) d[i][j] = 0;
            else d[i][j] = inf;
    for(int i = 0; i < m; i++){
        scanf("%d %d %d",&x, &y, &v);
        d[x][y] = v;
    }
    int begt = clock();
    for(int k = 0; k < n; k++){
        if(k % 1000 == 999)
            fprintf(stderr, "%d loops\n", k + 1);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    }
    for(int i = 0; i < n; i++)
        if(d[i][i] < 0){
            fprintf(stderr, "FALSE\n");
            return 0;
        }
    for(int i = 0; i < n; i++)
        printf("%d\n",d[0][i]);
    fprintf(stderr, "%.2lfs\n", (clock() - begt) * 1.0 / CLOCKS_PER_SEC);
    return 0;
}