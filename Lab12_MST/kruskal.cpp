#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>
using namespace std;

struct Road{
    int x,y,v;
}r[21000000];
int n,m;
int fa[2100000],de[2100000];

int cmp(Road x, Road y){
    return x.v < y.v;
}

int find(int x){
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int main(){
    int x,y,v;
    scanf("%d %d", &n, &m);
    for(int i=0;i<m;i++){
        scanf("%d %d %d", &x, &y, &v);
        r[i] = (Road){x, y, v};
    }
    int tb = clock();
    sort(r, r + m, cmp);
    for(int i = 0; i < n; i++){
        fa[i] = i;
        de[i] = 0;
    }long long ans = 0;
    for(int i = 0;i < m; i++){
        int x = r[i].x;
        int y = r[i].y;
        int fx = find(x);
        int fy = find(y);
        if(fx != fy){
//            printf("%d %d\n",x ,y);
            ans += r[i].v;
            if(de[fx] > de[fy])         fa[fy] = fx;
            else if(de[fx] < de[fy])    fa[fx] = fy;
            else                       {fa[fy] = fx; de[fx]++;}
        }
    }
    int te = clock();
//    printf("%lld\n",ans);
    printf("%.4lf\n",(te-tb)*1.0/CLOCKS_PER_SEC*1000);
    return 0;
}