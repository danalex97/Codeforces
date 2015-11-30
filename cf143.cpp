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

const int K = 20;
const int N = 100010; 
const int P = 100; 
const int B = 11; 
const int M = 1000000007;

int n,m,q,wh[N],tp[N],mk[N],cyc,lvl[N],cnt[N],k=18,dd[K][N],p2[N];
vector<int> v[N],stk;
set<int> w[N];

void build(int x,int dd)
{
	//cerr<<x<<' '<<stk.size()<<'\n';
	mk[x] = 1;
	for (int i=0;i<int(v[x].size());++i)
	{
		int y = v[x][i];
		if ( mk[y] == 1 && y != dd )
		{
			tp[++cyc] = 1;
			int pl = stk.size()-1;
			while ( stk[pl] != y )
			{
				wh[stk[pl]] = cyc;
				//cerr<<stk.back()<<' ';
				pl--;
			}
			wh[x] = cyc;
			wh[y] = cyc;
			//cerr<<"cyc "<<y<<' '<<stk.size()<<'\n';
		}
	}
	bool flag = 0;
	if ( !wh[x] ) 
	{
		stk.push_back(x);
		flag = 1;
	}
	for (int i=0;i<int(v[x].size());++i)
	{
		int y = v[x][i];
		if ( mk[y] == 0 )
			build(y,x);
	}
	if ( flag )
		stk.pop_back();
	//if ( x == 10 ) cerr<<"x "<<wh[x]<<'\n'; 
	if ( wh[x] == 0 ) 
	{
		wh[x] = ++cyc;
		tp[cyc] = 0;
	}
}

void dfs(int x,int d)
{
	cnt[x] = cnt[d] + tp[x];
	for (set<int>::iterator y=w[x].begin();y!=w[x].end();++y)
		if ( *y != d )
		{
			lvl[*y] = lvl[x]+1;
			dd[0][*y] = x;
			dfs(*y,x);
		}
}

int up(int x,int y)
{
	for (int i=k;i>=0;--i)
		if ( y >= (1<<i) )
		{
			y -= 1<<i;
			x = dd[i][x]; 
		}
	return x;
}

bool good(int l,int x,int y)
{
	int lx = lvl[x];
	int ly = lvl[y];
	//if ( x == 3 && y == 4 && l == 3 ) cerr<<up(x,lx-l)<<' '<<' '<<up(y,ly-l)<<'\n';
	return up(x,lx-l) == up(y,ly-l);
}

int bs(int l,int r,int x,int y)
{
	if ( r-l < 2 )
	{
		//cerr<<r<<'\n';
		if ( good(r,x,y) )
			return r;
		return l;
	}
	
	int m = (l+r) / 2;
	//cerr<<m<<'\n';
	
	if ( good(m,x,y) )
		return bs(m,r,x,y);
	return bs(l,m-1,x,y);
}

int lca(int x,int y)
{
	return up(x,lvl[x]-bs(1,min(lvl[x],lvl[y]),x,y));
}

int main() 
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif
	
	F>>n>>m;
	stk.push_back(0);
	for (int i=1,x,y;i<=m;++i)
	{
		F>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	build(1,0);
	//cerr<<"here\n";
	//for (int i=1;i<=n;++i) cerr<<wh[i]<<' ';cerr<<'\n';
	//for (int i=1;i<=cyc;++i) cerr<<tp[i]<<' ';cerr<<'\n';
	
	for (int x=1;x<=n;++x)
		for (int i=0;i<int(v[x].size());++i)
		{
			int y = v[x][i];
			if ( wh[x] != wh[y] )
			{ 
				int _x = wh[x];
				int _y = wh[y];
				w[_x].insert(_y);
				w[_y].insert(_x);
			}
		}

	lvl[1] = 1;
	dfs(1,0);
	//for (int i=1;i<=cyc;++i) cerr<<lvl[i]<<' ';cerr<<'\n';
	//for (int i=1;i<=cyc;++i) cerr<<dd[0][i]<<' ';cerr<<'\n';
	
	for (int i=1;i<=k;++i)
		for (int j=1;j<=n;++j)
			dd[i][j] = dd[i-1][dd[i-1][j]];

	p2[0] = 1;
	for (int i=1;i<=n;++i)
		p2[i] = ( 2 * p2[i-1] ) % M;
	
	F>>q;
	for (int i=1,x,y,z;i<=q;++i)
	{
		F>>x>>y;
		x = wh[x];
		y = wh[y];
		
		z = lca(x,y);
		//cerr<<x<<' '<<y<<' '<<z<<' ';
		int ans = cnt[x]+cnt[y]-2*cnt[z]+tp[z];  
		G<<p2[ans]<<'\n';
	}
}
