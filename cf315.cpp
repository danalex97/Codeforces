#include <iostream>
using namespace std;

#define F cin
#define G cout

const int M = 1000000007;
const int N = 4010;
int n,bell[N][N];

int main() 
{
	ios::sync_with_stdio(0);
    
    F>>n;
    bell[0][0] = 1;
    for (int i=1;i<=n;++i)
	{
		bell[i][0] = bell[i-1][i-1];
		for (int j=1;j<=i;++j)
			bell[i][j] = ( bell[i][j-1] + bell[i-1][j-1] ) % M;
	}
	G<<bell[n][n-1]<<'\n';
}
