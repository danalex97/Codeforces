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

const int K = 110;
const int N = 3110; 
const int P = 100; 
const int B = 11; 
const int M = 1000000007;

int n,l,a[N],b[N],dp[N][K][2];

int main() 
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif

	F>>n>>l;
	for (int i=1;i<=n;++i)
		F>>a[i]>>b[i];
	for (int i=1;i<=n;++i)
		if ( a[i] != b[i] )
		{
			dp[a[i]][i][0] = 1;
			dp[b[i]][i][1] = 1;
		}
		else
			dp[a[i]][i][0] = 1;
	for (int i=1;i<=l;++i)
		for (int j=1;j<=n;++j)
			for (int s=0;s<2;++s)
				if ( dp[i][j][s] )
				{
					int ln = s == 1 ? a[j] : b[j];
					//cerr<<ln<<'\n';
					for (int k=1;k<=n;++k)
						if ( k != j )
						{
							if ( a[k] != b[k] )
							{
								if ( a[k] == ln ) (dp[i+ln][k][0] += dp[i][j][s]) %= M;
								if ( b[k] == ln ) (dp[i+ln][k][1] += dp[i][j][s]) %= M;
							}
							else
								if ( a[k] == ln ) (dp[i+ln][k][0] += dp[i][j][s]) %= M;
						}
				}
	//for (int i=1;i<=l;++i)
	//	for (int j=1;j<=n;++j)
	//		cerr<<i<<' '<<j<<' '<<dp[i][j][0]<<' '<<dp[i][j][1]<<'\n';
	int ans = 0;
	for (int i=1;i<=n;++i)	
	{
		//cerr<<dp[l][i][0]<<' '<<dp[l][i][1]<<'\n';
		ans = (ans + dp[l][i][0]) % M;
		if ( a[i] != b[i] )
			ans = (ans + dp[l][i][1]) % M; 
	}
	G<<ans<<'\n';
}
