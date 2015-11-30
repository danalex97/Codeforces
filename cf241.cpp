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
const int N = 200010; 
const int P = 100; 
const int B = 11; 
const int M = 1000000007;

int ans,n;
lng rat,a[N]; 
// to remember - work with actual intervals, it helps

int main() 
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif

	F>>n;
	for (int i=1;i<=n;++i)	
		F>>a[i];
	int k=0,i=0,j=0;
	for (k=1;k<=n;)
	{
		++ans;
		
		for(i=k;a[i]==-1;++i);
		for(j=i+1;a[j]==-1;++j);
		
		if(j>n) break;
		if( (a[j]-a[i]) % (j-i) != 0)
		{
			k=j;
			continue;
		}
		
		rat = (a[j]-a[i]) / (j-i);
		if ( a[j]-rat*(j-k) <= 0 )
		{
			k=j;
			continue;
		}
		for(k=j+1;k<=n && a[j]+rat*(k-j)>0 && (a[k]==-1 || a[k] == a[j]+rat*(k-j) );++k);
	}
	G<<ans<<'\n';
}
