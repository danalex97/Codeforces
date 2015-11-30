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
   
ifstream F("valuare.in");
ofstream G("valuare.out"); 
  
typedef long long lng;
 
lng b;
int p;
  
void euclid(int a,int &x,int b,int &y,int c)
{
    if ( b == 0 )
    {
        x = 1;
        y = 0;
        return;
    }
  
    int x0 = 0, y0 = 0;
    euclid(b,x0,a%b,y0,c);
  
    x = y0;
    y = 1LL * x0 - 1LL * y0 * (a/b);
}
  
int inv(int a,int b)
{
    int c = 1; // cmmdc(a,n) = 1
    // ax + by = c
  
    int x = 0, y = 0;
    euclid(a,x,b,y,c);
  
    if ( x < 0 ) x += b;
  
    return x;
}
 
int pwr(lng a,lng b)
{
    if ( !b ) return 1;
    lng ans = pwr(a,b/2);
    ans = (ans * ans) % p;
    if ( b%2 ) ans = (ans * (a%p)) % p;
    return ans;
}
  
int form(lng b,int p)
{
    int up = ( 1LL * pwr(b,b) - 1LL * pwr(b,2) + 1LL * b - 1LL ) % p;
    up = ( up + p ) % p;
    int down = inv((b-1)%p,p);
    down = ( 1LL*down*down ) % p;
    return (1LL*up*down)%p;
}
 
int main() 
{
    ios::sync_with_stdio(0);
    F>>b>>p;
    if ( b % p == 0 )
		G<<(b-1)%p<<'\n';
	else
		G<<form(b,p)<<'\n';
}
