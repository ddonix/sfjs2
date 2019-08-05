#include <iostream>
#include <queue>
#include <map>
#include <vector>

using namespace std;

struct Point
{
	int x;
	int y;
	bool operator<(const Point & right)
	{
		return true;
	}
	
	bool operator>(const Point & right)
	{
		return true;
	}
};
bool cmp(const Point & a, const Point & b)
{
	return true;
}
int main()
{
	map<int , Point> q;
	make_heap(q.begin(), q.end());
}
