#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <numeric>
#include <map>
#include <set>
#include <algorithm>
#include <vector>
#include <cstring>
#include <sstream>
#include <queue>
#include <bitset>
#include <cmath>
using namespace std;

#define F cin
#define G cout

const int K = 110;
const int N = 100010; 
const int M = 1000000007;

struct robot {
	int c,f,m;
};

bool byf(robot a,robot b)
{
	return a.m == b.m ? a.f < b.f : a.m > b.m;
}

bool byc(robot a,robot b)
{
	return a.c > b.c;
}

int n,d,tf,bst;
vector<robot> v;
pair<int,int> ans;

pair<int,int> solve(int n,int tf,vector<robot> v,int bst)
{ 
	int ans = 0, carry = 0;
	int _tf = tf;
	if ( bst != -1 )
	{
		robot now = v[bst];
		if ( tf < now.f ) 
			return make_pair(0,0);
		swap(v[bst],v.back());
		v.pop_back();
	
		tf -= now.f;
		carry += now.c;
		ans++;
		--n;
	}
	sort(v.begin(),v.end(),byf);
	
	vector<robot> w,ww;
	for (int i=0;i<n;++i)
	{
		if ( v[i].f <= tf && v[i].m )
		{	
			ans++;
			carry += v[i].c;
			tf -= v[i].f;
			ww.push_back( v[i] );
		}
		else
			w.push_back( v[i] );
	}
	//cerr<<ans<<'\n';
	//cerr<<carry<<'\n';
	sort(w.begin(),w.end(),byc);
	n = int(w.size());
	
	for (int i=0;i<n;++i)
		if ( carry )
		{
			ans++;
			carry += w[i].c - 1;
		}
	if ( !ww.empty() )
		while ( carry-- )
		{
			tf += ww.back().f;
			ww.pop_back();
			if ( ww.empty() )
				break;
		}
	return make_pair(ans,_tf-tf);
}

int main() 
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif
	
	F>>n>>d>>tf;
	for (int i=1;i<=n;++i)
	{
		robot now;
		F>>now.c>>now.f>>now.m;
		now.m = now.m >= d ? 1 : 0;
		v.push_back(now);
	}
	bst = -1;
	for (int i=0;i<n;++i)
		if ( v[i].m && v[i].c )
		{
			if ( bst == -1 ) bst = i;
			if ( v[i].f < v[bst].f )
				bst = i;
		} 
	ans = max(solve(n,tf,v,bst),solve(n,tf,v,-1));
	//ans =solve(n,tf,v,bst);
	G<<ans.first<<' '<<ans.second<<'\n';
}
