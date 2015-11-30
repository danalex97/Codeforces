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
const int N = 200010; 
const int P = 35; 
const int B = 11; 
const int M2 = 7340033;
const int M = 1000000007;

int n,m,q,dd[N],mk[N],h[N],up[N];
vector<int> v[N];
set<int> s[N],t[N];

int merge(int a,int b) // merge a and b in the bigest set
// if we find one node's pair , then we eliminate it
{
	if ( a == b ) return a;
	if ( t[a].size()+s[a].size() > t[b].size()+s[b].size() ) swap(a,b);
	
	while ( s[a].size() )
	{
		int k = *s[a].begin();
		s[a].erase(k);
		if ( t[b].find(k) != t[b].end() )
			t[b].erase(k);
		else
			s[b].insert(k);
	} 
	while ( t[a].size() )
	{
		int k = *t[a].begin();
		t[a].erase(k);
		if ( s[b].find(k) != s[b].end() )
			s[b].erase(k);
		else
			t[b].insert(k);
	}
	return b;
}

void dfs(int x,int dd)
{
	mk[x] = 1;
	h[x] = h[dd] + 1;
	up[x] = h[x];
	
	int flag = 0;
	for (int i=0;i<int(v[x].size());++i)
	{
		int y = v[x][i];
		if ( y != dd || flag )
		{
			if ( !mk[y] ) 
				dfs(y,x);
			up[x] = min( up[x],up[y] );
			::dd[x] = merge( ::dd[x],::dd[y] );
		}
		else
			flag = 1;
	}
	if ( up[x] == h[x] ) // if we are on tree
		if ( s[::dd[x]].size() && t[::dd[x]].size() )
			throw 0;
}

int main()
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif
	
	F>>n>>m>>q;
	for (int i=1,x,y;i<=m;++i)
	{
		F>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	for (int i=1;i<=n;++i)
		dd[i] = i;
	for (int i=1,x,y;i<=q;++i)
	{
		F>>x>>y;
		s[x].insert(i);
		t[y].insert(i);
	}
	try 
	{ 
		for (int i=1;i<=n;++i)
			if ( mk[i] == 0 )
				dfs(i,0);
		for (int i=1;i<=n;++i)  /// on the dfs we verify only the 
		// querys merged in the bigest chain because the bigest chain
		// can throw some querys in a little chain 
			if ( up[i] == h[i] ) 
				if ( s[dd[i]].size() || t[dd[i]].size() )
					throw 0;
	}
	catch (int x)
	{
		G<<"No\n";
		return 0;
	}
	G<<"Yes\n";
}
