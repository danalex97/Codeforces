#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 1510;

ifstream F("permsplitcount.in");
ofstream G("permsplitcount.out");

int n,m,dp[N][N],fact;

int main()
{
	F>>n>>m;
	for (int i=1;i<=n;++i)
	{
		dp[i][1] = 1;
		for (int j=2;j<=i;++j)
			dp[i][j] = ( ( dp[i-1][j] + dp[i][j-1] ) % m + dp[i-1][j-1] ) % m;
	}
	fact = 1;
	for (int i=2;i<=n;++i)
		fact = (1LL * fact * i) % m;
	G<<(fact-dp[n][n]+m)%m<<'\n';
}

