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

typedef long long lng;

const int K = 5;
const int N = 20; 
const int P = 100; 
const int B = 11; 
const int M = 1000000007;

int a,b,c,l;

lng solve1(int a,int b,int c,int l) // c > a , c > b 
{
	lng ans = 0;
	for (int k=a+b;k<=a+b+l;++k)
	{
		int mn = max(a,b);
		int mx = min(k-1,c+l-(k-a-b));
		cerr<<k<<' '<<mn+1<<' '<<mx<<'\n';
		ans += 1LL * (k-a-b+1) * max(0,mx-mn);
	}
	return ans;
}

lng solve2(int a,int b,int c,int l) // a = b , b > c
{
	lng ans = 0;
	l -= max(a,b)-min(a,b);
	a = max(a,b);
	for (int k=a;k<=a+l/2;++k)
	{
		int nl = l-(k-a)*2;
		int mn = c-1;
		int mx = min(c+nl,k-1);
		ans += max(0,mx-mn);
		cerr<<k<<' '<<mn+1<<' '<<mx<<'\n';
	}
	cerr<<ans<<'\n';
	return ans;
}

lng solve3(int a,int b,int c,int l) // a = b = c 
{
	int m = max(a,b);
	m = max(m,c);
	l -= m-a;
	l -= m-b;
	l -= m-c;
	lng ans = 0;
	while ( l >= 0 )
	{
		ans ++;
		l -= 3;
	}
	return ans;
}

int main() 
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif
	
	F>>a>>b>>c>>l;
	lng ans = solve1(a,b,c,l) + solve1(b,c,a,l) + solve1(a,c,b,l); 
	ans += solve2(a,b,c,l) + solve2(b,c,a,l) + solve2(a,c,b,l); 
	ans += solve3(a,b,c,l);
	G<<ans<<'\n';
}
