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
#define vpii vector <pair<long long int , long long int>>
ll const mn = 6e5+5;
ll seg[4*mn], lazy[4*mn];
void init(){
	for(ll i=0;i<4*mn;i++){
		seg[i] = 0;
		lazy[i] = 0;
	}
}


//function to query the segment seg for RMQ
ll query(ll index,ll s,ll e,ll qs,ll qe ,ll up)
{
	//base case: if query range is outside the node range
	if(qs>e || s>qe)
		return INT_MIN;
	//complete overlap
	if(s>=qs && e<=qe){
		lazy[index] = max(lazy[index],up);
		return max(seg[index],lazy[index]);
	}
	//now partial overlap case is executed
	lazy[index] = max(lazy[index] , up);
	ll m = (s+e)/2;
	ll left_ans = query(2*index+1,s,m,qs,qe,lazy[index]);
	ll right_ans = query(2*index+2,m+1,e,qs,qe,lazy[index]);
	return max(left_ans,right_ans);
}

//function to update a value at position to "pos"
void updateNode(ll index,ll s,ll e,ll pos,ll val)
{
	if(pos<s || pos>e)
		return ;
	if(s==e)
	{
		seg[index] = val;
		return ;
	}
	ll m = (s+e)/2;
	updateNode(2*index+1,s,m,pos,val);
	updateNode(2*index+2,m+1,e,pos,val);
	seg[index] = max(seg[2*index+2],seg[2*index+1]);
	return;
}

//function to update the values in a range
void updateRange(ll index,ll s,ll e,ll rs,ll re,ll val)
{
	//query range outside the node range
	if(s>re || e<rs)
		return;
	if(s>=rs && e<=re)
	{
		seg[index] = max(seg[index],val);
		lazy[index] = max(lazy[index],val);
		return ;
	}
	ll m = (s+e)/2;
	updateRange(2*index+1,s,m,rs,re,val);
	updateRange(2*index+2,m+1,e,rs,re,val);
	seg[index] = max(seg[2*index+1],seg[2*index+2]);
	return;
}

int main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
 	ll n,m;
 	set<ll> s;
 	cin>>n>>m;
 	vvpii v(n+1);
 	for(ll i=0;i<m;i++){
 		ll x,y,z;
 		cin>>x>>y>>z;
 		v[x].pb(mp(y,z));
 		s.insert(y);
 		s.insert(z);
 	}	
 	ll c = 0;
 	map<ll , ll> in;
 	for(auto it = s.begin(); it!=s.end(); it++){
 		in[*it] = c;
 		c++;
 	}
 	init();
 	ll ans = 0;
 	ll dp[n+1], p[n+1];
 	for(ll i=n;i>=1;i--){
 		ll k = v[i].size();
 		ll val = 0;
 		p[i] = 0;
 		for(ll j=0;j<k;j++){
 			ll l = in[v[i][j].first];
 			ll r = in[v[i][j].second];
 			ll mx = query(0,0,c-1,l,r,0);
 			if(mx>=val){
 				val = mx;
 				p[i] = j;
 			}
 		}
 		val++;
 		ans = max(val , ans);
 		dp[i] = val;
 		for(ll j=0;j<k;j++){
 			ll l = in[v[i][j].first];
 			ll r = in[v[i][j].second];
 			updateRange(0,0,c-1,l,r,val);
 		}
 	}
 	cout<<n-ans<<"\n";
 	ll par = 0;
 	for(ll i=1;i<=n;i++){
 		if(ans==dp[i]){
 			par = i;
 			break;
 		}
 		else{
 			cout<<i<<" ";
 		}
 	}
 	for(ll i=par+1;i<=n;i++){
 		if(dp[i]!=dp[par]-1){
 			cout<<i<<" ";
 			continue;
 		}
 		ll k = v[i].size(),ch = 0;
 		for(ll j=0;j<k && ch==0;j++){
 			if(v[i][j].first>v[par][p[par]].second || v[i][j].second < v[par][p[par]].first){
 				continue;
 			}
 			else
 				ch = 1;
 		}
 		if(ch==0){
 			cout<<i<<" ";
 		}
 		else
 		{
 			par = i;
 		}
 	}
 	cout<<"\n";
 	return 0;
}