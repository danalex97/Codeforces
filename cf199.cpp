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

const int K = 310;
const int N = 100010; 
const int P = 22; 
const int B = 11; 
const int M = 1000000007;
const int M2 = 1000000009;

int n,k=300,m,p;
vector<int> v[N],now;
int ft[N],lvl[N],rmq[P][N<<2],dst[N],mk[N],lg[N<<2];

void dfs(int x,int dd)
{
	ft[x] = ++p;
	rmq[0][p] = lvl[x];
	for (int i=0;i<int(v[x].size());++i)
	{
		int y = v[x][i];
		if ( y == dd ) continue;
		
		lvl[y] = lvl[x] + 1;
		dfs(y,x);
		rmq[0][++p] = lvl[x];
	}
}

void build()
{
	for (int i=1,s=0;i<=p;++i)
	{
		if ( i == (1<<s) ) ++s;
		lg[i] = s-1;
	}
	for (int s=1;(1<<s)<=p;++s)
		for (int i=1;i<=p-(1<<s)+1;++i)
			rmq[s][i] = min(rmq[s-1][i],rmq[s-1][i+(1<<(s-1))]);
}

int lca(int x,int y)
{
	//cerr<<x<<' '<<y<<' '<<ft[x]<<' '<<ft[y]<<' ';
	x = ft[x];
	y = ft[y];
	if ( y < x ) swap(x,y);
	
	int s = lg[y-x+1];
	//cerr<<s<<'\n';
	return min(rmq[s][x],rmq[s][y-(1<<s)+1]);
}

int dist(int x,int y)
{
	int z = lca(x,y);
	//cerr<<x<<' '<<y<<' '<<z<<'\n';
	return lvl[x] - z + lvl[y] - z;
}

void compute(int x,int dd)
{
	if ( mk[x] ) 
		dst[x] = 0; 
	else
		dst[x] = 1<<30;
	//cerr<<x<<' '<<dst[x]<<'\n';
	
	for (int i=0;i<int(v[x].size());++i)
	{
		int y = v[x][i];
		if ( y == dd ) continue;
		
		compute(y,x);
		dst[x] = min(dst[x],dst[y]+1);
	}
}

void compute2(int x,int dd)
{
	if ( dd )  
		dst[x] = min(dst[dd]+1,dst[x]);
	for (int i=0;i<int(v[x].size());++i)
	{
		int y = v[x][i];
		if ( y == dd ) continue;
		
		compute2(y,x);
	}
}

int main()
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif
	
   F>>n>>m;
   for (int i=1,x,y;i<n;++i)
   {
	   F>>x>>y;
	   v[x].push_back(y);
	   v[y].push_back(x);
   }
   dfs(1,0);
   build();
   
   //for (int l=0;l<=5;++l)
   //{
	//   for (int i=1;i<=p;++i) 
	//		cerr<<rmq[l][i]<<' ';
	//	cerr<<'\n';
   //}
   //for (int i=1;i<=n;++i) cerr<<ft[i]<<' ';cerr<<'\n';
   
   mk[1] = 1;
   compute(1,0);
   compute2(1,0);
   
   for (int i=1,t,x;i<=m;++i)
   {
	   F>>t>>x;
	   //cerr<<t<<' '<<x<<'\n';
	   //for (int j=1;j<=n;++j) cerr<<dst[j]<<' '; cerr<<'\n';
	   if ( t == 1 ) 
	   {
		   now.push_back(x);
		   //mk[x] = 1;
		   //compute(1,0);
		  // compute2(1,0);
		   if ( int(now.size()) == k )
		   {
			   for (int j=0;j<k;++j)
					mk[now[j]] = 1;
			   now.clear();
			   compute(1,0);
			   compute2(1,0);
		   }
	   } 
	   else
	   {
		   int ans = dst[x];
		   for (int j=0;j<int(now.size());++j)
				ans = min(ans,dist(x,now[j]));
		   G<<ans<<'\n';
	   }
   }
}
