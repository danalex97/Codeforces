#include <fstream>
#include <iostream>
using namespace std;

const int N = 1000010;

class InputReader {
    public:
        InputReader() {}
        InputReader(const char *file_name) {
            input_file = fopen(file_name, "r");
            cursor = 0;
            fread(buffer, SIZE, 1, input_file);
        }
        inline InputReader &operator >>(int &n) {
            while(buffer[cursor] < '0' || buffer[cursor] > '9') {
                advance();
            }
            n = 0;
            while('0' <= buffer[cursor] && buffer[cursor] <= '9') {
                n = n * 10 + buffer[cursor] - '0';
                advance();
            }
            return *this;
        }
    private:
        FILE *input_file;
        static const int SIZE = 1 << 17;
        int cursor;
        char buffer[SIZE];
        inline void advance() {
            ++ cursor;
            if(cursor == SIZE) {
                cursor = 0;
                fread(buffer, SIZE, 1, input_file);
            }
        }
};

InputReader F("permsplit.in");
ofstream G("permsplit.out");

int n,sz,a[N],b[N],p[N],ans[N],cc;

int main()
{
	F>>n;
	for (int i=1,x;i<=n;++i)
	{
		F>>x;
		a[++sz] = x;
		b[sz] = x;
		p[sz] = i;
		while ( ( b[sz-1] + 1 == a[sz] || b[sz] + 1 == a[sz-1] ) && sz > 1 )
		{
			ans[++cc] = p[sz] - 1;
			a[sz-1] = min(a[sz-1],a[sz]);
			b[sz-1] = max(b[sz-1],b[sz]);
			sz--;
		}
	}
	if ( cc == n-1 )
		for (int i=n-1;i>0;--i)
			G<<ans[i]<<' ';
	else
		G<<"-1\n";
}
