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

ll const mn = 3e5+5,qn = 5e5+5;
vi a;
vvpii v(mn);
ll parent[mn] , h[mn], xo[mn],sub[mn],heavy[mn],head[mn],pos[mn],cur = 0,n,q;
ll p[mn][20];
struct query {
	ll x,y,w,vis;
}qe[qn];
bool s[4*mn], lazy[4*mn];

void init(){
	for(ll i=0;i<4*mn;i++){
		s[i] = false;
		lazy[i] = false;
	}
	for(ll i=0;i<=n;i++){
		parent[i] = i;
		h[i]= 0;
	}
}

bool query(ll v ,ll l, ll r, ll low , ll high){
	if(l>=low && r<=high)
		return s[v];
	if(l>high || r<low || l>r)
		return false;
	ll m = (l+r)/2;
	if(lazy[v]==true)
		return true;
	return (query(2*v+1, l , m, low,high) | query(2*v+2,m+1,r,low,high));
}

bool update(ll v, ll l, ll r , ll low, ll high){
	if(l>=low && r<=high){
		s[v] = true; lazy[v] = true;
		return true;
	}
	if(l>r  || l>high || r<low)
		return false;
	ll m = (l+r)/2;
	s[v] = s[v] | update(2*v+1,l , m , low, high);
	s[v] = s[v] | update(2*v+2,m+1,r, low,high);
	return s[v];
}


void dfs(ll i, ll par , ll val , ll dep){
	ll k = v[i].size();
	h[i] = dep;
	xo[i] = val; 
	sub[i] = 1;
	ll maxi = 0;
	p[i][0] = par;
	for(ll j=1;j<20;j++){
		p[i][j] = p[p[i][j-1]][j-1];
	}
	for(ll j=0;j<k;j++){
		if(par==v[i][j].first)
			continue;
		dfs(v[i][j].first , i , val^v[i][j].second , dep+1);
		sub[i] += sub[v[i][j].first];
		if(sub[v[i][j].first]>maxi){
			maxi = sub[v[i][j].first]; heavy[i] = v[i][j].first;
		}
	}
}

void decompose(ll i , ll h, ll par){
	head[i] = h; pos[i] = cur; cur++; a.pb(i);
	if(heavy[i]!=0){
		decompose(heavy[i],h,i);
	}
	ll k = v[i].size();
	for(ll j=0;j<k;j++){
		if(v[i][j].first==par || heavy[i]==v[i][j].first)
			continue;
		decompose(v[i][j].first, v[i][j].first , i);
	}
}

ll lca(ll x , ll y){
	if(h[x]<h[y])
		swap(x,y);
	ll po=h[x]-h[y], c = 0;
	while(po){
		if(po%2==1)
			x = p[x][c];
		po/=2;
		c++;
	}
	for(ll i=19;i>=0;i--){
		if(p[x][i]!=p[y][i]){
			x = p[x][i]; y = p[y][i];
		}
	}
	if(x!=y)
		x = p[x][0];
	return x;
}

bool ask(ll x , ll par){
	if(h[x]<=h[par])
		return false;
	ll r = x;
	for(ll i=19;i>=0;i--){
		if(head[p[r][i]]==head[x])
			r = p[r][i];
	}
	ll in = pos[r];
	if(h[r]<=h[par])
		in = pos[par]+1;
	return (query(0,0,n-1,in,pos[x]) | ask(p[r][0] , par));
}

void change(ll x , ll par){
	if(h[x]<=h[par])
		return;
	ll r = x;
	for(ll i=19;i>=0;i--){
		if(head[p[r][i]]==head[x])
			r = p[r][i];
	}
	ll in = pos[r];
	if(h[r]<=h[par])
		in = pos[par]+1;
	update(0,0,n-1,in,pos[x]);
	change(p[r][0] , par);
}

int main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
 	cin>>n>>q;
 	init();
 	for(ll i=0;i<q;i++){
 		cin>>qe[i].x>>qe[i].y>>qe[i].w;
 		qe[i].vis = 0;
 		ll x = qe[i].x , y = qe[i].y;
 		while(parent[x]!=x)
 			x = parent[x];
 		while(parent[y]!=y)
 			y = parent[y];
 		if(x!=y){
 			v[qe[i].x].pb(mp(qe[i].y,qe[i].w));
 			v[qe[i].y].pb(mp(qe[i].x,qe[i].w));
 			qe[i].vis = 1;
 			if(h[x]==h[y]){
 				parent[y] = x;
 				h[x]++;
 			}
 			else if(h[x]>h[y])
 				parent[y] = x;
 			else
 				parent[x] = y;
 		}	
 	}

 	for(ll i=2;i<=n;i++){
 		ll x = 1, y = i;
 		while(parent[x]!=x)
 			x = parent[x];
 		while(parent[y]!=y)
 			y = parent[y];
 		if(x!=y){
 			v[1].pb(mp(i,0));
 			v[i].pb(mp(1,0));
 			if(h[x]==h[y]){
 				parent[y] = x;
 				h[x]++;
 			}
 			else if(h[x]>h[y])
 				parent[y] = x;
 			else
 				parent[x] = y;
 		}
 	}
 	
 	dfs(1,1,0,0);
 	decompose(1,1,1);
 	for(ll i=0;i<q;i++){
 		if(qe[i].vis==1){
 			cout<<"Yes\n";
 			continue;
 		}
 		ll x= qe[i].x, y = qe[i].y;
 		if((xo[x]^xo[y]^qe[i].w)!=1){
 			cout<<"No\n";
 			continue;
 		}
 		ll par = lca(qe[i].x , qe[i].y);
 		if(ask(x,par)==true || ask(y,par)==true){
 			cout<<"No\n"; continue ;
 		}
 		change(x,par); change(y,par);
 		cout<<"Yes\n";
 	}
 	return 0;
}