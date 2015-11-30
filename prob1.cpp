#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

//#define F cin
ifstream F("p.in");
#define G cout

const int N = 100010;
const int P = 1000000007;

int n,s,a,b,v[N];

// 5 7 3 8 6

bool is_sorted(vector<int> v)
{
	for (int i=0;i<int(v.size())-1;++i)
		if ( v[i] > v[i+1] )
			return false;
	return true;
}

void sort1(vector<int> v) 
{
	while ( !is_sorted(v) )
	{
		for (int i=0;i<int(v.size())-1;++i)
			if ( v[i] > v[i+1] )
				swap(v[i],v[i+1]);
	}
}

int v2[N];

void mergeSort(int l,int r)
{
	if ( l == r )
		return;
		
	int m = (l + r) / 2;
	mergeSort(l,m);
	mergeSort(m+1,r);
	
	int i1=l;
	int i2=m+1;
	int now = 1;
	while ( i1<=m || i2<=r )
		if ( i1 <= m && i2 <= n )
		{
			if ( v[i1] < v[i2] )
				v2[now++] = v[i1++];
			else
				v2[now++] = v[i2++];
		} 
		else
			if ( i1 <= m )
				v2[now++] = v[i1++];
			else
				if ( i2 <= n)
					v2[now++] = v[i2++];	
	
	for (int i=l,i2=1;i<=r;++i,++i2)
		v[i] = v2[i2];
}

void sorting() 
{
	F>>n;
	for (int i=1;i<=n;++i)
	{
		F>>v[i];
	}
	mergeSort(1,n);
}

void problem1()
{
	F>>n;
	s = (n+1) * n / 2;
	for (int i=1;i<=n-1;++i)
	{
		F>>a;
		s -= a;
	}
	s += n;
	G<<s<<'\n';	
}

int pwr(int a,int b)
{
	if ( b == 0 )
		return 1;
	int h = pwr(a,b/2);
	h = (1LL * h * h) % P;
    if ( b % 2 == 1 ) 
		h = (h * a) % P;
    return h;
}

void problem3()
{
	F>>a>>b;
	G<<pwr(a,b)<<'\n'; 
}

int bs(int l,int r,int x)
{
    if ( l == r )
		return l;
	int m = (l + r + 1) / 2;
	if ( v[m] <= x )
		return bs(m,r,x);
	return bs(l,m-1,x);
}

void problem2()
{
	F>>n;
	for (int i=1;i<=n;++i)
		F>>v[i];
	int x = 0;
	F>>x; 
	
	sort(v+1,v+n+1);
	
	G<<bs(1,n,x)<<'\n';
}

int main()
{
	problem1();
	problem2();
	problem3();
	sorting();
}
