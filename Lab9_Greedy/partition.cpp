#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<stdlib.h>
#include<string.h>
#include<math.h>

using namespace std;

struct Node{
    double x,y;
    double ang;
}a[51000];

double eps = 1e-10;
double pi = acos(-1.0);

int n;
double x,y;

int cmp(Node x, Node y){
    return x.ang < y.ang;
}

double clockwise(double x, double y){
    return y - x > -eps ? y - x : y - x + pi * 2;
}

int main(){
    freopen("partition.in","r",stdin);
    freopen("partition.out","w",stdout);
    scanf("%d %lf %lf",&n,&x,&y);
    while(n!=0 && x!=0 && y!=0){
        x/=2;y/=2;
        for(int i=1;i<=n;i++){
            scanf("%lf %lf",&a[i].x,&a[i].y);
            a[i].x -= x;
            a[i].y -= y;
            a[i].ang = atan2(a[i].y,a[i].x);
            if(a[i].ang < 0) a[i].ang += 2 * pi;
        }sort(a+1,a+n+1,cmp);
        if(n==2){
            printf("%d %d\n",(int)(a[1].x + x + 0.5), (int)(a[1].y + y + 0.5));
        }else{
            int flag = 0;
            for(int i=1;i<=n/2;i++){
                int begx = i;
                int endx = i + n/2 - 1;
                int begy = (i==1)?n:(i-1);
                int endy = endx + 1;
                double innerang = clockwise(a[begx].ang, a[endx].ang);
                double outerang = clockwise(a[begy].ang, a[endy].ang);
                if(outerang < eps) outerang += pi * 2;
                if(innerang - pi <= eps &&  outerang - pi >= -eps){
                    for(int j = begx; j <= endx; j++)
                        printf("%d %d\n",(int)(a[j].x + x + 0.5), (int)(a[j].y + y + 0.5));
                    break;
                }
            }
        }scanf("%d %lf %lf",&n ,&x, &y);
    }return 0;
}