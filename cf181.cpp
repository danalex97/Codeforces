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

const int K = 1010;
const int N = 10000010; 
const int P = 35; 
const int B = 11; 
const int M2 = 7340033;
const int M = 1000000007;

int n=N-10,m,p[N],co[N];
lng tot[N];

int good(lng x)
{
	for (int i=2;i<=n;++i)
		if ( p[i] == i )
		{
			lng y = x, sm = 0;
			while ( y )
			{
				y /= i;
				sm += y;
			}
			if ( sm < tot[i] )
				return 0;
		} 
	return 1;
}

lng bs(lng l,lng r)
{
	if ( r-l < 1 )
	{
		if ( good(l) )
			return l;
		return r;
	}
	
	lng m = (l + r) / 2;
	if ( good(m) )
		return bs(l,m); 
	return bs(m+1,r);
}

int main()
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif
	
	for (int i=2;i<=n;++i)
		if ( p[i] == 0 ) 
			for (int j=i;j<=n;j+=i)
				p[j] = i;
		
	F>>m;
	for (int i=1,x;i<=m;++i)
	{
		F>>x;
		tot[x]++;
	}
	
	for (int i=n;i>=2;--i)
		tot[i] += tot[i+1];
	for (int i=n;i>=2;--i)
		if ( p[i] != i )
		{
			tot[p[i]] += tot[i];
			tot[i/p[i]] += tot[i];
		}
	G<<bs(1LL,1LL<<50)<<'\n';
}



