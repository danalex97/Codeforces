#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 100010;

#define F cin
#define G cout

struct seg
{
	int l,r,t,i;
};

bool _t(seg a,seg b)
{
	return a.t < b.t;
}

bool _l(seg a,seg b)
{
	return a.l < b.l;
}

seg c[N],b[N];
int sol[N],ans[N];
int n,m;

int main()
{
	ios::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif
	
	F>>n>>m;
	for (int i=1;i<=n;++i)
	{
		F>>b[i].l>>b[i].r>>b[i].t;
		b[i].i = i;
	}
	for (int i=1;i<=m;++i)
	{
		F>>c[i].l>>c[i].r>>c[i].t;
		c[i].i = i;
		sol[i] = -1;
	}
	
	sort(b+1,b+n+1,_t);
	sort(c+1,c+m+1,_l);
	
	int sq = int(sqrt(n))+1;
	for (int i=n;i>=1;i-=sq)
	{
		vector<seg> v;
		int i2 = max(i-sq+1,1);
		for (int j=i2;j<=i;++j)
			v.push_back(b[j]);
		sort(v.begin(),v.end(),_l);
	
		int k = 0, mx = 0;
		for (int j=1;j<=m;++j)
		{
			while ( k < int(v.size()) && v[k].l <= c[j].l )
				mx = max(mx,v[k++].r);
			if ( mx >= c[j].r && b[i2].t >= c[j].t )
				sol[j] = i2;
		}
	}
	
	for (int i=1;i<=m;++i)
	{
		ans[c[i].i] = -1;
		for (int j=sol[i];sol[i]!=-1 && j<=sol[i]+sq && j<=n;++j)
			if ( b[j].l <= c[i].l && c[i].r <= b[j].r )
			{
				ans[c[i].i] = b[j].i;
				break;
			}
		int l = lower_bound(b+1,b+n+1,c[i],_t)-b;
		for (int j=l;j<=l+sq && j<=n;++j)
			if ( b[j].l <= c[i].l && c[i].r <= b[j].r )
			{
				ans[c[i].i] = b[j].i;
				break;
			}
	}
	
	for (int i=1;i<=m;++i)
		G<<ans[i]<<' ';
	G<<'\n';
}
