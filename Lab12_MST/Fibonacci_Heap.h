#pragma once

#include <vector>
#include <cstring>
#include <algorithm>
#include <map>
#include <iostream>
using namespace std;

template <class T>
class Fibonacci_Heap {
private:
	struct Node {
		T key;
		int degree;
		bool mark;
		Node *p, *child, *left, *right;
		Node(T k) : key(k), degree(0), mark(false) {
			p = child = nullptr;
			left = right = this;
		}
	};

	Node *Min;
	int n;
//	map<T, Node*> mp;
    vector <Node *> mp;
	void Del_Tree(Node *root);
	void Consolidate();
	void Link(Node *y, Node *x);
	void Cut(Node *x, Node *y);
	void Cascading_Cut(Node *y);
public:
	Fibonacci_Heap();
	~Fibonacci_Heap();

	void Push(int id, T x);
	bool Empty();
	T Top();
	void Pop();
	void Decrease_Key(int id, T k);
};

template <class T>
Fibonacci_Heap<T>::Fibonacci_Heap() {
    Min = nullptr;
    n = 0;
}

template <class T>
void Fibonacci_Heap<T>::Del_Tree(Node *root) {
    if(root -> child != nullptr) {
        Node *ptr = root -> child;
        do {
            Del_Tree(ptr);
            ptr = ptr -> right;
        } while(ptr != root -> child);
    }
    delete root;
}

template <class T>
Fibonacci_Heap<T>::~Fibonacci_Heap() {
    mp.clear();
    Node *ptr = Min;
    if(ptr == nullptr)return;
    do {
        Del_Tree(ptr);
        ptr = ptr -> right;
    } while(ptr != Min);
}

template <class T>
void Fibonacci_Heap<T>::Push(int id, T x) {
    while(mp.size() <= id) mp.push_back(nullptr);
    Node *elem = new Node(x);
    mp[id] = elem;
    n++;
    
    if(n == 1){
        Min = elem;
    }else{
        Node *bet = Min -> left;
        bet -> right = elem;    Min -> left = elem;
        elem -> left = bet;     elem -> right = Min;
        if(Min -> key > elem -> key)
            Min = elem;
    }
    //Your code
}

template <class T>
bool Fibonacci_Heap<T>::Empty() {
    if(n==0) return true;
    else return false;
    //Your code
}

template <class T>
T Fibonacci_Heap<T>::Top() {
    return Min -> key;
    //Your code
}

template <class T>
void Fibonacci_Heap<T>::Pop() {
//    cerr << "POP" << endl;
//    cerr << Min -> key << endl;
    if(n == 0) return;
    n--;
    if(n == 0) {
        delete Min;
        Min = nullptr;
        return;
    }
    Node *tmp = Min -> child;
    vector <Node *> chdlist;  
    if(tmp != nullptr)
        do{
            chdlist.push_back(tmp);
            tmp = tmp -> right;
        }while(tmp != Min -> child);
    for(int i = 0; i < chdlist.size(); i++){
        Node *elem = chdlist[i];
        Node *bet = Min -> left;
        elem -> p = nullptr;
        bet -> right = elem;    Min -> left = elem;
        elem -> left = bet;     elem -> right = Min;
    }
    Node *l = Min -> left;
    Node *r = Min -> right;
    l -> right = r;
    r -> left = l;
    delete Min;
    Min = l;
    Consolidate();
    //Your code
}

template <class T>
void Fibonacci_Heap<T>::Consolidate() {
//    cerr << "CONSOLIDATE" << endl;
    vector<Node *>A;
    vector<Node *>rootlist;
    Node *tmp = Min;
    do{
        rootlist.push_back(tmp);
        tmp = tmp -> right;
    }while(tmp != Min);
    for(int i = 0; i < rootlist.size();i++){
        Node *x = rootlist[i];
        int d = x -> degree;
        while(A.size() < d + 5)
            A.push_back(nullptr);
        while(A[d] != nullptr){
            Node *y = A[d];
            if(x -> key > y -> key){Node *z = x; x = y; y = z;}
            Link(y, x);
            A[d] = nullptr;
            d++;
        }
        while(A.size() < d + 5)
            A.push_back(nullptr);
        A[d] = x;
    }
    Min = nullptr;
    for(int i = 0; i < A.size(); i++)
        if(A[i] != nullptr){
            if(Min == nullptr){
                Min = A[i];
                Min -> right = Min -> left = Min;
            }else{
                Node *elem = A[i];
                Node *bet = Min -> left;
                bet -> right = elem;    Min -> left = elem;
                elem -> left = bet;     elem -> right = Min;
                if(Min -> key > elem -> key)
                    Min = elem;
            }
        }
    //Your code
}

template <class T>
void Fibonacci_Heap<T>::Link(Node *y, Node *x) {
//    cerr << "LINK" << endl;
    Node *l = y -> left;
    Node *r = y -> right;
    l -> right = r;
    r -> left = l;

    y -> p = x;
    x -> degree++;
    y -> mark = false;
    if(x -> child == nullptr){
        x -> child = y;
        y -> left = y -> right = y;
    }else{
        Node * cl = x -> child;
        Node * cr = cl -> right;
        cl -> right = y;    cr -> left = y;
        y -> left = cl;    y -> right = cr;
    }
    //Your code
}

template<class T>
void Fibonacci_Heap<T>::Decrease_Key(int id, T k) {
//    cerr << "DECREASE_KEY" << endl;
    Node *x = mp[id];
    if(x == nullptr) return;
    if(k >= x -> key) return;
    x -> key = k;
    Node *y = x -> p;
    if(y != nullptr && x -> key < y -> key){
        Cut(x,y);
        Cascading_Cut(y);
    }if(Min -> key > x -> key)
        Min = x;
    //Your code
}

template <class T>
void Fibonacci_Heap<T>::Cut(Node *x, Node *y) {
//    cerr << "CUT" << endl;
    y -> degree--;
    if(y -> degree == 0){
        y -> child = nullptr;
    }else{
        if(y -> child == x)
            y -> child = x -> right;
        Node *l = x -> left;
        Node *r = x -> right;
        l -> right = r;
        r -> left = l;
    }
    x -> p = nullptr;
    Node *bet = Min -> left;
    bet -> right = x;   Min -> left = x;
    x -> left = bet;    x -> right = Min;
    //Your code
}

template <class T>
void Fibonacci_Heap<T>::Cascading_Cut(Node *y) {
//    cerr << "CASCADING_CUT" << endl;
    Node *z = y -> p;
    if(z != nullptr){
        if(y -> mark == false)
            y -> mark = true;
        else{
            Cut(y, z);
            Cascading_Cut(z);
        }
    }
    //Your code
}

