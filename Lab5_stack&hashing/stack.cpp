#include<stdio.h>
#include<string.h>
#include<iostream>
#include<stdlib.h>
#include<algorithm>
#include<queue>
using namespace std;

class stack_simulated_by_queue{
    private:
        queue<int>Q1;
        queue<int>Q2;
        void ERROR(int x){
            if(x == 1) cerr << "No element in stack." << endl;
        }
    public:
        void push(int x){
            Q1.push(x);
        }
        int top(){
            if(Q1.empty()){
                ERROR(1);
                return -1;
            }
            return Q1.back();
        }
        int pop(){
            if(Q1.empty()){
                ERROR(1);
                return -1;
            }
            while(Q1.size() != 1){
                Q2.push(Q1.front());
                Q1.pop();
            }
            Q1.pop();
            while(!Q2.empty()){
                Q1.push(Q2.front());
                Q2.pop();
            }return 0;
        }
};


int main(){
    int x,y;
    stack_simulated_by_queue data;
    while(1){
        cin >> x;
        if(x == 0) return 0;
        if(x == 1) {cin >> y; data.push(y);}
        if(x == 2) cerr << '\\' << data.top() << endl;
        if(x == 3) data.pop();
    }
}
