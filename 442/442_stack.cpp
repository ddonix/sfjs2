#include <iostream>
#include <map>
#include <stack>
#include <string>

using namespace std;

struct Mat
{
	int x;
	int y;

	int c;

	Mat():x(-1), y(0), c(-1) {}
	Mat(int xx, int yy) : x(xx), y(yy), c(0) {}
	bool mul(const Mat & a, const Mat & b)
	{
		if(a.y != b.x)
		{
			c = -1;
			return false;
		}
		else
		{
			x = a.x;
			y = b.y;
			c = a.x * a.y * b.y + a.c + b.c;
			return true;
		}
	}
};


int main()
{
	int nm;
	map<char, Mat> mat;
	cin>>nm;
	for(int i = 0; i < nm; i++)
	{
		char a;
		int x, y;
		cin>>a>>x>>y;
		mat[a] = Mat(x,y);
	}
	string e;
	while(cin>>e && e != "")
	{
		Mat res;
		stack<Mat> sta;
		if (e.length() == 1)
		{
			if (mat.count(e[0]))
				res.c = 0;
		}
		else if (e.length() == 2)
		{
			if (mat.count(e[0]) && mat.count(e[1]))
				res.mul(mat[e[0]], mat[e[1]]);
		}
		else
		{
			int i;
			for(i = 0; i < e.length(); i++)
			{
				if (e[i] == '(')
					continue;
				if (e[i] == ')')
				{
					Mat m1,m2, m;
					m2 = sta.top();
					sta.pop();
					m1 = sta.top();
					sta.pop();
					m.mul(m1, m2);
					sta.push(m);
				}
				else
				{
					if (mat.count(e[i]))
						sta.push(mat[e[i]]);
					else
						break;
				}
			}
			if (i == e.length())
			{
				res = sta.top();
			}
		}
		if (res.c < 0)
			cout<<"error"<<endl;
		else
			cout<<res.c<<endl;
	}

	return 0;
}
