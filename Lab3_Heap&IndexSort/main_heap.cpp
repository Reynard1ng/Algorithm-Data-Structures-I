#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
using namespace std;

#define MAX_ELEMENTS 23333333
#define inf 2147483647

class priority_queue_lower{
    private:
        int data[MAX_ELEMENTS + 2], size;
        void ERROR(int id){
            if(id == 0) cerr << "option denied: No elements in the priority_queue." << endl;
            if(id == 1) cerr << "option denied: No enough elements in the priority_queue." << endl;
            if(id == 2) cerr << "option denied: Too many elements in the priority_queue." << endl;
            if(id == 3) cerr << "option denied: Target element is smaller than the required." << endl;
        }
        void swap(int &x, int &y){
            int tp = x; x = y; y = tp;
        }
    public:
        priority_queue_lower(){
            memset(data, 0, sizeof(data));
            size = 0;
        }
        ~priority_queue_lower(){}
        int minimum(){
            if(size == 0){ERROR(0); return 0;}
            else return data[1];
        }

        int extract_minimum(){
            if(size == 0){ERROR(0); return 0;}
            int res = data[1];
            swap(data[1], data[size]);
            size --;
            for(int i = 1; i * 2 <= size;){
                int l = i * 2, r = i * 2 + 1;
                if(r > size){
                    if(data[l] <= data[i]){
                        swap(data[i], data[l]);
                        i = l;
                    }else break;
                }else{
                    if(data[l] <= data[i] && data[l] <= data[r]){
                        swap(data[i], data[l]);
                        i = l;
                    }else if(data[r] <= data[i] && data[r] <= data[l]){
                        swap(data[r], data[i]);
                        i = r;
                    }else break;
                }
            }
            return res;
        }

        void decrease(int id, int x){
            if(id > size){ERROR(1);return;}
            if(data[id] < x){ERROR(3);return;}
            data[id] = x;
            while(id != 1){
                int par = id / 2;
                if(data[id] < data[par]){
                    swap(data[id], data[par]);
                    id /= 2;
                }else break;
            }
        }

        void insert(int x){
            if(size > MAX_ELEMENTS){ERROR(2);return;}
            size ++;
            data[size] = inf;
            decrease(size, x);
        }
}x;

int main(){
    int begintime = clock();
    for(int i = 1; i <= 10000000; i++){
        x.insert(rand());
//        cerr << "ok" << endl;
    }
    cerr << 1.0 * (clock() - begintime) / CLOCKS_PER_SEC << endl;
    /*
    x.decrease(10, 233333);
    x.decrease(20, 666666);
    for(int i = 1; i <= 23; i++){
        cerr << x.minimum() << ' ' << x.extract_minimum() <<endl;
    }*/return 0;
}