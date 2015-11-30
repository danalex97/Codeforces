#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <set>
#include <cstring>
#include <cmath>
#include <iomanip>
using namespace std;

#define F cin
#define G cout

const int N = 410;

int n,m;
int v[N][N],d[N];

int main()
{
    ios::sync_with_stdio(0);
    #ifndef ONLINE_JUDGE
        ifstream F("p.in");
    #endif
    
    F>>n>>m;
    for (int i=1,x,y;i<=m;++i)
    {
		F>>x>>y;
		v[x][y] = v[y][x] = 1;
	}
	
	queue<int> q;
	q.push(1);
	memset(d,0x3f,sizeof(d));
	d[1] = 0;
	while ( !q.empty() )
	{
		int x = q.front();
		q.pop();
		
		for (int i=1;i<=n;++i)
			if ( d[x] + 1 < d[i] && v[x][i] != v[1][n] )
			{
				d[i] = d[x] + 1;
				q.push(i);
			}
	}
	
	//for (int i=1;i<=n;++i)
	//	cerr<<d[i]<<' ';
	//cerr<<'\n';
	
	if ( d[n] != d[0] )
		G<<d[n]<<'\n';
	else
		G<<"-1\n";
}
