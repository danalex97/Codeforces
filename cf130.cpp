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

int n,m,k=20,anc[K][N],ft[N],lt[N],co,lvl[N];
vector<int> v[N];
vector<int> nds[N];

void dfs(int x,int _lvl)
{
	ft[x] = ++co;
	nds[_lvl].push_back(co);
	lvl[x] = _lvl;
	for (int i=0;i<int(v[x].size());++i)
	{
		int y = v[x][i];
		dfs(y,_lvl+1);
	}
	lt[x] = co;
}

int main() 
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif

	F>>n;
	for (int i=1,x,y;i<=n;++i)
	{
		y = i;
		F>>x;
		v[x].push_back(y);
		anc[0][y] = x;
	}
	dfs(0,0);
	for (int i=1;i<=k;++i)
		for (int j=1;j<=n;++j)
			anc[i][j] = anc[i-1][ anc[i-1][j] ];
	
	F>>m;
	for (int j=1,x,p;j<=m;++j)
	{
		F>>x>>p;
		int y = x;
		for (int i=k;i>=0;--i)
			if ( (1<<i) <= p )
			{
				p -= (1<<i);
				y = anc[i][y];
			}
		//cerr<<y<<' '<<ft[y]<<' '<<lt[y]<<'|';
		if ( y == 0 )
			G<<"0\n";
		else
		{
			//cerr<<"here\n";
			vector<int> &now = nds[lvl[x]];
			//for (int i=0;i<int(now.size());++i) cerr<<now[i]<<' '; cerr<<'|';
			//cerr<<*lower_bound(now.begin(),now.end(),ft[y])<<' '<<*lower_bound(now.begin(),now.end(),lt[y]+1)<<'|';
			G<<lower_bound(now.begin(),now.end(),lt[y]+1)-lower_bound(now.begin(),now.end(),ft[y])-1<<'\n';
		}
	}
}
