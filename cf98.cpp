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

const int K = 20;
const int N = 200010; 
const int P = 100; 
const int B = 11; 
const int M = 1000000007;

int n,cnt[N],a[N],b[N];
char s[N];
char w[] = "AEIOUaeiou";

int main() 
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif

	F>>(s+1);
	n = strlen(s+1);
	
	for (int i=1;i<=n;++i)
	{
		bool flag = 0;
		for (int j=0;j<10;++j)
			if ( s[i] == w[j] )
				flag = 1;
		if ( flag ) 
			a[i] = 1;
		else
			a[i] = -2;
	}
	for (int i=1;i<=n;++i)
		a[i] += a[i-1];
	for (int i=1;i<=n;++i)
		b[i] = max(b[i-1],a[i]);
	//for (int i=1;i<=n;++i) cerr<<a[i]<<' ';cerr<<'\n';
	//for (int i=1;i<=n;++i) cerr<<b[i]<<' ';cerr<<'\n';
	
	for (int i=1;i<=n;++i)
	{
		int j = lower_bound(b,b+i+1,a[i]) - b;
		cnt[i-j]++;
	}
	for (int i=n;i>=1;--i)
		if ( cnt[i] )
		{
			G<<i<<' '<<cnt[i]<<'\n';
			return 0;
		}
	G<<"No solution\n";
}
