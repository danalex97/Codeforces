#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

#define F cin
#define G cout

const int N = 70;

long long l,r;
long long dp[N],dp2[N];

long long count(long long n)
{
	if ( n == 0 ) 
		return 0;
		
	int lg = 0;
	long long ans = 0;
	while ( (1LL<<lg) <= n )
		++lg;
	
	memset(dp,0,sizeof(dp));
	memset(dp2,0,sizeof(dp2));
	for (int i=1;i<=lg;++i)
		for (int j=1;j<=i;++j)
			if ( i % j == 0 )
			{
				if ( dp[j] == 0 )
					dp[j] = 1;
				else
					dp[j] = (dp[j] << j) + 1;
				dp2[j] = max( min(n,(1LL<<i)-1) / dp[j] - (1LL<<(j-1)) + 1 , 0LL );
				for (int k=1;k<j;++k)
					if ( j % k == 0 )
						dp2[j] -= dp2[k];
				if ( j < i ) 
					ans += dp2[j];
			} 
	return ans;
}


int main()
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif

	F>>l>>r;
	G<<count(r)-count(l-1)<<'\n';
}
