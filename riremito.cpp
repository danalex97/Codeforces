#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

ifstream F("riremito.in");
ofstream G("riremito.out");

const int N = 100010;

int n,k;
long long a[N],b[N],ln;
vector< pair<int,int> > v[N];

void dfs(int x,int dd,int ee)
{ 
	int leaf = 1;
	long long sm = 0;
	for (int i=0;i<int(v[x].size());++i)
	{
		int y = v[x][i].first;
		int cc = v[x][i].second;

		if ( y != dd )
		{
			leaf = 0;
			
			ln += cc;
			
			dfs(y,x,cc);
			sm += min(a[y],2*cc+b[y]);
			
			ln -= cc;
		}
	}
	
	if ( leaf )
	{
		a[x] = ln;
		b[x] = 0;
	}
	else
	{
		long long mx1 = 1LL<<60;
		long long mx2 = 0;
		for (int i=0;i<int(v[x].size());++i)
		{
			int y = v[x][i].first;
			int cc = v[x][i].second;

			if ( y != dd )
			{
				mx2 += min(a[y]+ln,2*cc+b[y]); // parcurg si fac riremito / parcurg si ma intorc
				mx1 = min(mx1,sm-min(a[y],2*cc+b[y])+a[y]); // merg in jos / merg in jos si ma intorc
			}
		}
		a[x] = mx1;
		b[x] = mx2;
	}
}

int main()
{
	F>>n;
	for (int i=1,x,y,c;i<n;++i)
	{
		F>>x>>y>>c;
		v[x].push_back( make_pair(y,c) );
		v[y].push_back( make_pair(x,c) );
	}
	F>>k;
	for (int i=1,r;i<=k;++i)
	{
		F>>r;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		dfs(r,0,0);
		//for (int i=1;i<=n;++i) cerr<<a[i]<<' ';cerr<<'\n';
		//for (int i=1;i<=n;++i) cerr<<b[i]<<' ';cerr<<'\n';
		G<<min(a[r],b[r])<<'\n';
	}
}
