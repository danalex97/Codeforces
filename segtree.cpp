#include <fstream>
#include <iostream>
using namespace std;

const int N = 100010;
const int infi = 1<<30; // 2 ^ 30 

#define F cin
#define G cout

struct segTree {
	int v[N*4];
	
	void update(int n,int l,int r,int p,int vl)
	{
		if ( l == r )
		{
			v[p] = vl;
			return;
		}
		
		int m = (l + r) /2;
		if(p <= m)
			update(n*2,l,m,p,vl);
		else
			update(n*2+1,m+1,r,p,vl);
		
		v[n] = max(v[n*2],v[n*2+1]);
	}
	
	int query(int n,int l,int r,int q_left,int q_right)
	{
		if ( q_left <= l && r <= q_right )
			return v[n];
			
		int m = (l + r) /2, lt = 0, rt = 0;
		if(q_left <= m)
			lt = query(n*2,l,m,q_left,q_right);
		if(q_right > m)
			rt = query(n*2+1,m+1,r,q_left,q_right);
		
		return max(lt,rt); 
	}
};

segTree tree;
int n,m;

int main()
{
	F>>n;
	for (int i=1,x;i<=n;++i)
	{
		F>>x;
		tree.update(1,1,n,i,x);
	}
	F>>m;
	for (int i=1,l,r;i<=m;++i)
	{
		F>>l>>r;
		G<<tree.query(1,1,n,l,r)<<'\n';
	}
}
