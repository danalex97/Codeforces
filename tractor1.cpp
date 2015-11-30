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
const int N = 100010; 
const int P = 35; 
const int B = 11; 
const int M2 = 7340033;
const int M = 1000000007;
 
// global
int n,m;
vector<int> v[N];

// cycle
vector<int> cyc;
int dd[N],mk[N];

void find_cycle(int x)
{
	//cerr<<x<<'\n';
	mk[x] = 1;
	for (int i=0;i<int(v[x].size());++i)
	{
		int y = v[x][i];
		if ( mk[y] == 1 && dd[x] != y )
		{
			throw make_pair(x,y);
		}
		if ( mk[y] == 0 )
		{
			dd[y] = x;
			find_cycle(y);
		}
	}
}

// building chains

int weight[N],pl[N],my[N],tree[N],act_tree;
vector< vector<int> > chains;

int find_chains(int x) // returns chain index
{
	//cerr<<x<<'\n';
	mk[x] = 1;
	tree[x] = act_tree;
	weight[x] = 1;
	int flag = 1;
	int idx = -1;
	for (int i=0;i<int(v[x].size());++i)
	{
		int y = v[x][i];
		if ( mk[y] == 0 )
		{
			flag = 0;
			dd[y] = x;
			int now = find_chains(y);
			weight[x] += weight[y];
			
			if ( idx == -1 ) 
				idx = now;
			if ( weight[chains[now].back()] > weight[chains[idx].back()] )
				idx = now;
		}
	}
	
	if ( flag ) 
	{
		vector<int> nw;
		nw.push_back(x);
		chains.push_back( nw );
		return int(chains.size())-1;
	}
	
	chains[idx].push_back(x);
	return idx;
}

/// seg tree !

struct seg {
	vector<int> a,b;
	seg()
	{
	}
	seg(int n)
	{
		a.resize((n+1)*4);
		b.resize((n+1)*4);
	}
	void push(int n,int l,int r)
	{
		if ( !b[n] ) return;
		
		b[n] = 0;
		a[n] = (r-l+1) - a[n];
		if ( l == r )
			return;
		b[n*2] ^= 1;
		b[n*2+1] ^= 1;
	}
	void build(int n,int l,int r)
	{
		b[n] = 0;
		if ( l == r )
		{
			a[n] = 1;
			return;
		}
		
		int m = (l + r) / 2;
		build(n*2,l,m);
		build(n*2+1,m+1,r);
		
		a[n] = a[n*2] + a[n*2+1];
	}
	void update(int n,int l,int r,int il,int ir)
	{
		push(n,l,r);
		if ( l > ir || r < il ) 
			return;
		if ( il <= l && r <= ir )
		{
			b[n] = 1;
			push(n,l,r);
			return;
		}
		
		int m = (l + r) / 2;
		update(n*2,l,m,il,ir); 
		update(n*2+1,m+1,r,il,ir);
		
		a[n] = a[n*2] + a[n*2+1]; 
	}
	int ask(int n,int l,int r,int il,int ir)
	{
		push(n,l,r);
		if ( l > ir || r < il ) 
			return 0;
		if ( il <= l && r <= ir )
			return a[n];
		
		int m = (l + r) / 2;
		int ans = ask(n*2,l,m,il,ir); 
		ans += ask(n*2+1,m+1,r,il,ir);
		
		return ans;
	}
};

///

seg s[N],c;
int ord[N],ans;

void solve(int chain,int l,int r)
{
	int n = chains[chain].size();
	
	ans -= s[chain].ask(1,1,n,l,r);
	s[chain].update(1,1,n,l,r);
	ans += s[chain].ask(1,1,n,l,r);
}

void solve2(int l,int r)
{
	int n = cyc.size();
	
	ans -= c.ask(1,1,n,l,r);
	//cerr<<ans<<' ';
	c.update(1,1,n,l,r);
	ans += c.ask(1,1,n,l,r);
	//cerr<<ans<<'\n';
}

int go(int x,int chain)
{
	//cerr<<chain<<'\n';
	while ( my[x] != chain )
	{
		solve(my[x],pl[x],chains[my[x]].size());
		x = chains[my[x]].back();
		//cerr<<x<<' '<<dd[x]<<'\n';
		if ( dd[x] ) x = dd[x];
	}
	return x;
}

int cmp(int x,int y,int flag)
{
	int l1 = ord[y]-ord[x];
	int l2 = ord[x] + int(cyc.size()) - ord[y];
	//cerr<<l1<<' '<<l2<<'\n';
	if ( l1 != l2 ) return l1 < l2;
	
	//cerr<<"here\n";
	
	//cerr<<x<<' '<<y<<'\n';
	if ( flag ) swap(x,y);
	int i1 = ord[x] == int(cyc.size()) ? 1 : ord[x]+1; // dr
	int i2 = ord[x] == 1 ? cyc.size() : ord[x]-1; // st
	if ( flag ) swap(i1,i2);
	
	return cyc[i1-1] < cyc[i2-1];
}

int main()
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif
	
	F>>n>>m;
	for (int i=1,x,y;i<=n;++i)
	{
		F>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	
	try 
	{
		find_cycle(1);
	}
	catch (pair<int,int> p) 
	{
		int x = p.first;
		int y = p.second;
		cyc.push_back(y);
		while ( x != y )
		{
			cyc.push_back(x);
			x = dd[x];
		}
	}
	for (int i=0;i<int(cyc.size());++i)
		ord[cyc[i]] = i+1;
	//for (int i=0;i<int(cyc.size());++i) cerr<<cyc[i]<<' '; cerr<<'\n';
	
	memset(mk,0,sizeof(mk));
	memset(dd,0,sizeof(dd));
	for (int i=0;i<int(cyc.size());++i) 
		mk[cyc[i]] = 1;
	for (int i=0;i<int(cyc.size());++i) 
	{
		act_tree = i;
		find_chains(cyc[i]);
	}
	for (int i=0;i<int(chains.size());++i)
		for (int j=0;j<int(chains[i].size());++j)
		{
			int x = chains[i][j];
			my[x] = i;
			pl[x] = j+1;
		}
	//for (int i=0;i<int(chains.size());++i,cerr<<'\n') { cerr<<i<<':'; for (int j=0;j<int(chains[i].size());++j) cerr<<chains[i][j]<<' '; }

	for (int i=0;i<int(chains.size());++i)
	{
		s[i] = seg(chains[i].size());
		s[i].build(1,1,chains[i].size());
	}
	c = seg(cyc.size());
	c.build(1,1,cyc.size());

	ans = n;
	//for (int i=1;i<=n;++i) cerr<<dd[i]<<' '; cerr<<'\n';
	//for (int i=1;i<=n;++i) cerr<<my[i]<<' '; cerr<<'\n';
	//for (int i=1;i<=n;++i) cerr<<pl[i]<<' '; cerr<<'\n';
	for (int q=1,x,y;q<=m;++q)
	{
		F>>x>>y;
		//cerr<<x<<' '<<y<<'\n';
		
		vector<int> ax,ay; 
		for (int i=x;;i=dd[i])
		{
			i = chains[my[i]].back();
			ax.push_back(my[i]);
			if ( !dd[i] ) break;
		}
		for (int i=y;;i=dd[i])
		{
			i = chains[my[i]].back();
			//cerr<<i<<'\n';
			ay.push_back(my[i]);
			if ( !dd[i] ) break;
		}
		
		reverse(ax.begin(),ax.end());
		reverse(ay.begin(),ay.end());
		
		ax.resize(ax.size()+1);
		ax[ax.size()-1] = -1;
		ay.resize(ay.size()+1);
		ay[ay.size()-1] = -2;
		
		int mx = max(ax.size(),ay.size());
		ax.resize(mx);
		ay.resize(mx);
		
		//for (int i=0;i<int(ax.size());++i) cerr<<ax[i]<<' '; cerr<<'\n';
		//for (int i=0;i<int(ay.size());++i) cerr<<ay[i]<<' '; cerr<<'\n';
		
		if ( tree[x] == tree[y] )
		{
			//cerr<<x<<' '<<y<<'\n';
			int idx = 0;
			while ( ax[idx+1] == ay[idx+1] ) 
				++idx;
			int chain = ax[idx]; 
			
			//cerr<<chain<<'\n';
			x = go(x,chain);
			y = go(y,chain);
			
			int p1 = pl[x];
			int p2 = pl[y];
			if ( p1 > p2 ) swap(p1,p2);
			if ( p1 != p2 ) solve(my[x],p1,p2-1);
		}
		else
		{
			x = go(x,ax[0]);
			y = go(y,ay[0]);
			
			int nx = chains[my[x]].back();
			int ny = chains[my[y]].back();
			
			if ( x != nx ) solve(my[x],pl[x],pl[nx]-1);
			if ( y != ny ) solve(my[y],pl[y],pl[ny]-1);
			
			x = nx;
			y = ny;
			
			// on cycle edges are defined like : x -> x+1
			
			int flag = 0;
			if ( ord[x] > ord[y] ) 
			{
				swap(x,y);
				flag = 1;
			}
			
			//cerr<<ord[x]<<' '<<ord[y]<<'\n';
			
			if ( cmp(x,y,flag) )
			{
				solve2(ord[x],ord[y]-1);
			}   
			else
			{
				//cerr<<"here\n";
				if ( ord[x] > 1 ) solve2(1,ord[x]-1);
				solve2(ord[y],cyc.size());
			}
		}
		
		G<<ans+(c.a[1]==0)<<'\n';
		//for (int i=1;i<=n;++i) cerr<<s[my[i]].ask(1,1,chains[my[i]].size(),pl[i],pl[i])<<' ';cerr<<'\n';
		//for (int i=0;i<int(chains.size());++i,cerr<<'\n') 
		//{ 
		//	cerr<<i<<':'; 
		//	for (int j=0;j<int(chains[i].size());++j) 
		//		cerr<<'('<<chains[i][j]<<','<<s[i].ask(1,1,chains[i].size(),j+1,j+1)<<") "; 
		//}
	}
}
