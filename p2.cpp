#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <numeric>
#include <map>
#include <tr1/unordered_map>
#include <set>
#include <tr1/unordered_set>
#include <algorithm>
#include <vector>
#include <cstring>
#include <sstream>
#include <queue>
#include <bitset>
#include <cmath>
using namespace std;
 
class InputReader {
    public:
        InputReader() {}
        InputReader(const char *file_name) {
            input_file = fopen(file_name, "r");
            cursor = 0;
            fread(buffer, SIZE, 1, input_file);
        }
        inline InputReader &operator >>(int &n) {
            while(buffer[cursor] < '0' || buffer[cursor] > '9') {
                advance();
            }
            n = 0;
            while('0' <= buffer[cursor] && buffer[cursor] <= '9') {
                n = n * 10 + buffer[cursor] - '0';
                advance();
            }
            return *this;
        }
    private:
        FILE *input_file;
        static const int SIZE = 1 << 17;
        int cursor;
        char buffer[SIZE];
        inline void advance() {
            ++ cursor;
            if(cursor == SIZE) {
                cursor = 0;
                fread(buffer, SIZE, 1, input_file);
            }
        }
};

InputReader F("vagoane.in");
ofstream G("vagoane.out");

typedef long long lng;

const int K = 500010;
const int N = 200010; 
const int P = 100; 
const int B = 11; 
const int M = 1000000007;

int n,m,c;
vector<pair<int,int> > v,w;

bool cmp(pair<int,int> x,pair<int,int> y)
{
	return x.first == y.first ? x.second > y.second : x.first < y.first;
}

bool in(pair<int,int> x,pair<int,int> y)
{
	return x.first >= y.first && x.second <= y.second;
}

int fact[K];
int inv[K];

int pwr(int x,int y)
{
	if ( y == 0 ) return 1;
	int h = pwr(x,y/2);
	h = (1LL * h * h) % M;
	if ( y%2 ) h = (1LL * h * x) % M;
	return h; 
}

int main() 
{
	F>>n>>m>>c;
	for (int i=1,x,y;i<=m;++i)
	{
		F>>x>>y;
		if ( y-x+1 > c ) 
		{
			G<<"0\n";
			return 0;
		}
		v.push_back( make_pair(x,y) );
	} 
	
	if ( v.empty() )
	{
		G<<pwr(c,n)<<'\n';
		return 0;
	}
	
	sort(v.begin(),v.end(),cmp);
	w.push_back( v[0] );
	for (int i=1;i<int(v.size());++i)
		if ( !in(v[i],w.back()) )
			w.push_back( v[i] );
	v = w;
	if ( v.begin()->first != 1 ) v.insert(v.begin(),make_pair(1,1));
	if ( v.back().second != n ) v.push_back(make_pair(n,n));
	
	fact[0] = 1;
	for (int i=1;i<=c;++i)
		fact[i] = ( 1LL * fact[i-1] * i ) % M;
	inv[c] = pwr(fact[c],M-2);
	for (int i=c-1;i>=0;--i)
		inv[i] = ( 1LL * inv[i+1] * (i+1) ) % M;
	//cerr<<inv[1]<<'\n';
	
	int last = 0 , ans = 1;
	for (int i=0;i<int(v.size());++i)
	{
		int lt = v[i].first;
		int rt = v[i].second;
		
		int cl = c-max(0,last-lt+1);
		int ln = rt - max(last+1,lt) + 1;
		//cerr<<lt<<' '<<rt<<' '<<cl<<' '<<ln<<'\n';
		if ( cl-ln < 0 )
		{
			G<<"0\n";
			return 0;
		} 
		int mul = (1LL*fact[cl]*inv[cl-ln]) % M;
		ans = (1LL*ans*mul) % M;
		last = max(last,v[i].second);
	
		if ( i ) // jump
			if ( v[i].first > v[i-1].second )
				ans = (1LL*ans*pwr(c,v[i].first-v[i-1].second-1)) % M;
	}
	G<<ans<<'\n';
}


