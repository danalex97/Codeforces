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

ifstream F("arbint.in");
ofstream G("arbint.out");

const int K = 35;
const int N = 100010; 
const int P = 100; 
const int B = 11; 
const int M = 1000000007;
const int M2 = 1000000009;
const int M3 = 666013;

int n,m,k;
char a[N];

int main()
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif

	F>>n>>m>>k;
	m += k;
	F.get();
	F>>a;
	
	for (int i=1,t,l,r,c,z;i<=m;++i)
	{
		F>>t;
		if ( t == 1 )
		{
			F>>l>>r>>c;
			memset(a+l,c,r-l+1);
		}
		else
		{
			F>>l>>r>>z;
			if ( !memcmp(a+l,a+l+z,r-l-z+1) )
				G<<"YES\n";
			else
				G<<"NO\n";
		}
	}
}
