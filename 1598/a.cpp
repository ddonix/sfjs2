#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Point
{
	int x;
	int y;
};
bool cmp(const Point & a, const Point & b)
{
	return true;
}
int main()
{
	vector<Point> q;
	make_heap(q.begin(), q.end(), cmp);
}
