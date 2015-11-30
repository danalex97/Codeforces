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

const int K = 35;
const int N = 200010; 
const int P = 100; 
const int B = 11; 
const int M = 1000000007;
const int M2 = 1000000009;

int n,h;
lng dp[2][K][K][K][2],ans; // dp[line][a1][a2][a3][v] = number of ways to complete the line-th row 
// ( 0/1 ) if the distances are a1,a2,a3 and 1 ( 1 for the last value + if it is still alive )
// - if either a1,a2,a3 are 0 , it is dead

int main()
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif

	F>>n>>h;
	dp[0][0][0][0][1] = 1;
	for (int i=0;i<n;++i)
		for (int a1=0;a1<=h;++a1)
			for (int a2=0;a2<=h;++a2)
				for (int a3=0;a3<=h;++a3)
					for (int v=0;v<=1;++v)
					{
						lng &t = dp[i&1][a1][a2][a3][v];
						if ( !t ) continue;
						
						int a4 = h;
						if ( v ) 
							a4 = 0;
						t %= M2;
						
						dp[(i&1)^1][min(h,a1+1)][min(h,a2+1)][min(h,a3+1)][a4<h] += t;
						dp[(i&1)^1][min(h,a4+1)][min(h,a1+1)][min(h,a2+1)][a3<h] += t;
						dp[(i&1)^1][min(h,a3+1)][min(h,a4+1)][min(h,a1+1)][a2<h] += t;
						dp[(i&1)^1][min(h,a2+1)][min(h,a3+1)][min(h,a4+1)][a1<h] += t;
						
						t = 0;
					}
	for (int a1=0;a1<=h;++a1)
		for (int a2=0;a2<=h;++a2)
			for (int a3=0;a3<=h;++a3)
				for (int v=0;v<=1;++v)
					if ( a1 < h || a2 < h || a3 < h || v == 1 )
					{
						ans += dp[n&1][a1][a2][a3][v];
						ans %= M2;
					}
	G<<ans<<'\n';
}
