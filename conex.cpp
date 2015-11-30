#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;
 
#define F cin
#define G cout
 
const int N = 10010;

/// is the graph conex if I cut all edges specified
 
int n,m,q,nbr,ans[N],mark[N],comp[N],ct,mk[N];
pair<int,int> edges[N];
vector<int> v[N],w[N];
vector<int> querys[N];
vector<int> bunch;
 
void dfs(int x)
{
    comp[x] = ct;
    for (int i=0;i<int(v[x].size());++i)
    {
        if ( mark[v[x][i]] ) continue;
        int y = edges[v[x][i]].first + edges[v[x][i]].second - x;
        if ( comp[y] == 0 ) dfs(y);
    }
}
 
void go(int x)
{
    mk[x] = 1;
    for (int i=0;i<int(w[x].size());++i)
    {
        int y = w[x][i];
        if ( mk[y] == 0 )
            go(y);
    }
}
 
void solve(vector<int> bunch)
{
    memset(mark,0,sizeof(mark));
    memset(comp,0,sizeof(comp));
    for (int i=0;i<int(bunch.size());++i)
    {
        int qq = bunch[i];
        for (int j=0;j<int(querys[qq].size());++j)
            mark[ querys[qq][j] ]++;
    }
    ct = 0;
    for (int i=1;i<=n;++i) // find components
        if ( comp[i] == 0 )
        {
            ++ct;
            dfs(i);
        }
    //for (int i=1;i<=n;++i) cerr<<comp[i]<<' '; cerr<<'\n';
    for (int i=0;i<int(bunch.size());++i)
    {
        for (int j=0;j<int(bunch.size());++j)
            if ( i != j )
            {
                int wh = bunch[j];
                for (int k=1;k<int(querys[wh].size());++k)
                {
                    int ee = querys[wh][k];
                    int x = edges[ee].first;
                    int y = edges[ee].second;
                    if ( (--mark[ee]) == 0 )
                        if ( comp[x] != comp[y] )
                        {
                            w[comp[x]].push_back(comp[y]);
                            w[comp[y]].push_back(comp[x]);
                        }
                }
            }
        go(1); // verify if graph w is conex
        ans[bunch[i]] = 1; 
        for (int j=1;j<=ct;++j)
            if ( mk[j] == 0 )
                ans[bunch[i]] = 0;
        for (int j=0;j<int(bunch.size());++j)
            if ( i != j )
            {
                int wh = bunch[j];
                for (int k=1;k<int(querys[wh].size());++k)
                {
                    int ee = querys[wh][k];
                    mark[ee]++;
                }
            }
        for (int j=1;j<=ct;++j)
            w[j] = vector<int>();
        memset(mk,0,sizeof(mk));
    }
}
 
int main()
{
    ios::sync_with_stdio(0);
    #ifndef ONLINE_JUDGE
        ifstream F("p.in");
    #endif
    F>>n>>m>>q;
    for (int i=1,x,y;i<=m;++i)
    {
        F>>x>>y;
        edges[i] = make_pair(x,y);
        v[x].push_back(i);
        v[y].push_back(i);
    }
 
    for (int i=1,nb;i<=q;++i)
    {
        F>>nb;
        for (int j=0,k;j<nb;++j)
        {
            F>>k;
            querys[i].push_back(k);
        }
    }
    nbr = int(sqrt(q));
    for (int i=1;i<=q;++i)
    {
        bunch.push_back(i);
        if ( int(bunch.size()) == nbr )
        {
            solve(bunch);
            bunch.clear();
        }
    }
    if ( bunch.size() )
        solve(bunch);
    for (int i=1;i<=q;++i)
        G<<ans[i]<<'\n';
}
