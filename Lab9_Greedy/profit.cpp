#include<iostream>
#include<string.h>
#include<algorithm>
#include<stdlib.h>
#include<string.h>
using namespace std;

int n,a[110000];

int main(){
    freopen("profit.in","r",stdin);
    freopen("profit.out","w",stdout);
    scanf("%d",&n);
    while(n!=0){
        int ans=-1,minn = 1e9;
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++){
            if(a[i] < minn) minn = a[i];
            ans = max(ans, a[i] - minn);
        }printf("%d\n", ans);
        scanf("%d",&n);
    }return 0;
}