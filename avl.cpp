#include<bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds; 
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define ll long long int 
#define vi vector <long long int >
#define pii pair<long long int, long long int>
#define pb push_back
#define pf push_front
#define mod 1000000007
#define ff fflush()
#define mp make_pair
#define vvi vector<vector<ll>> 
#define vvpii vector<vector<pair<long long int , long long int >>>
#define vpii vector <pair<long long int , long long int>>

struct node {
    ll val,f,h,sub;
    struct node *l;
    struct node *r;
};

ll freq(struct node *cur){
    if(cur==NULL)
        return 0;
    else
        return cur->sub;
}


ll height(struct node *cur){
    if(cur==NULL)
        return 0;
    else
        return cur->h;
}

struct node *leftR(struct node *cur){
    struct node *y = cur->r->l;
    struct node *x = cur->r;
    cur->r = y;
    cur->sub = freq(cur->l) + freq(cur->r)+cur->f;
    cur->h = max(height(cur->l),height(cur->r))+1;
    x->l = cur;
    x->sub = freq(x->r)+ freq(x->l) + x->f;
    x->h = max(height(x->l),height(x->r))+1;
    return x;
}

struct node *rightR(struct node *cur){
    struct node *y = cur->l->r;
    struct node *x = cur->l;
    cur->l = y;
    cur->sub = freq(cur->l) + freq(cur->r)+cur->f;
    cur->h = max(height(cur->l),height(cur->r))+1;
    x->r = cur;
    x->sub = freq(x->r)+ freq(x->l) + x->f;
    x->h = max(height(x->l),height(x->r))+1;
    return x;
}

struct node * insert(struct node *cur , ll val , ll * ptr){
   
    if(cur==NULL){
        cur = (struct node *)malloc(sizeof(struct node) );
        cur->val = val; cur->f = 1; cur->h = 1; cur->sub = 1; cur->l = NULL ; cur->r = NULL;
        return cur;
    }
    if(cur->val==val){
        (*ptr) += freq(cur->l);
        cur->f++;
        cur->sub++;
        return cur;
    }
    else if((cur->val)>val){
        cur->sub++;
        cur->l = insert(cur->l , val , ptr);
    }
    else{
        cur->sub++;
        (*ptr) += freq(cur->l)+cur->f;
        cur->r = insert(cur->r , val , ptr);
    }
    cur->h = max(height(cur->r),height(cur->l))+ 1;
    if(height(cur->l)-height(cur->r)>1)
        cur = rightR(cur);
    else if(height(cur->r)-height(cur->l)>1)
        cur = leftR(cur);
    
    return cur;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);    
    ll n;
    cin>>n;
    ll a[n],c1[n] , c2[n];
    for(ll i=0;i<n;i++){
        cin>>a[i];
    }        
    struct node *root = NULL;
    for(ll i=0;i<n;i++){
        ll count = 0;
        root = insert(root , a[i], &count);
        c1[i] = count;
    }
    struct node *root1 = NULL;
    for(ll i=n-1;i>=0;i--){
        ll count = 0;
        root1 = insert(root1 , a[i], &count);
        c2[i] = count;
    }
    ll ans = 0;
    for(ll i=0;i<n;i++){
        // cout<<c1[i]<<" "<<c2[i]<<endl;
        ans = ans + c1[i]*c2[i];
    }
    cout<<ans<<"\n";
    return 0;
}
