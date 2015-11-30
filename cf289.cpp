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

const int K = 510;
const int N = 100010; 
const int P = 22; 
const int B = 11; 
const int M = 1000000007;
const int M2 = 1000000009;

int n,dp[K][K],a[K];

int f(int x,int y)
{
	if ( x == y )
		return 1;
	if ( x > y ) 
		return 0;  
	if ( ~dp[x][y] )
		return dp[x][y];
	int &ans = dp[x][y];
	ans = f(x+1,y);
	for (int j=x+2;j<=y;++j)
		if ( a[j] > a[x+1] )
			ans = ( 1LL * ans + 1LL * f(x+1,j-1) * f(j-1,y) ) % M;
	//cerr<<x<<' '<<y<<' '<<ans<<'\n';
	return ans;
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
	memset(dp,-1,sizeof(dp));
	G<<f(1,n)<<'\n';
}
