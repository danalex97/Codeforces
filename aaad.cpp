#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <numeric>
#include <map>
#include <tr1/unordered_map>
#include <set>
#include <algorithm>
#include <vector>
#include <cstring>
#include <sstream>
#include <queue>
#include <bitset>
#include <cmath>
using namespace std;

#define F cin
#define G cout

typedef long long lng;

const int K = 5010;
const int N = 300010; 
const int P = 100; 
const int B = 11; 
const int M = 1000000007;

int n,m,k,l,a[N];
lng dp[K][K];
bool mk[K][K];

#define make_pair(x,y) (x*N+y)

lng f(int x,int y)
{
	int t = x / l;
	if ( x == l && y == 0 ) return 0;
	if ( x == l+1 && y == 1 ) return 0;
	if ( x < l ) return -1<<30;
	if ( y < 0 ) return -1<<30;
	if ( mk[t][y] )
		return dp[t][y];
	mk[t][y] = 1;
	int ans = 0; 
	ans = max( f(x-l-1,y-1) + a[x-l] - a[x-l-1], f(x-l,y) + a[x-l+1] - a[x-l]); 
	return dp[t][y] = ans;
}

int main() 
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif
	
	F>>n>>k;
	for (int i=1;i<=n;++i)
		F>>a[i];
	sort(a+1,a+n+1);
	
	l = n/k;
	for (int i=n;i>=1;--i)
		if ( i/k >= l && i % k )
			++m;
		else
			break;
	G<<(a[n]-a[1])-f(n,m)<<'\n';
}
