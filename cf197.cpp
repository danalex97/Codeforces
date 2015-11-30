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
const int N = 1010; 
const int P = 22; 
const int B = 11; 
const int M = 1000000007;
const int M2 = 1000000009;

int n,a[N];
vector<pair<int,int> > ans;

void dfs(int stp)
{
	if ( stp > 3 ) return;
		
	bool flag = 1;
	for (int i=1;i<=n && flag;++i)
		if ( a[i] != i )
			flag = 0;
	if ( flag ) 
	{
		reverse(ans.begin(),ans.end());
		G<<ans.size()<<'\n';
		for (int i=0;i<int(ans.size());++i)
			G<<ans[i].first<<' '<<ans[i].second<<'\n';
		exit(0);
	}

	for (int i=1;i<=n;++i)
		if ( a[i] != i )
			for (int j=i+1;j<=n;++j)
				if ( abs(a[i]-a[j+1]) == 1 || abs(a[i-1]-a[j]) == 1 )
				{
					ans.push_back( make_pair(i,j) );
					reverse(a+i,a+j+1);
				
					dfs(stp+1);
				
					reverse(a+i,a+j+1);
					ans.pop_back();
				}
}

int main()
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif
	
	F>>n;
	a[n+1] = n+1;
	for (int i=1;i<=n;++i)
		F>>a[i];
	dfs(0);
}
