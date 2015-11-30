#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

#define F cin
#define G cout

const int N = 100010;
const int nn = (N-10)/2;
const int M = 1000000007;

struct query {
	int a,t,id;
	query(int _a,int _t,int _id)
	{
		a = _a;
		t = _t;
		id = _id;
	}
};

const int Nmax = 100011 ;
const int LgNx = 20 ;
const int Mmax = 2000011 ;

int sz[N],Rmq[LgNx][Nmax << 2];
 
int L,Lg[Nmax << 1];
int High[Nmax << 1];
int Lvl[Nmax << 1];
int First[Nmax];
 
set<int> s[2][N];

int n,m,qs;
vector<int> v[N],w[N];
vector<query> q[N];

set<int> now;

void dfs(int x,int dd)
{
	for (int i=0;i<int(q[x].size());++i)
	{
		query qq = q[x][i];
		if ( qq.t != 1 ) continue; 
		int co = qq.a;
		for (set<int>::iterator j=now.begin();j!=now.end() && co;++j,--co)
			s[qq.t][qq.id].insert( *j );
	}	
	for (int i=0;i<int(w[x].size());++i)
		now.insert( w[x][i] );
	for (int i=0;i<int(q[x].size());++i)
	{
		query qq = q[x][i];
		if ( qq.t != 0 ) continue; 
		int co = qq.a;
		for (set<int>::iterator j=now.begin();j!=now.end() && co;++j,--co)
			s[qq.t][qq.id].insert( *j );
	}
	for (int i=0;i<int(v[x].size());++i)
	{
		int y = v[x][i];
		if ( y != dd )
			dfs(y,x);
	}
	for (int i=0;i<int(w[x].size());++i)
		now.erase( w[x][i] );
}

void Get( int Nod , int Niv)
{
    High[ ++L ]=Nod;
    Lvl[ L ]=Niv;
    First[ Nod ]=L;
 
    for (int i=0;i<int( v[Nod].size() );++i)
    {
        Get( v[Nod][i] , Niv+1 );
        High[ ++L ]=Nod;
        Lvl[ L ]=Niv;
    }
}
 
void Build()
{
    for (int i=1;i<=L;++i)
        Lg[i]=Lg[i>>1]+1;
    for (int i=1;i<=L;++i)
        Rmq[0][i]=i;
 
    for (int i = 1; (1 << i) < L; ++i)
        for (int j = 1; j <= L - (1 << i); ++j)
        {
            int l = 1 << (i - 1);
            Rmq[i][j] = Rmq[i-1][j];
            if ( Lvl[Rmq[i-1][j + l]] < Lvl[Rmq[i][j]] )
                Rmq[i][j] = Rmq[i-1][j + l];
        }
}
 
int LCA(int x, int y)
{
    int Difrence, l, Sol, Sift;
 
    int a = First[x];
    int b = First[y];
    if (a > b) swap(a, b);
 
    Difrence = b - a + 1;
    l = Lg[ Difrence ]-1;
 
    Sol = Rmq[l][a];
    Sift = Difrence - (1 << l) ;
 
    if( Lvl[Sol] > Lvl[Rmq[l][a + Sift]] )
        Sol = Rmq[l][a + Sift];
    return High[Sol];
}

int main()
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif
	
	F>>n>>m>>qs;
	for (int i=1,x,y;i<n;++i)
	{
		F>>x>>y;
		v[x].push_back(y);
	}
	for (int i=1,p;i<=m;++i)
	{
		F>>p;
		w[p].push_back(i);
	}
	Get( 1,0 );
    Build();
	
	for (int i=1,l,r,mm,a;i<=qs;++i)
	{
		F>>l>>r>>a;
		mm = LCA(l,r);
		q[l].push_back( query(5*a,0,i) );
		q[r].push_back( query(5*a,0,i) );
		q[mm].push_back( query(a,1,i) );
		sz[i] = a;
	}
	dfs(1,0);
	for (int i=1;i<=qs;++i)
	{
		set<int> my = s[0][i];
		for (set<int>::iterator j=s[1][i].begin();j!=s[1][i].end();++j)
			my.erase(*j);
		vector<int> ans;
		for (int j=1;j<=sz[i];++j)
		{
			if ( !my.empty() )
			{
				ans.push_back(*my.begin());
				my.erase(my.begin());
			}
		}
		G<<ans.size()<<' ';
		for (int i=0;i<int(ans.size());++i)
			G<<ans[i]<<' ';
		G<<'\n';
	}
}
