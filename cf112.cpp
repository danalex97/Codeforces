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
const int M = 1<<24;

int n,m,root,br,x[N],lvl[N],wh[N],y[N],deg[N];
vector<int> v[N];
vector<int> k[N];

void build(int x)
{
	if ( x != root )
	{
		k[br].push_back(0);
		wh[x] = br;
	}
	for (int i=0;i<int(v[x].size());++i)
	{
		int y = v[x][i];
		if ( x == root )
		{
			++br;
			k[br].push_back(0);
		} 
		if ( lvl[y] == 0 )
		{
			lvl[y] = lvl[x]+1;
			build(y);
		} 
	}
}

void add(int p,int x,int v)
{
	--x;
	int sz = int(k[p].size())-1;
	if ( x > 0 ) 
		for (int i=x;i<=sz;i+=i&-i)
			k[p][i] += v;
}

int ask(int p,int x)
{
	--x;
	int ans = 0;
	for (int i=x;i>0;i-=i&-i)
		ans += k[p][i];
	return ans;
}

int main() 
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif

	F>>n;
	for (int i=1;i<n;++i)
	{
		F>>x[i]>>y[i];
		v[x[i]].push_back(y[i]);
		v[y[i]].push_back(x[i]);
		deg[x[i]]++;
		deg[y[i]]++;
	}
	for (int i=1;i<=n;++i)
		if ( deg[i] > deg[root] )
			root = i;
	lvl[root] = 1;
	build(root);
	F>>m;
	//cerr<<m<<'\n';
	for (int i=1,t;i<=m;++i)
	{
		F>>t;
		//cerr<<t<<' ';
		if ( t == 1 || t == 2 )
		{
			int idx = 0;
			F>>idx;
			int x = ::x[idx];
			int y = ::y[idx];
			x = lvl[y] > lvl[x] ? y : x;
			
			if ( t == 1 )
			{
				if ( ask(wh[x],lvl[x])-ask(wh[x],lvl[x]-1) == 1 )
					add(wh[x],lvl[x],-1);
			}
			else
			{
				if ( ask(wh[x],lvl[x])-ask(wh[x],lvl[x]-1) == 0 )
					add(wh[x],lvl[x],1);
			}
		}
		else
		{
			int x = 0 , y = 0;
			F>>x>>y;
			//cerr<<x<<' '<<y<<'\n';
			if ( wh[x] == wh[y] ) 
			{
				if ( ask(wh[x],max(lvl[x],lvl[y])) - ask(wh[x],min(lvl[x],lvl[y])) == 0 )
					G<<abs(lvl[x]-lvl[y])<<'\n';
				else
					G<<"-1\n";
			}
			else
			{
				if ( ask(wh[x],lvl[x]) == 0 && ask(wh[y],lvl[y]) == 0 )
					G<<(lvl[x]+lvl[y]-2)<<'\n';
				else
					G<<"-1\n";
			}
		}
	}
}
