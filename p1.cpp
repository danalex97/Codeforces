#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <numeric>
#include <map>
#include <tr1/unordered_map>
#include <set>
#include <tr1/unordered_set>
#include <algorithm>
#include <vector>
#include <cstring>
#include <sstream>
#include <queue>
#include <bitset>
#include <cmath>
using namespace std;

ifstream F("dubi.in");
ofstream G("dubi.out");

typedef long long lng;

const int K = 5010;
const int N = 200010; 
const int P = 100; 
const int B = 11; 
const int M = 1000000007;

int n,m,mk[N];
vector<int> ans[N];

int elim(int x)
{
	int i = 1;
	while ( i <= x )
		i <<= 1;
	i >>= 1;
	return x ^ i;
}

int main() 
{
	F>>n;
	for (int i=n;i>=1;--i)
		if ( mk[i] == 0 )
		{
			vector<int> now;
			int k = i;
			while ( k > 0 ) 
			{
				if ( mk[k] == 0 )
				{
					now.push_back(k);
					mk[k] = 1;
					k = elim(k);
				}
				else
					break;
			}
			ans[++m] = now;
		}
	G<<m<<'\n';
	for (int i=1;i<=m;++i)
	{
		G<<ans[i].size();
		for (int j=0;j<int(ans[i].size());++j)
			G<<' '<<ans[i][j];
		G<<'\n';
	} 
}

