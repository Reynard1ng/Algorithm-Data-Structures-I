#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include "Fibonacci_Heap.h"
using namespace std;

struct Node{
    int x,y,v;
    bool operator < (Node t){   return v < t.v;}
    bool operator > (Node t){   return v > t.v;}
    bool operator <= (Node t){  return v <= t.v;    }
    bool operator >= (Node t){  return v >= t.v;    }
};

Fibonacci_Heap < Node > near;

int n,m;
bool vis[2100000];
struct Road{
    int e,next,v;
}r[21000000];int num,R[2100000];

void addr(int x,int y,int v){
    r[++num] = (Road){y,R[x],v};
    R[x] = num;
}

int main(){
    int x,y,v;
    scanf("%d %d",&n,&m);
    for(int i = 1; i <= m; i++){
        scanf("%d %d %d", &x, &y, &v);
        addr(x,y,v); addr(y,x,v);
    }
    int tb = clock();
    for(int i = 1; i < n; i++)
        near.Push(i, (Node){i, i, (int)1e9});
    near.Push(0, (Node){0, 0, 0});
    int ncnt = 0;
    long long ans = 0;;
    do{
        Node tmp = near.Top();
        near.Pop();
        ncnt++;
//        if(tmp.v != 0)printf("%d %d\n", tmp.x, tmp.y);
        ans += tmp.v;
        vis[tmp.y] = 1;
        for(int i = R[tmp.y]; i; i = r[i].next){
            int e = r[i].e;
            if(!vis[e]) near.Decrease_Key(e,(Node){tmp.y,e,r[i].v});
        }
    }while(ncnt < n);
    int te = clock();
//    printf("%lld\n",ans);
    printf("%.4lf\n",(te-tb)*1.0/CLOCKS_PER_SEC*1000);
    return 0;
}