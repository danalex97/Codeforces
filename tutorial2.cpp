#include <iostream>
#include <fstream>
#include <algorithm> 
#include <cstdio>
#include <iomanip>
#include <ctime>
#include <cstdlib>
using namespace std;

#define F cin
#define G cout
//ifstream F("p.in");

typedef long long lng;

const int K = 5010;
const int N = 100010; 
const int P = 100; 
const int B = 11; 
const int M = 1000000007;

int n,a[N],b[N];

void quickSort(int left,int right)
{
	if ( left == right )
		return; 
	
	int pivot = left + rand() % (right-left);
	
	int i2 = left;
	for (int i=left;i<=right;++i)
		if ( a[i] < a[pivot] )
			b[i2++] = a[i];
	int i3 = i2;
	for (int i=left;i<=right;++i)
		if ( a[i] == a[pivot] )
			b[i3++] = a[i];
	
	int i4 = i3;
	for (int i=left;i<=right;++i)
		if ( a[i] > a[pivot] )
			b[i4++] = a[i];
			
	for (int i=left;i<=right;++i)
		a[i] = b[i];
	
	quickSort(left,i2);
	quickSort(i3,right);
}

int kThElement(int left,int right,int k)
{
	if ( left == right )
		return left; 
	
	int pivot = left + rand() % (right-left);
	
	int kPrime = left;
	for (int i=left;i<=right;++i)
		if ( a[i] < a[pivot] )
			b[kPrime++] = a[i];
	int i3 = kPrime;
	for (int i=left;i<=right;++i)
		if ( a[i] == a[pivot] )
			b[i3++] = a[i];
	int i4 = i3;
	for (int i=left;i<=right;++i)
		if ( a[i] > a[pivot] )
			b[i4++] = a[i];
	for (int i=left;i<=right;++i)
		a[i] = b[i];
	
	if ( k < kPrime )
		return kThElement(left,kPrime-1,k);
	else
		return kThElement(kPrime,right,k-kPrime);
}

inline int maxSubBrute()
{
	int maxsum = -1000000006, sum;
	for(int i = 1; i <= n; i++) // first element
		for(int j = i; j <= n; j++) // last element
		{
			sum = 0;
			for(int k = i; j <= j; k++) // go to all elements
				sum += a[k];
			if(sum > maxsum)
				maxsum = sum;
		}
	return maxsum;
} // O(n^3)

inline int maxSubBrute2()
{
	int sum = 0, maxsum = -1000000006;
	for(int i = 1; i <= n; i++)
	{
		sum = 0;
		for(int j = i; j <= n; j++)
		{
			sum += a[j];
			if(sum > maxsum)
				maxsum = sum;
		}
	}
	return maxsum;
} // O(n^2)

inline int maxSub2()
{
	int vmin   = 0;
	int maxsum = 0;
	int sum    = 0;
	for (int i=1;i<=n;++i)
	{
		sum    = sum + a[i];
		vmin   = min(sum, vmin);
		maxsum = max(maxsum, sum - vmin); 
	}
	return maxsum;
} // O(n)

inline int maxSub()
{
	int sum = 0, maxsum = -1000000006;
	for(int i = 1; i <= n; i++)
	{
		sum += a[i];
		if(sum > maxsum)
			maxsum = sum;
		if(sum < 0)
			sum = 0;
	}
	return maxsum;
} // O(n)


int main() 
{
	ios::sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
		ifstream F("p.in");
	#endif
	
	srand(time(0));
	F>>n;
	for (int i=1;i<=n;++i)
		F>>a[i];
	quickSort(1,n);
	// sort(a+1,a+n+1);
	for (int i=1;i<=n;++i)
		G<<a[i]<<' ';
	G<<'\n';
	G << maxSubBrute() << '\n';
	G << maxSubBrute2() << '\n';
	G << maxSub() << '\n';
}
