#include<stdio.h>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<string.h>
#include<stdlib.h>
#include<time.h>

using namespace std;

struct Node{
    int x,id;
}a[23333333];
int kth;

bool operator < (Node x, Node y){
    if(x.x != y.x)return x.x < y.x;
    return x.id < y.id;
}

bool operator > (Node x, Node y){
    if(x.x != y.x)return x.x > y.x;
    return x.id > y.id;
}

bool operator == (Node x, Node y){
    return x.x==y.x && x.id==y.id;
}

void swap(Node &x, Node &y){
    Node z = x;
    x = y;
    y = z;
}

Node worstFindkth(int l, int r, int x){
    if(r - l <= 140){
        sort(a + l, a + r + 1);
        return a[l + x - 1];
    }
    int size = r - l + 1;
    int group = (r - l) / 5 + 1;
    for(int i = l; i <= r; i += 5){
        sort(a + i, a + min(i + 5, r + 1));
    }
    int cnt = l;
    for(int i = l; i <= r; i += 5){
        int rtmp = min(i + 4, r);
        swap(a[cnt++], a[(i + rtmp) / 2]);
    }
    Node MID = worstFindkth(l, l + group - 1, (group - 1) / 2 + 1);
    for(int i = l; i <= l + group - 1; i++)
        if(a[i] == MID){
            swap(a[i], a[r]);
            break;
        }
    int newl = l, newr = r - 1;
    while(1){
        while(newl <= newr && a[newl] < a[r]) newl++;
        while(newr >= newl && a[newr] > a[r]) newr--;
        if(newl < newr) swap(a[newl], a[newr]);
        else break;
    }newl--; newr++;
    swap(a[newr], a[r]);
    int mid = newr;
    if(mid-l+1 == x) return a[mid];
    if(mid-l >= x) return worstFindkth(l, mid-1, x);
    else return worstFindkth(mid+1, r, x-(mid-l+1));
}

int main(){
    ifstream fin("input.txt");
    for(int i = 1; i <= 20000000; i++){
        fin >> a[i].x;
        a[i].id = i;
    }
    int t = clock();
    cin >> kth;
    cout << worstFindkth(1, 20000000, kth).x << endl;
    cout << 1.0 * (clock()-t) / CLOCKS_PER_SEC <<endl;
    return 0;
}