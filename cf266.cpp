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
const int N = 1010; 
const int P = 22; 
const int B = 11; 
//const int M = 1000000007;
const int M2 = 1000000009;

int n,m,M;
lng dp[N][N];

int main()
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif
	
	F>>n>>m>>M;
	
	lng p = 1, ans = 0;
	dp[0][0] = 1;
	for (int i=1;i<=n;++i)
	{
		dp[i][0] = 0;
		
		for (int j=1;j<m;++j)
			dp[i][j] = dp[i-1][j];
		for (int j=0;j<m;++j)
			for (int c=1;c<=9;++c)
			{
				lng &x = dp[i][(j+c*p)%m];
				x += dp[i-1][j];
				x %= M;
			}
		if ( i == n ) 
			ans = (ans * 9) % M;
		else
			ans = (ans * 10) % M;
		ans = ( ans + dp[i][0] ) % M;
		
		dp[i][0] = 1;
		p = (p * 10) % m;
	}
	G<<ans<<'\n';
}
