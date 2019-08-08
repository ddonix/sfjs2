#include <iostream>
#include <map>
#include <stack>

using namespace std;

struct Mat
{
	int x;
	int y;

	Mat(){}
	Mat(int xx, int yy) : x(xx), y(yy) {}
	int mul(const Mat & a, const Mat & b)
	{
		if(a.y != b.x)
			return -1;
		else
		{
			x = a.x;
			y = b.y;
			return a.x * a.y * b.y;
		}
	}
};

int main()
{
	map<char, Mat> mat;
	int nm;
	cin>>nm;
	for(int i = 0; i < nm; i++)
	{
		char a;
		int x, y;
		cin>>a>>x>>y;
		mat[a] = Mat(x,y);
	}

	return 0;
}
