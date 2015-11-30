#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <numeric>
#include <map>
#include <set>
#include <tr1/unordered_map>
#include <tr1/unordered_set>
#include <algorithm>
#include <vector>
#include <cstring>
#include <sstream>
#include <queue>
#include <bitset>
#include <cmath>
using namespace std;
using namespace tr1;

typedef long long lng;

#define F cin
#define G cout

const int N = 100005;
const int MOD = 1000000007;
typedef long long ll;

const int P = 100; 
const int B = 11; 
const int M = 1000000007;
const int sz = 6;

struct _node {
	int a[sz],mk;
	_node()
	{
		for (int i=0;i<sz;++i)
			a[i] = 0;
		mk = 0;
	}
	_node(int k)
	{
		int x = 1;
		for (int i=0;i<sz;++i)
		{
			a[i] = x;
			x = ( 1LL * x * k ) % M;
		}
		mk = 0;
	}
	_node(int k,int mk)
	{
		int x = 1;
		for (int i=0;i<sz;++i)
		{
			a[i] = x;
			x = ( 1LL * x * k ) % M;
		}
		this->mk = mk;
	}
	_node operator + (_node y)
	{
		_node ans = _node();
		for (int i=0;i<sz;++i)
			ans.a[i] = this->a[i] + y.a[i];
		return ans;
	}
	_node operator * (int x)
	{
		_node b = _node();
		for (int i=0;i<sz;++i)
			b.a[i] = (1LL * a[i] * x) % M;
		return b;
	}
	int null()
	{
		return mk == 0;
	}
};

class seg_tree {
	private:
		int n;
		vector<_node> v;
		vector<_node> lazy;
		
		void push_up(int n,int l,int r)
		{
			if ( lazy[n].null() ) return;
			
			if ( l != r )
				lazy[n*2] = lazy[n*2+1] = lazy[n];
			v[n] = lazy[n] * (r-l+1);
			lazy[n] = _node();
		}
		
		void update(int n,int l,int r,int il,int ir,int x)
		{
			push_up(n,l,r);
			if ( ir < l || il > r ) 
				return;
			if ( il <= l && r <= ir ) 
			{
				lazy[n] = _node(x,1);
				push_up(n,l,r);
				return;
			}
			
			int m = (l + r) / 2;
			update(n*2,l,m,il,ir,x); 
			update(n*2+1,m+1,r,il,ir,x); 
			
			v[n] = v[n*2] + v[n*2+1];
		}
		
		_node query(int n,int l,int r,int il,int ir)
		{
			push_up(n,l,r);
			if ( ir < l || il > r ) 
				return _node();
			if ( il <= l && r <= ir ) 
				return v[n];
			
			int m = (l + r) / 2;
			_node ans = query(n*2,l,m,il,ir);
			ans = ans + query(n*2+1,m+1,r,il,ir); 
			
			return ans;
		}
	
	public:
		void init(int k)
		{
			n = k;
			v.resize(n<<2);
			lazy.resize(n<<2);
			for (int i=0;i<n*4;++i)
			{
				v[i] = _node();
				lazy[i] = _node();
			}
		}
		void update(int il,int ir,int x)
		{
			update(1,1,n,il,ir,x);
		}
		
		int query(int il,int ir,int k)
		{
			return query(1,1,n,il,ir).a[k];
		}
};


struct P
{
    int l,r,mid,v;
    int sum[6][6],xs[6][6];
}arr[4*N];
int a[N],C[10][10];
void down(int c)
{
    if(arr[c].v!=-1)
    {
        arr[c+c].v=arr[c+c+1].v=arr[c].v;
        for(int i=0;i<6;i++)for(int j=0;j<=i;j++)
        {
            arr[c+c].sum[i][j]=(ll)arr[c+c].xs[i][j]*arr[c+c].v%MOD;
            arr[c+c+1].sum[i][j]=(ll)arr[c+c+1].xs[i][j]*arr[c+c+1].v%MOD;
        }
        arr[c].v=-1;
    }
}
void up(int c)
{
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<=i;j++)
        {
            arr[c].sum[i][j]=(arr[c+c].sum[i][j]+arr[c+c+1].sum[i][j])%MOD;
        }
    }
}
int power(int x,int k)
{
    ll r=1;
    while(k--)r=r*x%MOD;
    return r;
}
void build(int L,int R,int c)
{
    arr[c].l=L;
    arr[c].r=R;
    arr[c].mid=(L+R)/2;
    arr[c].v=-1;
    if(L==R)
    {
        arr[c].v=a[L];
        for(int i=0;i<6;i++)
        {
            for(int j=0;j<=i;j++)
            {
                arr[c].xs[i][j]=(ll)C[i][j]*power(L,j)%MOD;
                arr[c].sum[i][j]=(ll)arr[c].xs[i][j]*arr[c].v%MOD;
            }
        }
        return ;
    }
    build(L,arr[c].mid,c+c);
    build(arr[c].mid+1,R,c+c+1);
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<=i;j++)
        {
            arr[c].xs[i][j]=(arr[c+c].xs[i][j]+arr[c+c+1].xs[i][j])%MOD;
            arr[c].sum[i][j]=(arr[c+c].sum[i][j]+arr[c+c+1].sum[i][j])%MOD;
        }
    }
}
int ret;
void cover(int L,int R,int v,int c)
{
    if(L<=arr[c].l&&R>=arr[c].r)
    {
        arr[c].v=v;
        for(int i=0;i<6;i++)
        {
            for(int j=0;j<=i;j++)arr[c].sum[i][j]=(ll)arr[c].xs[i][j]*arr[c].v%MOD;
        }
        return ;
    }
    down(c);
    if(L<=arr[c].mid)cover(L,R,v,c+c);
    if(R>arr[c].mid)cover(L,R,v,c+c+1);
    up(c);
}
void got(int L,int R,int k,int c)
{
    if(L<=arr[c].l&&R>=arr[c].r)
    {
        for(int i=0;i<=k;i++)
        {
            int tmp=(ll)arr[c].sum[k][i]*power(L-1,k-i)%MOD;
            if((k-i)%2)tmp=(MOD-tmp)%MOD;
            ret=(ret+tmp)%MOD;
        }
        return ;
    }
    down(c);
    if(L<=arr[c].mid)got(L,R,k,c+c);
    if(R>arr[c].mid)got(L,R,k,c+c+1);
    up(c);
}
char s[5];
int main()
{
    int n,m,i,j;
    for(i=0;i<10;i++)C[i][0]=C[i][i]=1;
    for(i=2;i<10;i++)for(j=1;j<i;j++)C[i][j]=C[i-1][j]+C[i-1][j-1];
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)scanf("%d",&a[i]);
    build(1,n,1);
    while(m--)
    {
        int l,r,x;
        scanf("%s%d%d%d",s,&l,&r,&x);
        if(s[0]=='=')
        {
            cover(l,r,x,1);
        }
        else
        {
            ret=0;
            got(l,r,x,1);
            printf("%d\n",ret);
        }
    }
    return 0;
}


