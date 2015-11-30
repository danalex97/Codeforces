#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#define first x
#define second y
using namespace std;
const int N = 20005;
struct point {
    int x, y, o;
};

bool cmp(point a, point b)
{
    if(a.x == b.x)
    {
        return a.y < b.y;
    }
    return a.x < b.x;
}

bool isUp(int a, int b, int c, int x, int y) {
    return a * x + b * y + c <= 0;
}

int main() {
    ios::sync_with_stdio(0);
    #ifndef ONLINE_JUDGE
        ifstream cin("p.in");
    #endif
    int c;
    cin >> c;
    int n;
    for (; c; --c)
    {
		vector<point> points;
		vector<int> sol(N);
		sol.clear();
        cin >> n;
        for (int i = 0; i < n; ++i)
        {
			point pp;
			points.push_back( pp );
            cin >> points[i].x >> points[i].y;
            points[i].o = i;
        }
        sort(points.begin(), points.end() , cmp);
        sol.push_back(points.front().o);
        int a = points.front().y - points[n - 1].y;
        int b = -points.front().x + points[n - 1].x;
        int c = points.front().x * points[n - 1].y - points[n - 1].x * points.front().y;
        for (int i = 1; i < n - 1; ++i)
        {
            if (isUp(a, b, c, points[i].x, points[i].y))
            {
               sol.push_back(points[i].o);
            }
        }

        sol.push_back(points[n - 1].o);

        for (int i = n-2; i >= 1; --i)
        {
            if (!isUp(a, b, c, points[i].x, points[i].y))
            {
               sol.push_back(points[i].o);
            }
        }
        int co = 0;
        for (vector<int>::iterator it = sol.begin(); it != sol.end(); ++it)
        {
			++co;
			
            //cout << *it << ' ';
        }
		cout<<co<<'\n';
        cout << '\n';
    }


}
