#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
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

const int K = 35;
const int N = 510;
const int M = 1000000007;

#define x first
#define y second
#define mp make_pair

int n,m,k;
char a[N][N];
int s[N][N],c[N];

int main()
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif

	F>>n>>m>>k;
	for (int i=1;i<=n;++i)
		F>>(a[i]+1);
	for (int i=2;i<n;++i)
		for (int j=2;j<m;++j)
			s[i][j] = int(a[i][j]+a[i-1][j]+a[i][j-1]+a[i+1][j]+a[i][j+1]-5*'0') == 5;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			s[i][j] += s[i-1][j];

	long long tot = 0;
	for (int i=1;i<=n;++i)
		for (int j=i;j<=n;++j)
		{
			//cerr<<tot<<' ';
			tot += m*(m+1)/2;
			if ( j-i+1 >= 3 ) 
			{
				for (int k=1;k<=m;++k)
					c[k] = s[j-1][k] - s[i][k]; 
			}
			else
				memset(c,0,sizeof(c));
			
			tot -= 3; // the first and last line and both ends
			
			int l = 2;
			int sm = 0;
			for (int r=2;r<m;++r)
			{
				sm += c[r];
				while ( sm >= k )
				{
					sm -= c[l];
					++l;
				}
				tot -= r-l+3;
			}
			//cerr<<tot<<'\n';
		} 
	tot = max(tot,0LL);
	G<<tot<<'\n';
}
