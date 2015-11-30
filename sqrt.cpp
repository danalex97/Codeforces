#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
 
ifstream F("arbint.in");
ofstream G("arbint.out");
 
const int N = 100010;
 
int n,m;

struct node {
	vector<int> a;
	int mx;
	
	node(int x)
	{
		a.push_back(x);
		mx = x;
	}
	void push(int x)
	{
		a.push_back(x);
		mx = max(x,mx);
	}
	void update(int p,int x)
	{
		a[p] = x;
		mx = 0;
		for (int i=0;i<int(a.size());++i)
			mx = max(mx,a[i]);
	}
	int query(int p1,int p2)
	{
		if ( p1 == p2 || p1 >= int(a.size()) || p2 <= 0 )
			return 0;
		if ( p1 == 0 && p2 == int(a.size()) ) 
			return mx;
		
		int _mx = 0;
		for (int i=p1;i<p2;++i)
			_mx = max(_mx,a[i]);
		return _mx;
	}
	void print()
	{
		for (int i=0;i<int(a.size());++i)
			cerr<<a[i]<<' ';
	}
};

struct ksegment {
	int k;
	vector<node> v;
	
	ksegment()
	{
	}
	ksegment(int _k)
	{
		k = _k;
	}
	void push(int x)
	{
		if ( v.empty() ) 
			v.push_back( node(x) );
		else
			if ( int(v.back().a.size()) == k )
				v.push_back( node(x) );
			else
				v.back().push(x);
	}
	void update(int p,int x)
	{
		int wh = (p-1)/k;   
		p -= wh*k+1; 
		v[wh].update(p,x);
	}
	int query(int l,int r)
	{
		int mx = 0;
		for (int i=0;i<int(v.size());++i)
		{
			int ll = max(l-i*k-1,0);
			int rr = min(k,r-i*k);
			mx = max(mx,v[i].query( ll,rr ));
		}
		return mx;
	}
	void print()
	{
		for (int i=0;i<int(v.size());++i)
		{
			cerr<<"[";
			v[i].print();
			cerr<<"] ";
		}
		cerr<<'\n';
	}
};
 
int main()
{
    F>>n>>m;
	ksegment ks = ksegment(sqrt(n));
	for (int i=1,x;i<=n;++i)
	{
		F>>x;
		ks.push(x);
	}
	for (int i=1,t,x,y;i<=m;++i)
	{
		//ks.print();
		F>>t;
		++t;
		
		if ( t == 1 ) 
		{
			F>>x>>y;
			G<<ks.query(x,y)<<'\n';
		}
		else 
		{
			F>>x>>y;
			ks.update(x,y);
		}
	}
}
