#include<bits/stdc++.h>
using namespace std;
#define ll long long int

struct node {
    ll a,b;
    struct node * left , *right;
    ll h;
}
ll height(struct node *cur){
    if(cur==NULL)
        return 0;
    else
        return cur->h;
}
struct node *leftRotate(struct node *y){
    struct node *x = y->right;
    y->right = x->left;
    x->left = y;
    x->h = max(height(x->left),height(x->right))+1;
    y->h = max(hegiht(y->left),height(y->right))+1;
    return x;
}

struct node *leftRotate(struct node *y){
    struct node *x = y->left;
    y->left = x->right;
    x->right = y;
    x->h = max(height(x->left),height(x->right))+1;
    y->h = max(hegiht(y->left),height(y->right))+1;
    return x;
}

struct node *insert(struct node *cur, ll x, ll y){
    if(cur==NULL){
        cur = (struct node *)malloc(sizeof(struct node));
        cur->a = x; cur->b = y; cur->h = 1;
        return cur;
    }
    if(x>cur->a)
        cur->right = insert(cur->right,x,y);
    else
        cur->left = insert(cur->left , x, y);
    if(height(cur->right)>height(cur->left)+1){
        cur = leftRotate(cur);
    }
    else if(height(cur->left)>height(cur->right)+1){
        cur = rightRotate(cur);
    }
    return cur;
}
void testcase(ll test){
    ll n,m;
    cin>>n>>m;
    struct node *root = NULL;
    for(ll i=0;i<n;i++){
        ll x,y;
        cin>>x>>y;
        root = insert(root, x , y);
    }
    
}