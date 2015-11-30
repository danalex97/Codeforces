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

int n,m,s[N];
vector< pair<int,int> > v[N];

void df(int x,int w)
{  
	s[x] = w;
	for (int i=0;i<int(v[x].size());++i)
	{
		int y = v[x][i].first;
		int z = v[x][i].second;
		if ( s[y] != 2 && ( s[x] ^ s[y] ) != z )
			throw(0);
		if ( s[y] == 2 )
			df(y,w^z);
	}
}

int main() 
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif

	F>>n>>m;
	for (int i=1,x,y,z;i<=m;++i)
	{
		F>>x>>y>>z;
		z = 1-z;
		v[x].push_back( make_pair(y,z) );
		v[y].push_back( make_pair(x,z) );
	}
	for (int i=1;i<=n;++i) 
		s[i] = 2;
	for (int i=1;i<=n;++i) 
		if ( s[i] == 2 )
		{
			try 
			{
				df(i,0);
			}
			catch(int x)
			{
				G<<"Impossible\n";
				return 0;
			}
		}
	int cc = 0;
	for (int i=1;i<=n;++i) 
		cc += s[i];
	G<<cc<<'\n';
	for (int i=1;i<=n;++i) 
		if ( s[i] )
			G<<i<<' ';
	G<<'\n';
}
