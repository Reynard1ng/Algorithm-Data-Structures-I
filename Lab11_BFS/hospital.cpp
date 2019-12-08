#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <queue>
using namespace std;
int dis[1005][1005];
int n,m,H;
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};
queue< pair<int,int> > Q;

void bfs(){
    while(!Q.empty()){
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();
        for(int i = 0; i <= 3; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx >= 0 && nx < n && ny >= 0 && ny < m && dis[nx][ny] > dis[x][y] + 1){
                dis[nx][ny] = dis[x][y] + 1;
                Q.push(make_pair(nx, ny));
            }
        }
    }
}

int main(){
    int x,y;
//    freopen("hospital.in","r",stdin);
//    freopen("hospital.out","w",stdout);
    scanf("%d %d %d",&n,&m,&H);
    memset(dis, 0x7f, sizeof(dis));
    for(int i=1;i<=H;i++){
        scanf("%d %d",&x,&y);
        if(dis[x][y] != 0){
            dis[x][y] = 0;
            Q.push(make_pair(x,y));
        }
    }bfs();
    int ans = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            ans = max(ans, dis[i][j]);
    printf("%d\n",ans);
    return 0;
}