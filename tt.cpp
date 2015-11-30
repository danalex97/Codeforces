#include <fstream>
#include <iostream>
using namespace std;

const int N = 100010;

ifstream F("p.in");
#define G cout

// to be tested 
// + lazy deletion 
// + general

struct data {
	int x;
	int is_empty;
	data()
	{
		x = 0;
		is_empty = 1;
	}
	data(int v)
	{
		x = v;
		is_empty = 0;
	}
	data operator + (data b)
	{
		if ( this->is_empty )
			return b;
		if ( b.is_empty )
			return *this;
			
		data c = data();
		c.x = this->x + b.x;
		c.is_empty = 0;
		
		return c;
	}
	void print(char ch)
	{
		cerr<<x<<ch;
	}
};

struct seg {
	data x;
	int lt,rt;
	seg *l,*r;
	
	seg(int lt,int rt)
	{
		this->lt = lt; 
		this->rt = rt; 
		x = data();
		l = r = NULL;
	}
	void update(int p,data v)
	{	
		if ( lt == rt )
		{
			x = v;
			return;
		}
	
		int md = (lt+rt)/2;
		if ( l == NULL ) l = new seg(lt,md);
		if ( r == NULL ) r = new seg(md+1,rt);
		
		if ( p <= md )
			l->update(p,v);
		else
			r->update(p,v);
		x = l->x + r->x;
	}
	data ask(int _l,int _r)
	{
		if ( _l > rt || _r < lt )
			return data();
		if ( _l <= lt && rt <= _r )
			return x;
			
		int md = (lt+rt)/2;
		
		if ( l == NULL ) l = new seg(lt,md);
		if ( r == NULL ) r = new seg(md+1,rt);
		
		return l->ask(_l,_r) + r->ask(_l,_r);
	}
	void print(int all)
	{
		if ( all )
		{
			cerr<<lt<<' '<<rt<<' ';
			x.print('\n');
		}
		
		if ( lt == rt ) 
		{
			if ( !all ) x.print(' ');
			return;
		}
	
		int md = (lt + rt)/2;
		if ( l == NULL ) l = new seg(lt,md);
		if ( r == NULL ) r = new seg(md+1,rt);
		
		l->print(all);
		r->print(all);
	}
};

int n,m;

int main()
{
	F>>n>>m;
	seg my = seg(1,n);
	for (int i=1,vl;i<=n;++i)
	{
		F>>vl;
		my.update(i,vl);
		//my.print(1); cerr<<'\n';
	}
	//my.print(1); cerr<<'\n';
	for (int i=1,t,x,y;i<=m;++i)
	{
		F>>t;
		if ( t == 1 ) // update
		{
			F>>x>>y;
			my.update(x,y);
		}
		else
		{
			F>>x>>y;
			data ans = my.ask(x,y);
			G<<ans.x<<'\n';
			//my.print(1); cerr<<'\n';
		}
	}
}
