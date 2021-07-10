#include<bits/stdc++.h>
using namespace std;
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

ll const mn = 1e5+5, mh = 18;
ll h[mn], p[mn][mh],n;
vvi v(mn);
void findLCA(ll i , ll par , ll dep){
	h[i] = dep;
	p[i][0] = par;
	for(ll j=1;j<mh;j++){
		p[i][j] = p[p[i][j-1]][j-1];
	}
	ll k = v[i].size();
	for(ll j=0;j<k;j++){
		if(v[i][j]==par)
			continue;
		findLCA(v[i][j] , i , dep+1);
	}
}

ll lca(ll x , ll y){
	if(h[x]<h[y])
		swap(x,y);
	ll i = 0,dif = h[x]-h[y];
	while(dif){
		if(dif%2==1)
			x = p[x][i];
		i++; dif/=2;
	}
	i = mh-1;
	while(i>=0){
		if(p[x][i]!=p[y][i])
		{
			x = p[x][i]; y = p[y][i];
		}
		i--;
	}
	if(x!=y){
		x = p[x][0];
	}
	return x;
}

void reset(){
	for(ll i=0;i<=n;i++){
		v[i].clear();
	}

}

void test_case(){
	cin>>n;
	reset();
	for(ll i=0;i<n-1;i++){
		ll x,y;
		cin>>x>>y;
		v[x].pb(y);
		v[y].pb(x);
	}
	findLCA(1,1,0);
	ll q;
	cin>>q;
	while(q--){
		ll k,x,par=-1,l1=-1,l2=-1,check=1,cur;
		cin>>k;
		priority_queue <pii> no;
		for(ll i=0;i<k;i++){
			cin>>x;
			no.push(mp(h[x],x));
		}
		l1 = no.top().second; no.pop();
		for(ll i=1;i<k;i++){
			cur = no.top().second; no.pop(); 
			if(par==-1){
				ll up = lca(l1,cur);
				if(up!=cur){
					par = up;
					l2 = cur;
				}
			}
			else{
				if(cur==par)
					continue;
				ll u1 = lca(l1,cur), u2 = lca(l2,cur);
				if(u1==par && u2==cur)
					check = 1;
				else if(u1==cur && u2==par)
					check = 1;
				else{
					check = 0; break;
				}
			}
		}
		if(check==1)
			cout<<"YES\n";
		else
			cout<<"NO\n";
	}
}

int main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
 	ll t;
 	cin>>t;
 	while(t--){
 		test_case();
 	}   

       
	return 0;
}