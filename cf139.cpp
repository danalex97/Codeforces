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

const int K = 41; 
const int M = 60000007;
const int B = 139;
const int B2 = 10003;

char s[K][K];
int n,m;
int dp[M];

int dx[] = { 1,-1,0,0 };
int dy[] = { 0,0,1,-1 };

int _hash(vector<pair<int,int> >& a)
{
	int ans = 0;
	for (int i=0;i<int(a.size());++i)
		ans = ( 1LL * ans * B2 + 1LL * a[i].first * B + 1LL * a[i].second ) % M;
	return ans;
}

void print(vector<pair<int,int> > v)
{
	for (int i=0;i<int(v.size());++i)
		cerr<<'('<<v[i].first<<' '<<v[i].second<<") ";
	cerr<<'\n';
}

int main()
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("input.txt");
	#endif
	
	F>>n>>m;
	for (int i=1;i<=n;++i)
		F>>(s[i]+1);
		
	vector<pair<int,int> > snake;
	int sz = 0;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			if ( s[i][j] >= '1' && s[i][j] <= '9' )
			{
				sz = max(sz,int(s[i][j]-'0'));
				//cerr<<sz<<'\n';
			}
	snake.resize(sz);
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			if ( s[i][j] >= '1' && s[i][j] <= '9' )	
				snake[int(s[i][j]-'1')] = make_pair(i,j);
	
	//print(snake);
	queue<vector<pair<int,int> > > q;
	q.push(snake);
	
	dp[_hash(snake)] = 0;
	
	int ans = -1;
	while ( !q.empty() )
	{
		vector<pair<int,int> > now = q.front();
		q.pop();
		//print(now);
		
		if ( s[now[0].first][now[0].second] == '@' )
		{
			ans = dp[_hash(now)];
			//print(now);
			break;
		}
		vector<pair<int,int> > nxt;
		for (int i=0;i<4;++i)
		{
			int nx = now[0].first + dx[i];
			int ny = now[0].second + dy[i];
		
			if ( nx < 1 || ny < 1 || nx > n || ny > m || s[nx][ny] == '#' ) continue;
			
			nxt = now;
			nxt.pop_back();
			
			//cerr<<"here"<<'\n';
			
			if ( !count(nxt.begin(),nxt.end(),make_pair(nx,ny)) )
			{
				nxt.insert(nxt.begin(),make_pair(nx,ny));
				//cerr<<"here";
				if ( dp[_hash(nxt)] == 0 )
				{
					dp[_hash(nxt)] = dp[_hash(now)] + 1;
					q.push(nxt);
				}  
			}
		}
	}
	G<<ans<<'\n';
}
