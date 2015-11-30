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
const int N = 101; 
const int P = 100; 
const int B = 11; 
const int M = 1000000007;

struct mat
{
	int v[N+10][N+10];
	mat()
	{ 
		memset(v,0,sizeof(v)); 
	}
};

mat operator * (mat a,mat b)
{
	mat c;
	for(int i=1;i<=N;++i)
		for(int k=1;k<=N;++k)
			for(int j=1;j<=N;++j)
			{
				c.v[i][j] += (1LL*a.v[i][k]*b.v[k][j]) % M;
				c.v[i][j] %= M;
			}
	return c;
}

mat operator ^ (mat a,int k)
{
	mat c = a;
	--k;
	while ( k )
	{
		if ( k % 2 ) c = c * a;
		a = a * a;
		k /= 2;
	}
	return c;
}

mat a;
int n,x;

int main() 
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif

	F>>n>>x;
	if ( x == 0 )
	{
		G<<"1\n";
		return 0;
	}

	for (int i=1,y;i<=n;++i)
	{
		F>>y;
		a.v[N-y][N-1]++;
		a.v[N-y][N]++;
	}
	for (int i=2;i<=N-1;++i)
		a.v[i][i-1] = 1;
	a.v[N][N] = 1;
	
	a = a ^ x;
	int ans = ( a.v[N-1][N] + a.v[N][N] ) % M;
	G<<ans<<'\n';
}
