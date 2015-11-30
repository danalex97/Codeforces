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

const int K = 310;
const int N = 200010; 
const int P = 100; 
const int B = 11; 
const int M = 1000000007;

#define double long double

double ans = 1LL<<60;
int n;
double s[N];

double f(double x)
{













for (int i=1;i<=n;++i)
	{
		if ( mx < s[i] ) mx = s[i];
		if ( mn > s[i] ) mn = s[i];
	}
	for (int i=1;i<=n;++i) s[i] -= x*i;
	return max(mx-mn,max(abs(mx),abs(mn)));
}

int stk = 10000;

double ts(double lx,double rx)
{
	//if ( --stk > 0 ) cerr<<lx<<' '<<rx<<'\n';
	if ( rx - lx < 0.00000000001 )
		return rx;
	double m = ( rx - lx ) / 3;
	if ( f(lx+m) < f(lx+2*m) )
		return ts(lx,lx+2*m);
	return ts(lx+m,rx);
}

int main() 
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif

    	F>>n;
	for (int i=1;i<=n;++i)
		F>>s[i];
	for (int i=1;i<=n;++i)
		s[i] += s[i-1];
	ans = f(0);
	ans = min(ans,f(ts(-10000,10000)));
	G<<fixed<<setprecision(6)<<ans-0.000001<<'\n';
}
