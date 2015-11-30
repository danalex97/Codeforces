#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <numeric>
#include <map>
#include <set>
#include <tr1/unordered_map>
#include <tr1/unordered_set>
#include <algorithm>
#include <vector>
#include <cstring>
#include <sstream>
#include <queue>
#include <bitset>
#include <cmath>
using namespace std;
using namespace tr1;

typedef long long lng;

#define F cin
#define G cout

const int N = 5010;

int n,id,x[N],y[N],z[N],cnt[N];
vector<int> v[N];

lng sum,ans,mn;

int dfs(int u,int f)
{
	int d = x[f]+y[f]-u;
	int sz = 1;
	
	for (int i=0;i<int(v[u].size());++i)
	{
		int v = x[::v[u][i]] + y[::v[u][i]] - u;
		if ( v == d ) continue;
		sz += dfs(v,::v[u][i]);
	}
	if ( f )
	{
		if ( u < d ) 
			cnt[f]=sz;
		else 
			cnt[f]=n-sz;
		sum += 1LL*sz*(n-sz)*z[f];
	}
	return sz;
}

void solve(int number,int u,int f,lng c)
{
	int d = x[f]+y[f]-u;
	lng k = 0;
    
    if ( f ) 
    {
		if ( u < d ) 
			k = cnt[f];
		else 
			k = n - cnt[f];
     	k = c+1LL*(number-k)*(n-number+k)*z[f]-1LL*(n-k)*k*z[f];
    }
    else 
		k = c;
   
	mn = min(mn,k);

	for (int i=0;i<int(v[u].size());++i)
	{
		int v = x[::v[u][i]] + y[::v[u][i]] - u;
		if ( v == d || ::v[u][i] == id ) continue;
		solve(number,v,::v[u][i],k);
	}
}

int main() 
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif

	F>>n;
	for(int i=1;i<n;i++)
	{
		F>>x[i]>>y[i]>>z[i];
		v[x[i]].push_back(i);
		v[y[i]].push_back(i);
		if ( x[i] > y[i] ) swap(x[i],y[i]);
	}
	dfs(1,0);
	ans = sum;

	for (int i=1;i<n;++i)
	{
		id = i;
		mn = sum;
		
		long long tmp = sum;
		
		solve(cnt[i],x[i],0,0);
		
		tmp += mn;
		
		mn = sum;
		solve(n-cnt[i],y[i],0,0);
		tmp += mn;
		
		ans = min(ans,tmp);
	}
	G<<ans<<'\n';
}

