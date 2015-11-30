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

#define F cin
#define G cout

const int K = 1010;
const int N = 5010; 
const int P = 100; 
const int B = 11; 
const int M = 1000000007;

int n,sg[N];
string s;

int main() 
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif

	for (int i=3;i<N;++i)
	{
		set<int> st;
		for (int j=1;j<=i/2;++j)
			st.insert(sg[j]^sg[i-j-1]);
		int mex = 0;
		while ( st.count(mex) )
			++mex;
		sg[i] = mex;
	}
	
	F>>s;
	n = s.size();
	
	for (int i=1;i<n;++i)
		if ( s[i-1] == s[i+1] )
		{
			int co = 0, ans = 0;
			for (int j=0;j<n;++j)
				if ( j != 0 && j != n-1 && ( j < i-1 || j > i+1 ) && s[j-1] == s[j+1] )
					co++;
				else
				{
					ans ^= sg[co+1];
					co = 1;
				}
			if ( ans == 0 )
			{
				G<<"First\n"<<i+1<<'\n';
				return 0;
			}
		}
	G<<"Second\n";
}
