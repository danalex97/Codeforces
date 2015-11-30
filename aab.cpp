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

const int K = 510;
const int N = 100010; 
const int P = 22; 
const int B = 11; 
const int M2 = 666013;
const int M = 1000000007;

int n,m,s,t,x[3][N];
lng dst[2][N];
int ways[2][N];
int ways2[2][N];
vector<int> v[2][N];

void build(int s,int t,int k)
{
	ways[k][s] = 1;
	ways2[k][s] = 1;
	memset(dst[k],-1,sizeof(dst[k]));
	dst[k][s] = 0;
	
	priority_queue<pair<lng,int> > pq;
	pq.push( make_pair(0,s) );
	
	while ( !pq.empty() )
	{
		int x = pq.top().second;
		lng cst = -pq.top().first;
		pq.pop();
		
		if ( cst > dst[k][x] )
			continue;
		for (int i=0;i<int(v[k][x].size());++i)
		{
			int idx = v[k][x][i];
			int y = ::x[1-k][idx];
			int c2 = ::x[2][idx];
			//cerr<<x<<' '<<dst[k][y]<<' '<<cst+c2<<'\n';
			
			if ( dst[k][y] == -1 || cst + c2 < dst[k][y] )
			{
				dst[k][y] = cst + c2;
				ways[k][y] = ways[k][x]; 
				ways2[k][y] = ways2[k][x]; 
				pq.push( make_pair(-cst-c2,y) );
				//cerr<<"h: "<<cst+c2<<'\n';
			}
			else
				if ( cst + c2 == dst[k][y] )
				{
					//cerr<<"here\n";
					ways[k][y] += ways[k][x];
					ways2[k][y] += ways2[k][x];
					ways[k][y] %= M;
					ways2[k][y] %= M2;
				}
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif
	
	F>>n>>m>>s>>t;
	for (int i=1;i<=m;++i)
	{
		for (int j=0;j<3;++j) F>>x[j][i];
		v[0][x[0][i]].push_back(i);
		v[1][x[1][i]].push_back(i);
	}
	build(s,t,0);
	build(t,s,1);
	//cerr<<dst[0][t]<<'\n';
	//cerr<<dst[1][s]<<'\n';
	//for (int i=1;i<=n;++i) cerr<<ways[0][i]<<' ';cerr<<'\n';
	for (int i=1;i<=m;++i)
	{
		int x = ::x[0][i];
		int y = ::x[1][i];
		int c = ::x[2][i];
		
		if ( dst[0][x] == -1 || dst[1][y] == -1 ) 
			G<<"NO\n"; else
		
		if ( dst[0][t] == dst[0][x] + dst[1][y] + c && ( 1LL * ways[0][x] * ways[1][y] ) % M == ways[0][t] && ( 1LL * ways2[0][x] * ways2[1][y] ) % M2 == ways2[0][t] )
			G<<"YES\n";
		else
			if ( dst[0][t] > dst[0][x] + dst[1][y] + 1 ) 
			{
				G<<"CAN ";
				G<<( dst[0][x] + dst[1][y] + c + 1 ) - dst[0][t] <<' ';
				G<<'\n';
			}
			else
				G<<"NO\n";
	}
}
