#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <numeric>
#include <map>
#include <tr1/unordered_map>
#include <set>
#include <algorithm>
#include <vector>
#include <cstring>
#include <sstream>
#include <queue>
#include <bitset>
#include <cmath>
using namespace std;

ifstream F("eliminare.in");
ofstream G("eliminare.out");

typedef long long lng;

const int K = 5010;
const int N = 1000010; 
const int P = 100; 
const int B = 11; 
const int M = 1000000007;

int n,m,v[N];

struct seg {
	int a[N<<2],b[N<<2];
	seg()
	{
	}
	int best(int x,int y)
	{
		return v[x] == v[y] ? min(x,y) : v[x] > v[y] ? x : y;
	}
	void push(int n,int l,int r) 
	{
	}
	void build(int n,int l,int r)
	{
		if ( l == r )
		{
			a[n] = l;
			b[n] = 1;
			return;
		}
		
		int m = (l + r) / 2;
		build(n*2,l,m);
		build(n*2+1,m+1,r);
		
		a[n] = best(a[n*2],a[n*2+1]);
		b[n] = b[n*2]+b[n*2+1];
	}
	void update(int n,int l,int r,int p)
	{
		if ( l > p || r < p ) 
			return;
		if ( l == r )
		{
			a[n] = b[n] = 0;
			return;
		}
		
		int m = (l + r) / 2;
		update(n*2,l,m,p); 
		update(n*2+1,m+1,r,p);
		
		a[n] = best(a[n*2],a[n*2+1]);
		b[n] = b[n*2]+b[n*2+1];
	}
	int ask(int n,int l,int r,int il,int ir)
	{
		if ( l > ir || r < il ) 
			return 0;
		if ( il <= l && r <= ir )
			return a[n];
		
		int m = (l + r) / 2;
		int ans = ask(n*2,l,m,il,ir); 
		ans = best(ans,ask(n*2+1,m+1,r,il,ir));
		
		return ans;
	}
	int find(int n,int l,int r,int x)
	{
		if ( l == r ) 
			return l;
		int m = (l+r) / 2;
		if ( b[n*2] >= x ) 
			return find(n*2,l,m,x);
		else
			return find(n*2+1,m+1,r,x-b[n*2]);
	}
	void print(int n,int l,int r)
	{
		if ( l == r )
		{
			if ( b[n] )
				G<<v[l]<<'\n';
			return;
		}
		
		int m = (l + r) / 2;
		print(n*2,l,m);
		print(n*2+1,m+1,r);
	}
};

seg arb;

int main() 
{
	ios::sync_with_stdio(0);
	
	F>>n>>m;
	for (int i=1;i<=n;++i)
		F>>v[i];
	arb.build(1,1,n);
	
	for (int i=1,x,y;i<=m;++i)
	{
		F>>x>>y;
		x = arb.find(1,1,n,x);
		y = arb.find(1,1,n,y);
		int p = arb.ask(1,1,n,x,y);
		arb.update(1,1,n,p);
	}
	arb.print(1,1,n);
}

