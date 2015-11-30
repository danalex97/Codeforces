#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#define F cin
#define G cout
//ifstream F("p.in");

typedef long long lng;

const int N = 100010; 
const int P = 20; 

int n,m,a[N],rmq[P][N<<1],lg[N];

void buildRMQ()
{
	for (int i=1;i<=n;++i)
		rmq[0][i] = a[i];
	for (int l=1;(1<<l)<=n;++l)
		for (int i=1;i<=n;++i)
			rmq[l][i] = max( rmq[l-1][i] , rmq[l-1][i+(1<<(l-1))] );
}

int query(int l,int r)
{
	int len  = r - l + 1;
	int line = lg[len];
	
	int int1 = rmq[line][l]; 
	int int2 = rmq[line][r-(1<<line)+1];
	return max(int1,int2);
}

void computeLog()
{
	lg[1] = 0;
	for (int i=2,t=2;i<=n;++i)
		if ( i == t )
		{
			lg[i] = lg[i-1] + 1;
			t <<= 1;
		} 
		else
			lg[i] = lg[i-1];
}

int main() 
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif
	
	F>>n;
	for (int i=1;i<=n;++i)
		F>>a[i];
	
	buildRMQ();
	computeLog();
	
	F>>m;
	for (int i=1,l,r;i<=m;++i)
	{
		F>>l>>r;
		G<<query(l,r)<<'\n';
	}
}
