#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "Fibonacci_Heap.h"
using namespace std;

struct State{
	int d, x;
	State(int d = 0, int x = 0) : d(d), x(x) {}
	const bool operator < (const State& A) const {
		if(d != A.d)return d < A.d;
        else return x < A.x;
	}
    const bool operator <= (const State& A) const {
        if(d != A.d)return d <= A.d;
        else return x < A.x;
    }
	const bool operator > (const State& A) const {
		if(d != A.d)return d > A.d;
        else return x > A.x;
	}
    const bool operator >= (const State& A) const {
        if(d != A.d)return d >= A.d;
        else return x > A.x;
    }
};

struct Edge{
    int x, y, next, v;
}e[410000];int E[410000],num;

int n, m, dpre[410000];
int d[7100][7100];
int inf = 1 << 29; 

void addr(int x, int y, int v){
    e[++num] = (Edge){x, y, E[x], v};
    E[x] = num;
}

bool bellmanFord(int s, int *d){
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

void dijkstra(int s, int *d) {
	int sizess = 1000;
	Fibonacci_Heap<State> Q;
	memset(d, 63, sizeof(d[0]) * (n+20));
	d[s] = 0;
    for(int i = 0; i < n; ++i) {
        Q.Push(i, State(d[i], i));
    }
	while(!Q.Empty()) {
		State tmp = Q.Top();
		Q.Pop();
		int x = tmp.x;
        for(int i = E[x]; i; i = e[i].next){
			if (d[e[i].y] > d[x] + e[i].v) {
				Q.Decrease_Key(e[i].y, State(d[x] + e[i].v, e[i].y));
				d[e[i].y] = d[x] + e[i].v;
			}
        }
	}
}

int main(){
    int x,y,v;
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++){
        scanf("%d %d %d", &x, &y, &v);
        addr(x, y, v);
    }
    for(int i = 0; i < n; i++)
        addr(n, i, 0);
    int begt = clock();
    if(!bellmanFord(0, dpre))
        printf("FALSE\n");
    for(int i = 1; i <= m; i++)
        e[i].v += dpre[e[i].x] - dpre[e[i].y];
    for(int i = 0; i < n; i++){
        dijkstra(i, d[i]);
        if(i % 1000 == 999) fprintf(stderr, "%d finished\n", i+1);
    }
    for(int i = 0; i < n; i++)
        printf("%d\n", d[0][i] + dpre[i] - dpre[0]);
    fprintf(stderr, "%.2lfs\n",1.0 * (clock() - begt) / CLOCKS_PER_SEC);
    return 0;
}
