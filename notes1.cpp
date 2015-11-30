/// Notes for Beginner Programming Competition Training - 19 Nov. 

/// Feel free to email/message for feedback. 
/// For problems to solve look at bottom.
// I will pass through language clarification only in this notes, starting to give references from the next tutorials.
// I will use // for language specific references, so the ones who know C++ please ignore // lines.

#include <iostream> 
// Includes the console input (cin) and output (cout).
// ref.: http://www.cplusplus.com/reference/iostream/
#include <fstream>
// Includes input (ifstream) and output (ofstream) file streams.
// These are used for reading/printing from/to files in a similar manner to cin/cout.

// # is used for macro definition. 
// You can think as the preprocessor replacing the line #include <iostream> with the text of the file iostream.

using namespace std;

#define F cin // This (#define) macro can be used for replacing F with cin at each apparition in the program.
// ifstream F("p.in"); // opens the file "F" for reading

#define G cout

const int N = 100010; // Constant definition, similar to Java's final.
const int P = 1000000007; 

int n,a[N],b[N];

void missingElement()
/// 1. Given the length of a permutation and n-1 of its elements, output the missing element.

/// The general method to remember from this problem is setting an invariant. (https://en.wikipedia.org/wiki/Invariant_%28mathematics%29)
/// In our case the invariant is that the sum of the elements of a permutation is 1+2+...+n = n*(n+1)/2.

/// The solutions below uses O(1) memory.
{
	F>>n;
	int invariant_sum = (n+1) * n / 2; 
	// C++ allows declaring local variables at any point and the memory is liberated afterwards
	int actual_sum = 0;
	for (int i=1;i<=n-1;++i) 
	// You can also declare local variables in for loops in first gap.
	{
		int element = 0; 
		F>>element;  
		actual_sum += element;
	}
	int ans = invariant_sum - actual_sum;
	G<<ans<<'\n';	
}

/*** 2. Logarithmic Exponentiation
 * Compute x^n modulo p where x,n < p and p is a prime number. For simplicity take p = P. (line 25)
 * 
 * The obvious bruteforce runs in O(N).
 * We will use the properties of multiplication in order to gain a faster solution. 
 * ( x ^ (2*k) ) mod p = ( (x ^ k) ^ (x ^ k) ) mod p
 * ( x ^ (2*k+1) ) mod p = ( (x ^ k) * (x ^ k) * x ) mod p
 * 
 * By approximating the number of operations we get: T(n) = c + T(n/2) = c + c + T(n/4) = ... = c log n
 * Therefore, the complexity is O(log n). 
 *                                                   
 * An important implementation detail is that x * x can exceed the integer limit, so we have to use a typecast to a bigger type.
 * 
 */

int logExp(int x,int n)
{
	if ( n == 0 )
		return 1;
	int half = logExp(x,n/2);
	half = (1LL * half * half) % P;
	// 1LL is a typecast to (long long).
	// The complier can convert automatically long long to int afterwards.
	// For type reference look here: http://www.cplusplus.com/doc/tutorial/variables/
    if ( n % 2 == 1 ) 
		half = (1LL * half * x) % P;
    return half;
}

/** 3. Binary search
 * 
 * Having a sorted array find the index of an element with a certain value.
 * 
 * Example:
 * 1 2 5 8 9 10
 * The element 8 has intex 4.
 * 
 * Fixing a range of search (left, right) we need to reduce it as much as possible.
 * At each step we will look in what part the element we search for is i.e. (left,middle-1) or (middle,right).
 * The complexity is O(log N) as we reduce the range of the search at half each time. 
 * Time analysis is similar to the previous problem.
 */

int binarySearch(int left,int right,int value)
{
    if ( left == right )
		return left;
	int middle = (left + right + 1) / 2;
	if ( a[middle] <= value )
		return binarySearch(middle,right,value);
	return binarySearch(left,middle-1,value);
}

/// As the sorts are a basic topic in computing and the O(N^2) are simple to understand I will not go through bubble sort.
/// If you are not familiar with sortings you can read about bubble and insert sort on Wiki.
/// For understanding sort there are various useful visual tools on the internet such as http://visualgo.net/sorting.html

/**
 * 4. Merge sort is a classic usage of divide et impera method. 
 * The general fact that we have to remember out of this when solving a problem is the so-called "leap of faith". 
 * Assume you have solved the problem for smaller cases and then combine the result.
 *
 * Suppose we already have an algorithm that takes two indexes in an array and sorts the numbers between them ( denote it mergeSort ).
 * Now we cut the array in two ( [left,right] -> [left,middle] , [middle+1,right] ), sort each part and combine the results.
 * 
 * Take an example of how the solution recombines as we go up the recursion stack: 
 * [6][5][3][1][7][8][2][4] 
 * 
 *  [5,6] [1,3] [7,8] [2,4]
 * 
 *   [1,3,5,6]   [2,4,7,8]
 * 
 *     [1,2,3,4,5,6,7,8]
 * 
 * From the example above you can also observe the O(N log N) time complexity as the depth of the stack is O(log N).
 * The number of elements that we take into account is constant O(N).
 * The complexity of combining two subarrays is linear proportional to the array size.
 * Therefore, the total complexity is O(N log N).
 * 
 * The advantages of merge sort over other sorts is the stability as its upper bound running time is O(N log N). 
 */

void mergeSort(int left,int right)
{
	/// stopping the algorithm
	if ( left == right )
		return;
		
	/// leap of faith
	int middle = (left + right) / 2;
	mergeSort(left,     middle);
	mergeSort(middle+1, right );
	
	/// interclass two arrays
	int i = left;
	int j = middle+1;
	int k = left;
	
	while ( i <= middle || j <= right )
		if ( j > right || ( i <= middle && a[i] < a[j] ) )
		{	
			b[k] = a[i];
			k++;
			i++;
		}
		else
		{
			b[k] = a[j];
			k++;
			j++;
		}
	for (k=left;k<=right;++k)
		a[k] = b[k];
}

/**
 * Additional problems/topics to think about:
 * 
 * 1. The product along with the sum is another invariant for the first problem. Can you find another one ?
 * 
 * 2. Why is important the number P is prime ? 
 * 
 * 3. Suppose you have an array that is strictly increasing to a point and then strictly decreasing. 
 *    Ex: 1 2 3 4 5 6 7 4 3 2 1
 *    How can you find the maximum in such an array ? 
 * 
 * 4. Suppose you want to make a similar recursive algorithm to the mergeSort but the compiler stack can take a maximum depth of one.
 *    ( I.e. You can recurse only once )
 *    How you do it ? 
 * 
 *    Hint: The complexity will be O(N sqrt N).
 * 
 * 5. Logarithmic exponetiation can be generalised. How would you use it for matrices ? Find the N-th fibonacci.
 *    Article on this topic here: http://codeforces.com/blog/entry/21189
 */

/**
 * 
 * Things to remember:
 * 1. Calculating complexity
 * 2. Recursivity + divide et impera
 * 3. Invariants
 * 
 */

int main()
{
	F>>n;
	for (int i=1;i<=n;++i)
		F>>a[i];
	mergeSort(1,n);
	for (int i=1;i<=n;++i)
		G<<a[i]<<' ';
	G<<'\n';
}
