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
//typedef set<node,bool(*)(node,node)> myset; // custom set

#define F cin
#define G cout

const int K = 1010;
const int N = 100010; 
const int P = 35; 
const int B = 11; 
const int M2 = 7340033;
const int M = 1000000007;

int n,a[N],dp[N],ans;
vector<int> v[N];

void dfs(int x,int dd)
{
	int l = lower_bound(dp+1,dp+n+1,a[x]) - dp;
	ans = max(ans,l);
	int now = dp[l];
	dp[l] = a[x];
	for (int i=0;i<int(v[x].size());++i)
	{
		int y = v[x][i];
		if ( y != dd ) 
			dfs(y,x);
	}
	dp[l] = now;
}

int main()
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif
	
	F>>n;
	for (int i=1;i<=n;++i)
		F>>a[i];
	for (int i=1,x,y;i<n;++i)
	{
		F>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	
	memset(dp,0x3f,sizeof(dp));
	for (int i=1;i<=n;++i)
		dfs(i,0);
	G<<ans<<'\n';
}




