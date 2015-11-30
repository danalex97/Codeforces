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
 
typedef long long lng; 
 
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

InputReader F("rayman.in");
ofstream G("rayman.out");

const int N = 16;
const int M = 100010;

int n,m,h[N][M],c[N][M],ct[N][N];
int len[N][M],nxt[N][M];
lng tot[N][M];

const int MH = 1000000;

struct aib {
	int bst[M*10],line;
	
	int best(int x,int y)
	{	
		if ( len[line][x] == len[line][y] ? tot[line][x] < tot[line][y] : len[line][x] > len[line][y] )
			return x;
		return y;
	}
	
	int ask(int x)
	{
		int ans = 0;
		for (int i=x;i>0;i-=i&-i)
			ans = best(ans,bst[i]);
		return ans;
	}
	
	void upd(int x,int idx)
	{
		for (int i=x;i<=MH;i+=i&-i)
			bst[i] = best(bst[i],idx);
	}
} arb[N];

void compute_nxts(int line)
{
	for (int i=m;i>=1;--i)
	{
		int hh = h[line][i];
		nxt[line][i] = arb[line].ask( hh );
		len[line][i] = 1 + len[line][ nxt[line][i] ];
		tot[line][i] = c[line][i] + tot[line][ nxt[line][i] ];
		arb[line].upd( hh,i );
	}
}

vector<pair<int,int> > cells; 
vector<int> v[MH+10]; 

int solve(vector<pair<int,int> > cells)
{
	for (int i=0;i<int(cells.size());++i)
		v[ h[cells[i].first][cells[i].second] ].push_back( cells[i].first );
	
	int lst = 0, ans = 0;
	for (int i=MH;i>=1;--i)
	{
		sort(v[i].begin(),v[i].end());
		v[i].erase( unique( v[i].begin(),v[i].end() ) , v[i].end() );
		if ( v[i].size() ) 
		{
			ans += ct[lst][v[i][0]];
			
			int t = v[i].size();
			for (int j=1;j<t;++j)
				ans += ct[v[i][j-1]][v[i][j]];
			lst = v[i][t-1];
		}
	}
	return ans;
}

int main() 
{
	F>>n>>m;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			F>>h[i][j];
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			F>>c[i][j];
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j)
			F>>ct[i][j];
	for (int i=1;i<=n;++i)
		arb[i].line = i;
	
	for (int i=1;i<=n;++i)
	{
		compute_nxts(i);
		int pl = 0;
		for (int j=1;j<=m;++j)
			pl = arb[i].best(pl,j);
		while ( pl )
		{
			cells.push_back( make_pair(i,pl) );
			pl = nxt[i][pl];
		}
	}
	
	lng a_cst = 0;
	for (int i=0;i<int(cells.size());++i)
	{
		a_cst += c[cells[i].first][cells[i].second];
		//cerr<<cells[i].first<<' '<<cells[i].second<<'\n';
	}
	G<<cells.size()<<' '<<a_cst<<" ";
	
	int ans = solve(cells);
	G<<ans<<'\n';
}


