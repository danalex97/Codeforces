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

const int N = 100010;

set< pair<int,int> > t1,t2;
int n,m,mk[N],mk2[N];
vector<int> v[N];

void go(int x)
{
	mk[x] = 1;
	for (int i=0;i<int(v[x].size());++i)
	{
		int y = v[x][i];
		if ( mk[y] == 0 )
		{
			t1.insert(make_pair(x,y));
			go(y);
		} 
	}
}

// if the graph isn't conex without edges in first dfs , then we have a bridge 

void go2(int x)
{
	mk2[x] = 1;
	for (int i=0;i<int(v[x].size());++i)
	{
		int y = v[x][i];
		if ( t1.find(make_pair(x,y)) == t1.end() && t2.find(make_pair(y,x)) == t2.end() )
		{
			t2.insert(make_pair(x,y));
			if ( mk2[y] == 0 )
				go2(y);
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif

	F>>n>>m;
	for (int i=1,x,y;i<=m;++i)
	{
		F>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	go(1);
	go2(1);
	for (int i=1;i<=n;++i)
		if ( mk2[i] == 0 )
		{
			G<<"0\n";
			return 0;
		}
	for (int x=1;x<=n;++x)
		for (int i=0;i<int(v[x].size());++i)
		{
			int y = v[x][i];
			if ( t1.find(make_pair(x,y)) != t1.end() || t2.find(make_pair(y,x)) != t2.end() )
				G<<x<<' '<<y<<'\n';
		}
}
