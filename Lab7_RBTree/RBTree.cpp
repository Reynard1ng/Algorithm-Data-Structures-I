#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<unistd.h>
#include<fstream>
using namespace std;

int data[50000010];

class Node{
    public:
        int val, col;
        Node *ch[2], *p;
        Node(){};
        Node(int _val, int _col, Node *_left, Node *_right, Node *_p):
            val(_val), col(_col), p(_p){
                ch[0] = _left, ch[1] = _right;
            };
};

class RedBlackTree{
    private:
        Node *nil;
        Node *root;
        void rotate(Node *x, int dir){
            int rdir = dir ^ 1;
            Node *y = x->ch[rdir];
            x -> ch[rdir] = y -> ch[dir];
            if(y -> ch[dir] != nil)
                y -> ch[dir] -> p = x;
            y -> p = x -> p;
            if(x -> p == nil)
                root = y;
            else if(x == x -> p -> ch[dir])
                x -> p -> ch[dir] = y;
            else x -> p -> ch[rdir] = y;
            y -> ch[dir] = x;
            x -> p = y;
        }
        void insertFixup(Node *z){
            Node *y;
            int dir;
            while(z -> p -> col == 0){
                if(z -> p == z -> p -> p -> ch[0]) dir = 0;
                else dir = 1;
                int rdir = dir ^ 1;
                y = z -> p -> p -> ch[rdir];
                if(y -> col == 0){
                    z -> p -> col = 1;
                    y -> col = 1;
                    z -> p -> p -> col = 0;
                    z = z -> p -> p;
                }else{
                    if(z == z -> p -> ch[rdir]){
                        z = z -> p;
                        rotate(z, dir);
                    }
                    z -> p -> col = 1;
                    z -> p -> p -> col = 0;
                    rotate(z -> p -> p, rdir);
                }
            }root -> col = 1;
        }
        Node *queryForNode(int x){
            Node *ans = root;
            while(ans != nil && ans -> val != x){
                if(ans -> val > x) ans = ans -> ch[0];
                else ans = ans -> ch[1];
            }return ans;
        }
        Node *maximumInTree(Node *x){
            while(x -> ch[1] != nil) x = x -> ch[1];
            return x;
        }
        Node *minimumInTree(Node *x){
            while(x -> ch[0] != nil) x = x -> ch[0];
            return x;
        }
        void outit(Node *x){
            if(x == nil) return;
            printf("val:%d col:%d\n", x->val, x->col);
            printf("leftson:");
            if(x -> ch[0] == nil) printf("nil\n");
            else printf("%d\n",x->ch[0]->val);
            printf("rightson:");
            if(x -> ch[1] == nil) printf("nil\n");
            else printf("%d\n",x->ch[1]->val);
            printf("\n");
            outit(x -> ch[0]);
            outit(x -> ch[1]);
        }
        void clearTree(Node *x){
            if(x == nil) return;
            clearTree(x -> ch[0]);
            clearTree(x -> ch[1]);
            delete x;
        }
    public:
        RedBlackTree(){
            nil = new Node(-1, 1, 0, 0, 0);
            nil -> ch[0] = nil;
            nil -> ch[1] = nil;
            nil -> p = nil;
            root = 0;
        }
        Node * newnode(int _val){
            return new Node(_val, 1, nil, nil, nil);
        }
        void insert(Node *z){
            if(root == 0) {root = z; return;}
            Node *y = nil;
            Node *x = root;
            while(x != nil){
                y = x;
                if(z -> val < x -> val)
                    x = x -> ch[0];
                else x = x -> ch[1];
            }
            z -> p = y;
            if(y == nil)
                root = z;
            else if(z -> val < y -> val)
                y -> ch[0] = z;
            else y -> ch[1] = z;
            z -> ch[0] = z -> ch[1] = nil;
            z -> col = 0;
            insertFixup(z);
        }
        int maximum(){
            return maximumInTree(root) -> val;
        }
        int minimum(){
            return minimumInTree(root) -> val;
        }
        int query(int x){
            Node *ans = queryForNode(x);
            return ans -> val;
        }
        int predecessor(int x){
            Node *ans = queryForNode(x);
            if(ans -> ch[0] != nil) return maximumInTree(ans -> ch[0]) -> val;
            while(ans -> p != nil){
                if(ans -> p -> ch[1] == ans) return ans -> p -> val;
                ans = ans -> p;
            }
            return -1;
        }
        int successor(int x){
            Node *ans = queryForNode(x);
            if(ans -> ch[1] != nil) return minimumInTree(ans -> ch[1]) -> val;
            while(ans -> p != nil){
                if(ans -> p -> ch[0] == ans) return ans -> p -> val;
                ans = ans -> p;
            }
            return -1;
        }
        void out(){
            outit(root);
        }
        void clear(){
            if(root == 0) return;
            clearTree(root);
            root = 0;
        }
};

int main(){
    RedBlackTree RBT;
    srand(time(NULL));
    ofstream fout("RBTree.csv");
    
    for(int N = 100000; N <= 10000000; N+=100000){
    
    RBT.clear();
    for(int i = 1; i <= N; i++)
        data[i] = i;
    random_shuffle(data+1, data+N+1);
    int t1 = clock();
    for(int i = 1; i <= N; i++)
        RBT.insert(RBT.newnode(data[i]));
//        RBT.out();
    fout << N << "," << (clock() - t1) / 1.0 / CLOCKS_PER_SEC << endl;
    cerr << N << endl;
    }
}
