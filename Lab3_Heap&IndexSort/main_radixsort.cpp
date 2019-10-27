#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <time.h>
using namespace std;

char ori[1100000][55];
int x[1100000][15];
int n, ind, maxend, maxrepo;
int ans[1100000];
vector<int> repo[1100000];

int pow10(int x){
    int res = 1;
    while(x--) res*=10;
    return res;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
    while(scanf("%s", ori[++n]) != EOF){
        reverse(ori[n], ori[n] + strlen(ori[n]));
        ans[n] = n;
//        printf("%s\n", ori[n]);
    }n--;

    int begintime = clock();

    ind = (int) ((log(1.0 * n) / log(1.0 * 10)) + 0.5);
    for(int i = 1; i <= n; i++){
        int end = strlen(ori[i]);
        maxend = max(end, maxend);
        for(int j = 0; j < end; j += ind){
            int tmp = 0, pow = 1;
            for(int cnt = 0; cnt < ind && j + cnt < end; cnt++, pow *= 10)
                tmp+=(ori[i][j+cnt] - '0') * pow;
            x[i][j/ind] = tmp;
        }
    }
    maxend = (maxend - 1) / ind;
    maxrepo = pow10(ind);
    for(int i = 0; i <= maxend; i++){
        for(int j = 1; j <= n; j++)
            repo[x[ans[j]][i]].push_back(ans[j]);
        int cnt = 0;
        for(int j = 0; j < maxrepo; j++){
            for(vector<int>::iterator it = repo[j].begin(); it != repo[j].end(); it++){
                ans[++cnt] = *it;
            }repo[j].clear();
        }
    }
    
    cerr << 1.0 * (clock() - begintime) / CLOCKS_PER_SEC << endl;

    std::string out = "%0?d";
    out[2] = ind + '0';

    for(int i = 1; i <= n; i++){
        int j = maxend;
        while(j >= 0 && x[ans[i]][j] == 0) j--;
        printf("%d",x[ans[i]][j]); j--;
        for(; j >= 0; j--)
            printf(out.c_str(), x[ans[i]][j]);
        printf("\n");
    }return 0;

}