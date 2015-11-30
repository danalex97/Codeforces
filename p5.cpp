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
    
InputReader F("cumainilecurate.in");
ofstream G("cumainilecurate.out");
    
const int N = 100010;
//const int L = 2;
int L;
    
int a[N],n,m;
    
struct aib 
{
    int sz;
    vector<int> bst;
        
    aib(int sz)
    {
        this->sz = sz;
        for (int i=0;i<sz+5;++i)
            bst.push_back(1<<30);
    }
        
    int ask(int x)
    {
        x = sz-x+1;
        int ans = 1<<30;
        for (int i=x;i>0;i-=i&-i)
            ans = min(ans,bst[i]);
        return ans;
    }
        
    void upd(int x,int idx)
    {
        x = sz-x+1;
        for (int i=x;i<=sz;i+=i&-i)
            bst[i] = min(bst[i],idx);
    }
};
    
struct seg 
{
    vector< pair<int,int> > v;
    vector<int> ln,nxt,vl,idx;
    int l,r,sz;
        
    seg(int ll,int rr) // O(sqrt*log)
    {
        l = ll;
        r = rr;
        sz = r-l+1;
        aib idx2(sz);
        nxt.resize(sz);
        ln.resize(sz);
        idx.resize(sz);
        for (int i=0;i<sz;++i)
        {
            vl.push_back(a[l+i]);
            v.push_back( make_pair(a[l+i],l+i) );
        }
        sort(v.begin(),v.end());
        idx.push_back(1<<30);
        for (int i=sz-1;i>=0;--i)
        {
            //cerr<<v[i].second<<'\n';
            idx[i] = min(idx[i+1],v[i].second);
          
            vector<pair<int,int> >::iterator it = upper_bound( v.begin() , v.end() , make_pair(a[l+i],1<<30) );
            if ( it != v.end() )
            {
                int val = idx2.ask(it-v.begin());
                //cerr<<it->second-l+1<<' '<<val<<'\n';
                if ( val == 1<<30 )
                    nxt[i] = l+i;
                else
                    nxt[i] = val;
            }
            else
            {
                nxt[i] = l+i;
                //cerr<<"nothing\n";
            }
            int pos = lower_bound( v.begin() , v.end() , make_pair(a[l+i],l+i) ) - v.begin();
            idx2.upd( pos+1,l+i );
          
            ln[i] = ln[nxt[i]-l] + 1;
            nxt[i] = nxt[nxt[i]-l];
        }
    }
        
    void print()
    {
        cerr<<"nxt: "; for (int i=0;i<sz;++i) cerr<<nxt[i]<<' '; cerr<<'\n';
        cerr<<"ln: "; for (int i=0;i<sz;++i) cerr<<ln[i]<<' '; cerr<<'\n';
        cerr<<"vl: "; for (int i=0;i<sz;++i) cerr<<vl[i]<<' '; cerr<<'\n';
        cerr<<"idx: "; for (int i=0;i<sz;++i) cerr<<idx[i]<<' '; cerr<<'\n';
    }
        
    int ask(int x)
    {
        vector<pair<int,int> >::iterator it = upper_bound( v.begin() , v.end() , make_pair(a[x],1<<30) );
        if ( it != v.end() )
            return idx[it-v.begin()];
        else
            return -1;
    }
        
    int add(int x)
    {
        return ln[x-l];
    }
        
    int border(int x)
    {
        return nxt[x-l];
    }
};
    
vector<seg> segs;
    
int to_seg[N];
    
int solve(int x)
{
    int t = segs.size();
    int pl = to_seg[x];
    int ans = 0;
    if ( pl == -1 )
        return 0;
    else
    {
        ans += segs[pl].add(x);
        x = segs[pl].border(x);
        ++pl;
        //cerr<<x<<' ';
    }
    while ( pl < t ) 
    {
        if ( a[x] > segs[pl].v.back().first )
        {
            ++pl;
            continue;
        }
        int y = segs[pl].ask(x);
        if ( y != -1 )
        {
            x = y;
            ans += segs[pl].add(x);
            x = segs[pl].border(x);
            //cerr<<x<<' ';
        }
        ++pl;
    }
    //cerr<<'\n';
    return ans;
}
    
int main() 
{
    ios::sync_with_stdio(0);
     
    F>>n>>m;
     
    L = 300;
     
    for (int i=1;i<=n;++i)
        F>>a[i];
    int len = 0;
    for (int i=1;i<=n;++i)
    {
        to_seg[i] = segs.size();
        if ( (++len) == L || i == n )
        {
            segs.push_back( seg(i-len+1,i) );
            len = 0;
        }
    }
      
    //for (int i=1;i<=n;++i) cerr<<to_seg[i]<<' ';cerr<<'\n';      
    //for (int j=0;j<int(segs.size());++j) segs[j].print();
      
    for (int i=1,t,x,y;i<=m;++i)
    {
        F>>t;
        if ( t == 2 )
        {
            F>>x;
            G<<solve(x)<<'\n';
        }
        else
        {
            F>>x>>y;
            a[x] = y;
            int j = to_seg[x];
            segs[j] = seg(segs[j].l,segs[j].r);
            //for (int j=0;j<int(segs.size());++j)
            //    if ( segs[j].l <= x && x <= segs[j].r )
            //        segs[j] = seg(segs[j].l,segs[j].r);
        }
    }
}
