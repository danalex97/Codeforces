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

const int K = 5;
const int N = 20; 
const int P = 100; 
const int B = 11; 
const int M = 1000000007;
 
int n,m,a[K],p[K],b[N],ans[N];

map<int,bool> mk[N][P];

void solve(int cl,int x,int y)
{
	if ( cl == m )
	{
		for (int i=0;i<n;++i,G<<'\n')
			for (int j=0;j<m;++j)
				if ( (ans[j]>>i) & 1 )
					G<<'*';
				else
					G<<'.';
		throw(0);
	} 
	
	if ( mk[cl][x][y] ) return;
	mk[cl][x][y] = 1;
	
	for (int i=0;i<(1<<n);++i)
	{
		int co = i&1;
		for (int j=1;j<n;++j)
			co += ((i>>j) & 1) & (~(i>>(j-1)) & 1); 
			
		if ( co != b[cl] ) continue;
		
		int now = y;
		for (int j=0;j<n;++j)
			if ( (~((x>>j) & 1)) & ((i>>j) & 1) )  
				now += p[j];
		
		bool flag = 1;
		for (int j=0;j<n;++j)
			if ( (now / p[j]) % B > a[j] || (now / p[j]) % B + (m - cl) / 2 < a[j] ) 
				flag = 0;
	
		if ( flag ) 
		{
			ans[cl] = i;
			solve(cl+1,i,now);
 		}
	}
}

int main() 
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif
	
	F>>n>>m;
	p[0] = 1;
	for (int i=0;i<n;++i)
	{
		F>>a[i];
		if ( i ) p[i] = p[i-1] * B;
	}
	for (int i=0;i<m;++i)
		F>>b[i];
	try 
	{
		solve(0,0,0);
	} 
	
	catch(int x)
	{
		cerr<<"found\n";
	}
}
