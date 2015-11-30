#include <iostream>
//#include <iomanip>
//#include <cmath>
using namespace std;

// int(32 biti cu semn) : [-2^31,2^31)
// long long(64 biti cu semn) : [-2^63,2^63)
// unsigned int(32 biti fara semn) : [0,2^32)
// unsigned long long(64 ..) : [0,2^64)

// char : [0,255] 

char a = 'a';
char b = 97;

// float - precizie de 6 zecimale
// double - precizie de 12 zecimale
// bool - True/False , 0/1

void operators()
{
	cout<<int(a)<<b<<'\n';
	//cout<<fixed<<setprecision(6)<<sqrt(2)<<'\n';
	
	bool x = 1, y = 0;
	cout<<(x && y)<<'\n';  
	cout<<(x || y)<<'\n';  
	cout<<(x + y)<<'\n'; // + , - , / , *
	cout<<(x & y)<<'\n'; // 1101(2) & 101(2) = 101(2) 
	cout<<(x | y)<<'\n'; // 1101(2) & 110(2) = 1111(2) 
	cout<<(x ^ y)<<'\n'; // 1101(2) & 110(2) = 1101(2) 
	// 1 ^ 1 = 0
	// 1 ^ 0 = 1
	// 0 ^ 1 = 1
	// 0 ^ 0 = 0
	cout<<(256>>2)<<'\n';
	cout<<(1<<8)<<'\n';
}

int sqr(int x)
{
	return x*x;
}

int fact(int x)
{
	int rez = 1;
	for (int i=1;i<=x;++i)
		rez *= i;
	return rez;
}

int fact2(int x)// fact2(5) -> fact2(4) -> .. -> fact2(1) -> fact2(2) -> .. -> fact2(5)
{
	if ( x <= 1 ) 
		return 1;
	else
		return x * fact2(x-1);
}

int a2(int);
int a3(int);

int a2(int x)
{
	if ( x > 0 ) 
		return (x+1)*a3(x-1); 
	return 1;
}

int a3(int x)
{
	if ( x > 0 ) 
		return x*a2(x-1); 
	return 1;
}

int main()
{
	// if , while , for
	for (int i=1;i<=20;++i)
	{
		if ( i == 5 ) continue; // sare peste un pas in cel mai din interior for
		cout<<i<<' ';
	}
	cout<<'\n';
	for (int i=1;i<=20;++i)
	{
		if ( i == 5 ) break; // opreste cel mai din interior for
		cout<<i<<' ';
	}
	cout<<'\n';
	
	#define sqr(x) (x*x)
	cout<<sqr(5)<<'\n';
	#undef sqr
	
	//cout<<sqr(5)<<'\n';
	
	//#if
	//#elif // elseif
	//#else
	//#endif
	
	 
}
