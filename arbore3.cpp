#include <fstream>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
 
ifstream F("arbore3.in");
ofstream G("arbore3.out");
 
const int N = 1000010;
 
vector<int> v[N];
int n,s,a[N];
 
struct grp {
    map<int,int> *mp;
    int pl;
     
    grp(int x)
    {
        pl = x;
        mp = new map<int,int>;
        mp->insert(make_pair(0,1));
    }
     
    void merge(grp b)
    {
        if ( mp->size() >= (*b.mp).size() ) 
        {
            for (map<int,int>::iterator it=(b.mp)->begin();it!=(b.mp)->end();++it)
            {
                int wh = it->first + b.pl - pl;
                if ( mp->find(wh) == mp->end() )
                    mp->insert( make_pair(wh,it->second) );
                else
                    (*mp)[wh] += it->second;
            }
        }
        else
        {
            b.merge(*this);
            *this = b;
        }
    }
    void print()
    {
        cerr<<"deb: "<<pl<<'\n';
        for (map<int,int>::iterator it=mp->begin();it!=mp->end();++it)
            cerr<<"deb: "<<it->first<<' '<<it->second<<'\n';
        cerr<<'\n';
    }
};
 
int ans;
 
grp dfs(int x)
{
    if ( v[x].size() == 0 )
    {
        if ( a[x] == s ) ++ans;
        return grp(a[x]);
    }
    grp now = grp(0);
    for (int i=0;i<int(v[x].size());++i)
        now.merge( dfs(v[x][i]) );
    now.pl += a[x];
    //cerr<<"deb: "<<x<<'\n';
    //now.print();
    ans += (*now.mp)[s-now.pl];
    return now;
}
 
int main()
{
    F>>n>>s;
    for (int i=1,dd;i<=n;++i)
    {
        F>>dd>>a[i];
        if ( dd ) v[dd].push_back(i);
    }
    dfs(1);
    G<<ans<<'\n';
}
