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

int t;
double a,b;

int main()
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif

	F>>t;
	while ( t-- )
	{
		F>>a>>b;
		double ans = 0;
		if ( b == 0 ) 
			ans = 1; 
		else
			if ( a == 0 ) 
				ans = 0.5;
			else
			{
				double l = b * 4;
				ans = 1.0 * a * b;
				if ( l < a )
					ans += 0.5 * l * b + 1.0 * (a - l) * b;
				else
					ans += 0.125 * a * a;
				ans /= (2.0 * a * b);
			}
		G<<fixed<<setprecision(6)<<ans<<'\n';
	}
}

