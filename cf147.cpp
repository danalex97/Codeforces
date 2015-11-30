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
const int N = 210; 
const int P = 100; 
const int B = 11; 
const int M = 1000000007;

int n,m,cap[N][N],ans,mk[N];
char s[N];

int path(int x,int _mn) // returns the capacity of a path from node x to the sink ( _mn being the current minimum )
// O(V*F) , where F is the maximum flow , i.e. the length of s
{
	if ( x == m-1 ) 
		return _mn;
	mk[x] = 1;
	for (int y=0;y<m;++y)
		if ( !mk[y] && cap[x][y] )
		{
			int mn = path(y,min(_mn,cap[x][y]));
			if ( mn ) 
			{
				cap[x][y] -= mn;
				cap[y][x] += mn;
				return mn; 
			} 
		}
	return 0;
}

int main() 
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif
	
	F>>s>>n;
    m = n+28;

	for (int i=0;s[i];++i)
		cap[n+int(s[i]-'a'+1)][m-1]++;
	for (int i=1;i<=n;++i)
	{
		F>>s>>cap[0][i];
		for (int j=0;s[j];++j)
			cap[i][n+int(s[j]-'a'+1)]++;
	}

	while ( 1 )
	{
		if ( !path(0,1<<30) ) 
			break;
		memset(mk,0,sizeof(mk));
	}
	
	int ans = 0;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=26;++j)
			ans += i*cap[n+j][i];
	for (int i=n+1;i<=n+26;++i)
		if ( cap[i][m-1] )
			ans = -1;
	G<<ans<<'\n';
}
