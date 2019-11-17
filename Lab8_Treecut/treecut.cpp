#include<stdio.h>
#include<iostream>
#include<string.h>
using namespace std;

const int inf = 1e9;
int n,root,f[100005];

struct Road{
    int e,next,v;
}r[233333];int R[100005],num;

void addr(int x,int y,int v){
    r[++num] = (Road){y,R[x],v};
    R[x] = num;
}

void dfs(int u,int fa){
    int isleaf = 1;
    for(int i = R[u]; i; i = r[i].next){
        int v = r[i].e;
        if(v == fa) continue;
        isleaf = 0;
    }
    if(isleaf) return;
    f[u] = 0;
    for(int i = R[u]; i; i = r[i].next){
        int v = r[i].e;
        if(v == fa) continue;
        dfs(v, u);
        f[u] += min(f[v], r[i].v);
    }
}

void clear(){
    num = 0;
    memset(R, 0, sizeof(int) * (n + 5));
}

int main(){
	freopen("data2.txt","r",stdin);
	freopen("test.txt","w",stdout);
	int x,y,v;
    while(1){
        scanf("%d %d",&n, &root);
        if(n==0 && root==0) break;
        for(int i = 1; i < n; i++){
            scanf("%d %d %d",&x,&y,&v);
            addr(x,y,v);addr(y,x,v);
        }
//        fprintf(stderr,"ojbk\n");
        for(int i = 1;i <= n; i++)
            f[i] = inf;
        if(n==1) f[root] = 0;
        else dfs(root,0);
        printf("%d\n",f[root]);
        clear();
    }return 0;
}
