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

const int K = 1010;
const int N = 2000010; 
const int P = 100; 
const int B = 11; 
const int M = 1000000007;

int n,m,a[N],b[N],c[N<<1],z[N<<1];

int main() 
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif

	F>>n>>m;
	for (int i=1;i<=n;++i) F>>a[i];
	for (int i=1;i<=m;++i) F>>b[i];
	
	if ( m == 1 )
	{
		G<<n<<'\n';
		return 0;
	}
	
	for (int i=1;i<n;++i) a[i] -= a[i+1];
	for (int i=1;i<m;++i) b[i] -= b[i+1];
	
	n--, m--;
	for (int i=1;i<=m;++i) c[i] = b[i];
	for (int i=1;i<=n;++i) c[m+i] = a[i];
	n = m+n;
	
	z[1] = 0;
	int l = 0 , r = 0, ans = 0;
	for (int i=2;i<=n;++i)
	{
		//cerr<<i<<' '<<l<<' '<<r<<' ';
		if ( i > r )
		{
			l = i;
			r = i-1;
			while ( c[r-l+2] == c[r+1] && r+1 <= n )
				++r;
			z[i] = r-l+1;
		} 
		else
		{
			//cerr<<z[i-l+1]<<' ';
			if ( i + z[i-l+1] - 1 >= r )
			{
				l = i;
				r = r;
				while ( c[r-l+2] == c[r+1] && r+1 <= n )
					++r;
				z[i] = r-l+1;
			}
			else
				z[i] = z[i-l+1];
		}
		if ( z[i] >= m && i > m )
			++ans;
		//cerr<<'\n';
	}
	//for (int i=1;i<=n;++i) cerr<<c[i]<<' '; cerr<<'\n';
	//for (int i=1;i<=n;++i) cerr<<z[i]<<' '; cerr<<'\n';
	G<<ans<<'\n';
}
