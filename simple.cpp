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

const int K = 1010;
const int N = 200010; 
const int P = 35; 
const int B = 11; 
const int M2 = 7340033;
const int M = 1000000007;

int n,x,times;

int main()
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif
	
	F>>n>>x;
	times = (n - x) % n;
	for (int i=1;i<n;++i)
	{
		F>>x;
		if ( i % 2 )
			x -= times;
		else
			x += times;
		x = ( x + n ) % n;
		if ( x != i )
		{
			G<<"No\n";
			return 0;
		}
	}
	G<<"Yes\n";
}
