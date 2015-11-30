#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <numeric>
#include <map>
#include <set>
#include <algorithm>
#include <vector>
#include <cstring>
#include <sstream>
#include <queue>
#include <bitset>
using namespace std;

#define F cin
#define G cout

const int K = 110;
const int N = 100010; 
const int M = 1000000007;

int n,dad[N],cost[N];

int _dad(int x)
{
	if ( x == dad[x] ) 
		return x; 
	int dd = _dad(dad[x]);
	cost[x] = ( cost[x] + cost[dad[x]] ) % M;
	dad[x] = dd;
	return dad[x]; 
}

int main() 
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif

	F>>n;
	for (int i=1;i<=n;++i)
		dad[i] = i;
	int ans = 0;
	for (int i=1,k,x,y;i<=n;++i)
	{
		F>>k;
		while ( k-- )
		{
			F>>x>>y;
			int dd = _dad(x);
			cost[dd] = ( cost[x] + y ) % M;
			ans = ( ans + cost[dd] ) % M;
			dad[dd] = i;
		}
		//cerr<<ans<<'\n';
	}
	if ( ans < 0 ) ans += M;
	G<<ans<<'\n';
}
