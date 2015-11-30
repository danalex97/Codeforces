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

typedef long long lng;
//typedef set<node,bool(*)(node,node)> myset; // custom set

string x="ab",y="cd";

#define F cin
#define G cout

const int K = 20;
const int N = 2010; 
const int P = 100; 
const int B = 11; 
const int M = 1000000007;
int steps;

int n,m,co;
char a[K][K];
char b[K][K];

void flip(int p)
{
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			if ( (i + j) % 2 == p )
			if ( a[i][j] == '1' )
			{
				++co;
				a[i-1][j] = '1'+'0'-a[i-1][j];
				a[i+1][j] = '1'+'0'-a[i+1][j];
				a[i][j-1] = '1'+'0'-a[i][j-1];
				a[i][j+1] = '1'+'0'-a[i][j+1];
				a[i][j] = '0';
			}
}

int main() 
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
    #endif
    
    cerr<<x+y<<'\n';
    
    F>>n>>m;
    for (int i=1;i<=n;++i)
	{
		F>>(b[i]+1);
	}
	for (int i=1;i<=n;++i)
					for (int j=1;j<=m;++j)
						a[i][j] = b[i][j];
	steps = 500;
	while (steps--){flip(0);
	flip(1);}
	int x = co;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			if ( a[i][j] == '1' )
				x = -1;
	for (int i=1;i<=n;++i)
					for (int j=1;j<=m;++j)
						a[i][j] = b[i][j];
	steps = 500;
	while (steps--){flip(1);
	flip(0);}
	int y = co;
for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			if ( a[i][j] == '1' )
				y=  -1;
	if ( x == -1 && y == -1 ) G<<"Nan";else
	if ( x == -1 && y != -1 ) G<<y;else
	if ( x != -1 && y == -1 ) G<<x;else
	G<<min(x,y)<<'\n';
}
