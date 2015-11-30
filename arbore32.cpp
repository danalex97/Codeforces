#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
 
ifstream F("arbore3.in");
ofstream G("arbore3.out");
 
const int N = 1000010;
 
vector<int> v[N];
int n,s,a[N],vl;

int ans;

const int md = 666013;

struct myhash {
	vector< pair<int,int> > v[md];
	
	void add(int x,int y)
	{
		int pl = max(x,-x) % md, i = 0, sz = int(v[pl].size());
		for (;i<sz;++i)
			if ( v[pl][i].first == x )
			{
				v[pl][i].second += y;
				if ( v[pl][i].second == 0 )
				{
					swap(v[pl][i],v[pl].back());
					v[pl].pop_back();
				}
				break;
			} 
		if ( i == sz )
			v[pl].push_back( make_pair(x,1) );
	}
	
	int wh(int x)
	{
		int pl = max(x,-x) % md;
		for (int i=0;i<int(v[pl].size());++i)
			if ( v[pl][i].first == x )
				return v[pl][i].second;
		return 0;
	}
};
 
myhash mp;
 
void dfs(int x)
{   
	vl += a[x]; 
	ans += mp.wh(vl-s);
 
	mp.add(vl,1);
 
    for (int i=0;i<int(v[x].size());++i)
		dfs(v[x][i]);
	
	mp.add(vl,-1);
	vl -= a[x];
}
 
int main()
{
    F>>n>>s;
    mp.add(0,1);
    for (int i=1,dd;i<=n;++i)
    {
        F>>dd>>a[i];
        if ( dd ) v[dd].push_back(i);
    }
    dfs(1);
    G<<ans<<'\n';
}
