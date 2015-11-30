#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <set>
using namespace std;

#define F cin
#define G cout

const int N = 100010;

int n,m,x[N],y[N],seg[N];
vector<int> v[N];
vector<int> w[N];
set<pair<int,int> > st;

int main()
{
    ios::sync_with_stdio(0);
    #ifndef ONLINE_JUDGE
        ifstream F("p.in");
    #endif

	F>>n>>m;
	for (int i=1;i<=m;++i)
	{
		F>>x[i]>>y[i];
		v[y[i]].push_back(i); 
		w[x[i]].push_back(i); 
	}
	vector<int> ans;
	for (int i=n;i>=1;--i)
	{
		for (int j=0;j<int(v[i].size());++j)
		{
			int x = v[i][j];
			st.insert( make_pair(::x[x],x) );
		}
		
		if ( !st.empty() )
		{
			ans.push_back( st.begin()->second );
			st.erase(st.begin());
		}
		
		for (int j=0;j<int(w[n-i+1].size());++j)
		{
			int x = w[n-i+1][j];
			st.erase( make_pair(::x[x],x) );
		}
	}
	G<<ans.size()<<'\n';
	for (int i=0;i<int(ans.size());++i)
		G<<ans[i]<<' ';
	G<<'\n';
}
