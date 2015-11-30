#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
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

const int M = 1000000007;
const int N = 100010;

#define mp make_pair

int n,nxt[N*40][2],co;
long long a[N];

void add(long long x,long long y,int wh)
{
	if ( y ) 
	{
		int bit = (x & y) > 0;
		int &now = nxt[wh][bit]; 
		if ( !now )
			now = ++co;
		add(x,y>>1,now);
	}
}

long long ask(long long x,long long y,int wh)
{
	if ( y ) 
	{
		int bit = (x & y) == 0;
		if ( nxt[wh][bit] )
			return ask(x,y>>1,nxt[wh][bit]) + y;
		else
			return ask(x,y>>1,nxt[wh][1-bit]);
	}
	return 0;
}

int main()
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif
	
	F>>n;
	long long value = 0;
	for (int i=1;i<=n;++i)
	{
		F>>a[i];
		value ^= a[i];
	}
	long long ans = value;
	add(0,1LL<<40,0);
	for (int i=n;i>=1;--i)
	{
		value ^= a[i];
		a[i] ^= a[i+1];
		add(a[i],1LL<<40,0);
		ans = max(ans,ask(value,1LL<<40,0));
	}
	G<<ans<<'\n';
}
