#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <numeric>
#include <map>
#include <set>
#include <algorithm>
#include <vector>
#include <cstring>
#include <sstream>
#include <queue>
#include <bitset>
#include <cmath>
using namespace std;

typedef long long ll;

#define F cin
#define G cout

const int K = 3010;
const int N = 5010; 
const int P = 100; 
const int B = 11; 
const int M = 1000000000;

ll n,m;
int md;

int calc(ll x,ll r,ll s,ll a)
{
	a -= x;
	if ( a < 0 ) return 0;
	ll ct = a / r + 1;
	ct = min(ct,s);
	ll sm = ct % 2 == 0 ? ((ct/2)%md) * ((ct-1)%md) :  (ct%md) * (((ct-1)/2)%md);
	sm %= md;
	//cerr<<x<<' '<<r<<' '<<ct<<' '<<sm*r<<'\n';
	ll ans = ( ((ct%md) * (x%md)) % md + (sm*(r%md)) % md ) % md;
	return ans;
}

int solve(ll x,ll r,ll il,ll ir,ll ql,ll qr,ll mn,ll mx)
{
	if ( ql <= il && ir <= qr )
	{
		int ans = calc(x,r,ir-il+1,mx) - calc(x,r,ir-il+1,mn-1);
		if ( ans < 0 ) ans += md;
		ans %= md;
		return ans;
	}
	if ( ir < ql || il > qr ) return 0;
	
	ll rt = (ir-il+1)/2;
	ll lt = (ir-il+1)-rt;
	
	int ans = solve(x,r*2LL,il,il+lt-1,ql,qr,mn,mx); 
	if ( rt > 0 ) ans += solve(x+r,r*2LL,il+lt,ir,ql,qr,mn,mx); 
	ans %= md;
	
	return ans;
}

ll l,r,x,y;

int main() 
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif
	
	F>>n>>m>>md;
	for (int i=1;i<=m;++i)
	{
		F>>l>>r>>x>>y;
		G<<solve(1,1,1,n,l,r,x,y)<<'\n';
	}
}
