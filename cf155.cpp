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

const int K = 410; 
const int N = 1010; 
const int M = 1000000007;

char a[N][N];

struct cell
{
	int x,y;
};

cell _cell(int x,int y)
{
	cell ans;
	ans.x = x;
	ans.y = y;
	return ans;
}

bool cmp(cell a,cell b)
{
	return a.x == b.x ? a.y < b.y : a.x < b.x;
}

typedef bool (*comp)(cell,cell);

int n,m,d,mk[N][N];
vector<cell> rats,spots,aux,spots2; 
set<cell,comp> st(cmp);

int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };

vector<cell> boom(int x,int y,int d)
{
	queue<cell> q;
	q.push( _cell(x,y) );
	vector<cell> ans;
	
	if ( a[x][y] == 'X' ) return ans;
	mk[x][y] = 1;
	
	while ( !q.empty() )
	{
		cell now = q.front();
		q.pop(); 
		
		ans.push_back( now );
		for (int i=0;i<4;++i)
		{
			cell nxt = _cell( now.x + dx[i] , now.y + dy[i] );
			if ( a[nxt.x][nxt.y] == 'X' ) continue;
			if ( mk[now.x][now.y] - 1 >= d ) continue;
			if ( !mk[nxt.x][nxt.y] )
			{
				mk[nxt.x][nxt.y] = mk[now.x][now.y] + 1; 
				q.push(nxt);
			}
		}
	}
	
	for (int i=0;i<int(ans.size());++i) mk[ans[i].x][ans[i].y] = 0;
	
	return ans;
}

#define print(st) { for(vector<cell>::iterator it=st.begin();it!=st.end();++it) cerr<<'('<<it->x<<','<<it->y<<") "; cerr<<'\n'; }
#define print2(st) { for(set<cell,comp>::iterator it=st.begin();it!=st.end();++it) cerr<<'('<<it->x<<','<<it->y<<") "; cerr<<'\n'; }

int main()
{
	ios::sync_with_stdio(0);
	ifstream F("input.txt");
	#ifdef ONLINE_JUDGE
		ofstream G("output.txt");
	#endif
	
	F>>n>>m>>d;
	for (int i=1;i<=n;++i)
		F>>(a[i]+1);
	
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			if ( a[i][j] == 'R' )
				rats.push_back( _cell(i,j) );
	spots = boom(rats[0].x,rats[0].y,d);
	
	//print(spots);
	//print(rats);
	
	if ( int(rats.size()) > d*d*8 ) 
	{
		G<<"-1\n";
		return 0;
	} 
	for (int i=0;i<int(spots.size());++i)
	{
		st.clear();
		for (int j=0;j<int(rats.size());++j)
			st.insert(rats[j]);
	
		int xx = spots[i].x , yy = spots[i].y;
		//if ( a[xx][yy] != '.' ) continue;  
		
		aux = boom(xx,yy,d);
		for (int j=0;j<int(aux.size());++j)
			st.erase(aux[j]);
			
		//if ( xx == 2 && yy == 3 ) print2(st);
		//if ( xx == 2 && yy == 3 ) print(aux);
			
		if ( st.empty() )
		{
			//cerr<<"here\n";
			for (int i=1;i<=n;++i)
				for (int j=1;j<=m;++j)
					if ( a[i][j] != 'X' && ( i != xx || j != yy ) )
					{
						G<<xx<<' '<<yy<<'\n';
						G<<i<<' '<<j<<'\n';
						return 0;
					}
			G<<"-1\n";
			return 0;
		}
		
		spots2 = boom(st.begin()->x,st.begin()->y,d);
		for (int j=0;j<int(spots2.size());++j)
		{
			set<cell,comp> st2(cmp);
			st2 = st;
			int x = spots2[j].x , y = spots2[j].y;
			//if ( a[x][y] != '.' ) continue;  
			
			aux = boom(x,y,d);
			for (int j=0;j<int(aux.size());++j)
				st2.erase(aux[j]);
			if ( st2.empty() )
			{
				G<<xx<<' '<<yy<<'\n';
				G<<x<<' '<<y<<'\n';
				return 0;
			} 
		}
	}
	G<<"-1\n";
}
