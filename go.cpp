#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

#define ONLINE_JUDGE

#define F cin
#define G cout

const int N = 20010;

int m,s,c,a[N],b[N];

int main()
{
	#ifdef ONLINE_JUDGE
		ifstream F("barnrepair.in");
		ofstream G("barnrepair.out");
	#endif

	F>>m>>s>>c;
	for (int i=1;i<=c;++i)
		F>>a[i];
	sort(a+1,a+c+1);
	
	int tot = a[c]-a[1]+1;
	for (int i=1;i<c;++i)
		b[i] = a[i]-a[i+1]+1; // nr. de spatii libere inversate
		
	sort(b+1,b+c);
	for (int i=1;i<m;++i)
		tot += b[i];
	G<<tot<<'\n';
}
