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
	Mat(int xx, int yy) : x(xx), y(yy) {}
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

map<char, Mat> mat;

void sum(string e, Mat & res)
{
	if (e.length() == 1)
	{
		if (mat.count(e[0]))
		{
			res.x = mat[e[0]].x; 
			res.y = mat[e[0]].y; 
			res.c = 0;
		}
	}
	else if (e.length() == 2)
	{
		if (mat.count(e[0]) && mat.count(e[1]))
			res.mul(mat[e[0]], mat[e[1]]);
	}
	else
	{
		Mat res1, res2;
		string s;
		string s1, s2;
		s =  e.substr(1, s.length()-2);
		if(s[0] != '(')
		{
			s1 = e.substr(0,1);
			s2 = e.substr(1, s.length()-1);
		}
		else
		{
		
		}
	}
}

int main()
{
	int nm;
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
		sum(e, res);
		if (res.c < 0)
			cout<<"error"<<endl;
		else
			cout<<res.c<<endl;
	}

	return 0;
}
