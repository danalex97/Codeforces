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
//typedef set<node,bool(*)(node,node)> myset; // custom set

#define F cin
#define G cout

const int K = 1010;
const int N = 1000010; 
const int P = 35; 
const int B = 11; 
const int M2 = 7340033;
const int M = 1000000007;

char c[N];
string s,ss;

int main()
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("list.txt");
		ofstream G("div 1.txt");
	#endif
	
	while ( F>>s )
	{
		ss += s + ' ';
	}
	for (int i=0;i<int(ss.size());++i)
		c[i] = ss[i];
	
	char *p1 = c,*p2 = c;
	while ( p1 = strstr(p1,"\"id\"") ) 
	{
		p2 = strstr(p1,"\"type\"");
		char cc[K];
		memset(cc,0,sizeof(cc));
		int w = 0;
		for (char *p=p1;p!=p2;++p)
			cc[w++] = *p;
		if ( strstr(cc,"Div. 1") ) 
			G<<cc<<'\n';
		p1 = p2;
	}
}
