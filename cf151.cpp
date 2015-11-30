#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <deque>
using namespace std;

const int N = 100010;

#define F cin
#define G cout

int n, m, x, y;
string s[N];
vector<int> v[N];
vector<int> q[N];
vector<int> an[N];
int ans[111111];

deque<set<string>*>* dfs(int j) 
{
    deque<set<string>*>* d = new deque<set<string>*>;
    d->push_back(new set<string>() );
    for (int k=0;k<int(v[j].size());++k) 
    {
        deque<set<string>*>* d1 = dfs(v[j][k]);
        d1->push_front(new set<string>);
        if ( d1->size() > d->size() ) 
			swap(d1, d);
        for (int i=1;i<int(d1->size());++i) 
            if ( (*d)[i]->size() > (*d1)[i]->size() ) 
				(*d)[i]->insert( (*d1)[i]->begin(), (*d1)[i]->end());
            else 
			{
				(*d1)[i]->insert((*d)[i]->begin(), (*d)[i]->end());
				(*d)[i] = (*d1)[i];
			}
    }
    (*d)[0]->insert(s[j]);
    for (int i=0; i<int(q[j].size());++i)
        if ( int(d->size()) > q[j][i] )
			ans[an[j][i]] = (*d)[q[j][i]]->size();
        else 
			ans[an[j][i]] = 0;
    return d;
}

int main()
{
	ios::sync_with_stdio(0);
	#ifndef	ONLINE_JUDGE
		ifstream F("p.in");
	#endif
    F>>n;
    for (int i=1;i<=n;++i) 
	{
		F>>s[i]>>x; 
		v[x].push_back(i);
    }
    F>>m;
    for (int i=1;i<=m;++i) 
    {
		F>>x>>y;
		q[x].push_back(y);
		an[x].push_back(i);
    }
    dfs(0);
    for (int i=1;i<=m;++i) 
		G<<ans[i]<<'\n';
}
