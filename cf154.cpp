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

ifstream F("input.txt");
#define G cout

const int K = 410;
const int N = 50010; 
const int M = 1000000007;

struct event {
	int t,p,s,i;
};

bool _t(event a,event b)
{
	return a.t < b.t;
}

typedef bool (*comp)(event,event);

bool cmp(event a,event b)
{
	return a.p < b.p;
}

event e[N];
int n,idx;
long long t,ans[N];
set<int> st;

long long good(int pr)
{
	for (int i=1;i<=n;++i)
		if ( e[i].i == idx )
			e[i].p = pr;
	
	priority_queue<event,vector<event>,comp> pq(cmp);
	int pl = 1;
	long long tt = 0;
	while ( pl <= n )
	{
		if ( !pq.empty() )
		{
			while ( pq.top().s + tt <= e[pl].t )
			{
			//	cerr<<"d:"<<pl<<'\n';
				tt += pq.top().s;
				ans[pq.top().i] = tt;
				pq.pop();
				
				if ( pq.empty() )
					break;
			}  
		} 
		if ( !pq.empty() )
		{
			event tp = pq.top();
			tp.s -= e[pl].t - tt;
			tt = e[pl].t;
			pq.pop();
			pq.push(tp);
		}
		tt = e[pl].t;
		pq.push( e[pl++] );
	}
	while ( !pq.empty() )
	{
		tt += pq.top().s;
		ans[pq.top().i] = tt;
		pq.pop();
	}
	return ans[idx];
}

int bs(int l,int r)
{
	if ( r-l < 2 )
	{
		if ( good(r) == t )
			return r;
		return l;
	}
	int m = (1LL*l + 1LL*r) / 2LL;
	//cerr<<l<<' '<<r<<' '<<good(m)<<'\n';
	if ( good(m) > t )
		return bs(m+1,r);
	return bs(l,m);
}

int main() 
{
	ios::sync_with_stdio(0);
	#ifdef ONLINE_JUDGE
		ofstream G("output.txt");
	#endif
	
	F>>n;
	for (int i=1;i<=n;++i)
	{
		F>>e[i].t>>e[i].s>>e[i].p;
		e[i].i = i;
		if ( e[i].p == -1 ) idx = i;
		st.insert(e[i].p);
	}
	sort(e+1,e+n+1,_t);
	F>>t;
	//int rt = 4;
	//good(rt);
	int tt = bs(1,1000000000);
	int lt = tt;
	int rt = tt;
	while ( st.count(lt) ) --lt; 
	while ( st.count(rt) ) ++rt;
	if ( lt >= 0 ) 
		if ( good(lt) == t )
		{
			G<<lt<<'\n';
			for (int i=1;i<=n;++i)
				G<<ans[i]<<' ';
			return 0;
		}
	good(rt);
	G<<rt<<'\n';
	for (int i=1;i<=n;++i)
		G<<ans[i]<<' ';
	G<<'\n';
}
