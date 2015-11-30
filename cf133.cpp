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
#include <cmath>
using namespace std;

#define F cin
#define G cout

const int K = 25;
const int N = 100005; 
const int M = 1000000007;

map<int,long long> mp;

int b,k,n,a[N],co,now;
long long ans,zeros;

int main() 
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif
	
	F>>b>>k>>n;
	for (int i=1;i<=n;++i)
		F>>a[i];
		
	b--;
	for (int i=1;i<=n;++i)
	{
		if ( a[i] == 0 )
		{
			co++;
			zeros += co;
		}
		else
		{
			co = 0;
		}
		
		mp[now]++;
		now = ( now + a[i] ) % b;
		ans += mp[(now-k+b)%b];
	}
	
	if ( k == b ) 
		ans -= zeros;
	if ( k == 0 )
		ans = zeros;
	G<<ans<<'\n';
}
