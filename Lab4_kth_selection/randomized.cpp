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

void swap(Node &x, Node &y){
    Node z = x;
    x = y;
    y = z;
}

int randomizedFindkth(int l, int r, int x){
    if(r - l <= 5){
        sort(a + l, a + r + 1);
        return a[l + x - 1].x;
    }
    int mid = rand()%(r - l + 1) + l;
    swap(a[mid], a[r]);
    int newl = l, newr = r - 1;
    while(1){
        while(newl <= newr && a[newl] < a[r]) newl++;
        while(newr >= newl && a[newr] > a[r]) newr--;
        if(newl < newr) swap(a[newl], a[newr]);
        else break;
    }newl--; newr++;
    swap(a[newr], a[r]);
    mid = newr;
    if(mid-l+1 == x) return a[mid].x;
    if(mid-l >= x) return randomizedFindkth(l, mid-1, x);
    else return randomizedFindkth(mid+1, r, x-(mid-l+1));
}

int main(){
    ifstream fin("input.txt");
    for(int i = 1; i <= 20000000; i++){
        fin >> a[i].x;
        a[i].id = i;
    }
    int t = clock();
    cin >> kth;
    cout << randomizedFindkth(1, 20000000, kth) << endl;;
    cout << 1.0 * (clock()-t) / CLOCKS_PER_SEC <<endl;
    return 0;
}