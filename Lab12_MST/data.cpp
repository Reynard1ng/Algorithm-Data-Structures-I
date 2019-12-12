#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <time.h>
#include <map>
using namespace std;

int N, M;

map <int,int> exi[1100000];

int main(){
    freopen("graph.txt","w",stdout);
    int cnt = 0;
    scanf("%d %d", &N, &M);
    printf("%d %d\n", N, M);
    while(cnt < N - 1){
        int x;
        cnt++;
        printf("%d %d %d\n", cnt, x = (rand()%cnt), rand());
        exi[cnt][x] = exi[x][cnt] = 1;
    }while(cnt < M){
        cnt++;
        while(1){
            int x = rand()%N;
            int y = rand()%N;
            if(x == y) continue;
            if(exi[x][y]) continue;
            printf("%d %d %d\n", x, y, rand());
            exi[x][y] = exi[y][x] = 1;
            break;
        }
    }return 0;
}