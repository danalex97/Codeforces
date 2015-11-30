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
 
ifstream F("cclj.in");
ofstream G("cclj.out");

const int N = 510;

int t,n,m,a[N][N],l;

void up(int& x,int& y,int stop)
{
	while ( 1 )
	{
		a[x][y] = ++l;
		x += 2, y++;
		if ( x == stop ) 
		{
			a[x][y] = ++l;
			x++, y += 2;
			break;
		}
		a[x][y] = ++l;
		x -= 2, y++;
		a[x][y] = ++l;
		x ++, y -= 2;
	}
}

void down(int& x,int& y,int stop)
{
	while ( 1 )
	{
		a[x][y] = ++l;
		x -= 2, y++;
		if ( x == stop ) 
		{
			a[x][y] = ++l;
			x--, y += 2;
			break;
		}
		a[x][y] = ++l;
		x += 2, y++;
		a[x][y] = ++l;
		x --, y -= 2;
	}
}

int main() 
{
	F>>t;
	while ( t-- )
	{
		F>>n>>m;
		l = 0;
		for (int i=1;i<=max(n,m);++i)
			for (int j=1;j<=max(n,m);++j)
				a[i][j] = 0;
		
		bool flag = 0;
		if ( ( ( m % 6 == 1 || m % 6 == 2 ) && ( n % 6 != 1 && n % 6 != 2 ) ) || ( n % 6 == 3 ) )
		{
			swap(n,m);
			flag = 1;
		}
			
		int i = 1,j = 1;
		
		if ( m % 6 == 3 )
		{
			while ( j + 4 <= m )
			{
				if ( j + 4 <= m ) up(i,j,n-1);
				if ( j + 4 <= m ) down(i,j,2);
			}
			up(i,j,n);
			i -- , j -= 2 , --l;
			a[i][j] = ++l , i -= 2, j++;
			a[i][j] = ++l , i ++,j -= 2; 
			a[i][j] = ++l , i ++,j += 2; 
			a[i][j] = ++l; 
		}
		else if ( m % 6 == 0 )
		{
			m -= 3;
			while ( j + 4 <= m )
			{
				if ( j + 4 <= m ) up(i,j,n-1);
				if ( j + 4 <= m ) down(i,j,2);
			}
			up(i,j,n);
			i -- , j -= 2 , --l;
			m += 3;
			
			a[i][j] = ++l , i --,j += 2; 
			a[i][j] = ++l , i ++,j += 2; 
			a[i][j] = ++l; 
		}
		else if ( m % 6 == 4 ) 
		{
			m -= 1;
			while ( j + 4 <= m )
			{
				if ( j + 4 <= m ) up(i,j,n-1);
				if ( j + 4 <= m ) down(i,j,2);
			}
			up(i,j,n);
			i -- , j -= 2 , --l;
			m += 1;
			a[i][j] = ++l , i -= 2,j ++; 
			a[i][j] = ++l , i += 2,j ++; 
			a[i][j] = ++l; 
		}
		else if ( m % 6 == 5 )
		{
			m -= 2;
			while ( j + 4 <= m )
			{
				if ( j + 4 <= m ) up(i,j,n-1);
				if ( j + 4 <= m ) down(i,j,2);
			}
			up(i,j,n);
			i -- , j -= 2 , --l;
			m += 2;
			a[i][j] = ++l , i -= 2, j++;
			a[i][j] = ++l , i ++,j -= 2; 
			a[i][j] = ++l , i ++,j += 2; 
			a[i][j] = ++l , i -= 2, j++; 
			a[i][j] = ++l , i += 2, j++; 
			a[i][j] = ++l; 
		}
		else
			while ( j + 2 <= m )
			{
				if ( j + 2 <= m ) up(i,j,n-1);
				if ( j + 2 <= m ) down(i,j,2);
			}
	
		G<<l<<'\n';
			
		if ( flag ) 
		{
			for (int i=1;i<=m;++i)
			{
				for (int j=1;j<=n;++j)
					G<<a[j][i]<<' ';
				G<<'\n';
			}
		}
		else
			for (int i=1;i<=n;++i)
			{
				for (int j=1;j<=m;++j)
					G<<a[i][j]<<' ';
				G<<'\n';
			}
	}
}

