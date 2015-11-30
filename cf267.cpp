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
using namespace std;

#define F cin
#define G cout

const int K = 110;
const int N = 200010; 
const int M = 1000000007;

int n;

vector<int> ans;
multiset<int> ct; //count number of occurrences
map<int,int> wrap; // wrapper for each value : ( a b a )
vector<int> stk; // stack of unwrapped values 

void finish(int a,int b) 
{
	ans.push_back(a);
	ans.push_back(b);
	ans.push_back(a);
	ans.push_back(b);
	
	ct.clear();
	wrap.clear();
	stk.clear();
}

int main() 
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif
	F>>n;
	for (int i=1,v;i<=n;++i)
	{
		F>>v;
		if ( wrap.count(v) ) 
		// if we already have a wrap ( a b a ) , then we can update the solution
		// and clear the containers as two wraps won't overlaps and the wrap we made
		// is the leftmost
		{
			finish(wrap[v],v);
			continue;
		} 
		else
		{
			if ( ct.count(v) )
			{
				int cnt = ct.count(v) >= 2 ? 1 : 0; 
				// if a have at least 2 v's then we can also wrap one
				
				while ( cnt || stk.back() != v ) 
				{
					if ( stk.back() == v ) 
						cnt--;
					wrap[stk.back()] = v; // now just wrap
					stk.pop_back();
				} 
			} 
			ct.insert(v);
			stk.push_back(v);
		}
	}
	G<<ans.size()<<'\n';
	for (int i=0;i<int(ans.size());++i)
		G<<ans[i]<<' ';
	G<<'\n';
}
