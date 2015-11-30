#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <set>
#include <cstring>
#include <cmath>
#include <iomanip>
using namespace std;

#define F cin
#define G cout

const int L = 20;
const int N = 110;
const int M = 1010;

int n,m,x,s;
long double dp[2][N*M+M];
long double sp[2][N*M+M];

int main()
{
    ios::sync_with_stdio(0);
    #ifndef ONLINE_JUDGE
        ifstream F("p.in");
    #endif

	F>>n>>m;
	F>>x;
	s += x;
	for (int i=1;i<=m;++i)
		if ( i != x ) 
			dp[1&1][i] = 1;
	if ( m == 1 )
	{
		G<<"1\n";
		return 0;
	}
	for (int i=2;i<=n;++i)
	{
		F>>x;
		s += x;
		memset(dp[i&1],0,sizeof(dp[i&1]));
		memset(sp[i&1],0,sizeof(sp[i&1]));
		for (int j=0;j<n*m;++j)
		{
			sp[i&1][j+1] += dp[(i-1)&1][j];
			sp[i&1][j+x] -= dp[(i-1)&1][j];
			sp[i&1][j+x+1] += dp[(i-1)&1][j];
			sp[i&1][j+m+1] -= dp[(i-1)&1][j];
		}
		for (int j=1;j<=n*m;++j)
		{
			dp[i&1][j] = dp[i&1][j-1] + sp[i&1][j] / (m-1);
			//cerr<<dp[i&1][j]<<' ';
		}
		//cerr<<'\n';
	}
	long double ans = 1;
	for (int i=1;i<s;++i)
		ans += dp[n&1][i];
	G<<fixed<<setprecision(12)<<ans<<'\n';
}
