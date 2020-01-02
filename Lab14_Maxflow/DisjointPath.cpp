#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <queue>
using namespace std;

int n, m;
struct Edge{
    int e,next,v;
}e[410000];int E[110000],cnt = 1;

int prevI[110000];
int prevE[110000];

void adde(int x, int y, int v){
    e[++cnt] = (Edge){y, E[x], 1};
    E[x] = cnt;
    e[++cnt] = (Edge){x, E[y], 0};
    E[y] = cnt;
}

int SearchPath(int s, int t){
    queue<int>Q;
    for(int i = 1; i <= n; i++)
        prevI[i] = prevE[i] = 0;
    Q.push(s);
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        for(int i = E[u]; i; i = e[i].next){
            int v = e[i].e;
            if(prevI[v] != 0) continue;
            if(e[i].v == 0) continue;
            prevI[v] = u;
            prevE[v] = i;
            Q.push(v);
        }
    }if(prevI[t] == 0) return 0;
    return 1;
}

int MaxFlow(int s, int t){
    int ans = 0;
    while(SearchPath(s, t)){
        int minn = 1<<30, tmpu;
        
        tmpu = t;
        while(tmpu != s){
            minn = min(minn, e[prevE[tmpu]].v);
            tmpu = prevI[tmpu];
        }
        
        tmpu = t;
        while(tmpu != s){
            e[prevE[tmpu]].v -= minn;
            e[prevE[tmpu]^1].v += minn;
            tmpu = prevI[tmpu];
        }

        ans += minn;
    }return ans;
}

int main(){
    int x, y, v;
    scanf("%d %d",&n,&m);
    for(int i = 0; i < m; i++){
        scanf("%d %d %d", &x, &y, &v);
        adde(x,y,v);
    }
    printf("%d\n", MaxFlow(1, n));
    return 0;
}