#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include <set>
using namespace std;

int tt;
string a,b;

ifstream F("twosets.in");
ofstream G("twosets.out");

const int sz = 1;

int md[] = { 1000007 , 100003 };

struct myhash {
	int x[sz];
	myhash()
	{
		memset(x,0,sizeof(x));
	}
	void insert(int y,int bs)
	{
		for (int i=0;i<sz;++i)
			x[i] = ( x[i] * bs + y ) % md[i];
	}
};


struct mycmp {
	bool operator() (const myhash& a,const myhash& b) const
	{
		for (int i=0;i<sz;++i)
			if ( a.x[i] != b.x[i] )
				return a.x[i] < b.x[i];
		return 0;
	}
};

typedef set<myhash,mycmp> myset;

myset get_set(string s,int bs)
{
	myset st;
	vector<myhash> stk;
	stk.push_back( myhash() );
	for (int i=0;i<int(s.size());++i)
	{
		if ( s[i] == 'i' )
		{
			++i;
			myhash now = stk.back();
			now.insert( int(s[i]-'0') , bs );
			stk.push_back( now );
			continue;
		}
		if ( s[i] == 'd' )
		{
			stk.pop_back();
			continue;
		} 
		if ( s[i] == 't' )
		{
			st.insert( stk.back() );
			continue;
		}
	}	
	return st;
}

int main()
{
	F>>tt;
	while ( tt-- )
	{
		F>>a>>b;
		myset s1 = get_set(a,2);
		myset s2 = get_set(b,10);
		for (myset::iterator it = s1.begin();it != s1.end();++it)
			if ( s2.find(*it) != s2.end() )
				s2.erase(*it);
		G<<s2.empty()<<'\n';
	}
}


