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

const int M = 1000000007;
const int N = 100010;

struct node 
{
	int x[26];
	node() 
	{
		memset(x,0,sizeof(x));
	}
	node operator + (node &u) 
	{
		node out;
		for (int i=0;i<26;++i)
			out.x[i] += x[i] + u.x[i];
		return out;
	}
};

node aint[N*4];
int lazy[N*4];
char a[N];
int n,q;

void push_down(int n,int l,int r)
{
	if ( !lazy[n] ) return;
	
	aint[n] = node();
	
	aint[n].x[lazy[n]-1] = r-l+1;
	if ( l != r )
	{
		lazy[n*2] = lazy[n];
		lazy[n*2+1] = lazy[n];
	}
	lazy[n] = 0;
}

void build(int n,int l,int r)
{
	if ( l == r )
	{
		aint[n].x[a[l]-int('a')]++;
		return;
	}
	
	int m = (l + r) / 2;
	build(n*2,l,m);
	build(n*2+1,m+1,r);
	
	aint[n] = aint[n*2] + aint[n*2+1];
}

void upd(int n,int l,int r,int x,int y,int v)
{
	push_down(n,l,r);
	if ( l > y || r < x )
		return;
	if ( x <= l && r <= y )
	{
		lazy[n] = v;
		push_down(n,l,r);
		return;
	}
	
	int m = (l + r) / 2;
	upd(n*2,l,m,x,y,v);
	upd(n*2+1,m+1,r,x,y,v);
	
	aint[n] = aint[n*2] + aint[n*2+1];
}

node query(int n,int l,int r,int x,int y)
{
	push_down(n,l,r);
	if ( l > y || r < x ) 
		return node();
	if ( x <= l && r <= y )
		return aint[n];
	
	int m = (l + r) / 2;
	node q1 = query(n*2,l,m,x,y);
	node q2 = query(n*2+1,m+1,r,x,y);
	node q = q1 + q2;

	return q;
}

int main()
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif
	
	F>>n>>q;
	F>>(a+1);
	
	build(1,1,n);
	cerr<<(a+1)<<'\n';
	
	while ( q-- )
	{
		//cerr<<"here";
		int l = 0 , r = 0 , k = 0;
		F>>l>>r>>k;
		node qu = query(1,1,n,l,r);
		if ( k )
		{
			for (int i=0;i<26;++i)
				if ( qu.x[i] )
				{
					upd(1,1,n,l,l+qu.x[i]-1,i+1);
					l += qu.x[i];
				}
		}
		else
		{
			for (int i=25;i>=0;--i)
				if ( qu.x[i] )
				{
					upd(1,1,n,l,l+qu.x[i]-1,i+1);
					l += qu.x[i];
				}
		}
		
		//string ans = "";
		//for (int i=1;i<=n;++i)
		//{
		//	node qu = query(1,1,n,i,i);
		//	for (int i=0;i<26;++i)
		//		if ( qu.x[i] )
		//		{
		//			ans += char(i)+'a';
		//		}
		//}
		//cerr<<ans<<'\n';
	}
	
	string ans = "";
	for (int i=1;i<=n;++i)
	{
		node qu = query(1,1,n,i,i);
		for (int i=0;i<26;++i)
			if ( qu.x[i] )
			{
				ans += char(i)+'a';
				//cerr<<"here";
			}
	}
	G<<ans<<'\n';
}
