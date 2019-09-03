#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <set>
using namespace std;

const int maxe = 21;

int ed;
int bl;

struct Point
{
	int x;
	int y;
	Point() {}
	Point(int x_, int y_) : x(x_), y(y_) {}
	bool operator<(const Point & b) const
	{
		return (x < b.x) || (x == b.x && y < b.y);
	}
	
	bool operator==(const Point & b) const
	{
		return (x == b.x) && (y == b.y);
	}
};

queue<string> ans;
Point be(0,0);


string dir = "ensw";
int dx[] = {1, 0,  0, -1};
int dy[] = {0, 1, -1,  0};

set<Point> block;
set<Point> vis;

//p:	当前位置
//e:	当前走了多少步
//true:	之前路径
void dfs(Point p, int e, string trace)
{
	if (e == ed)
	{
		if (p == be)
			ans.push(trace);
		return;
	}
	else
	{
		int x = p.x > 0 ? p.x : -p.x;
		int y = p.y > 0 ? p.y : -p.y;
		if ((ed-e)*ed < x || (ed-e)*ed < y)
			return;

		bool df[4] = {true, true, true, true};
		if (!trace.empty())
		{
			if (trace.back() == 'n' || trace.back() == 's')
				df[1] = df[2] = false;
			else
				df[0] = df[3] = false;
		}
		for(int i = 0; i < 4; i++)
		{
			if (!df[i]) 
				continue;
			Point np = Point(p.x + dx[i]*(e+1), p.y+dy[i]*(e+1));
			if (vis.count(np) && !(np == be && (e+1) == ed))
				continue;
			int j;
			for(j = 1; j <= (e+1) && !block.count(Point(p.x+dx[i]*j, p.y+dy[i]*j)); j++);
			if (j <= (e+1))
				continue;

			auto r = vis.insert(np);
			string nt = trace+dir[i];
			dfs(np, e+1, nt);
			if (r.second)
				vis.erase(r.first);
		}
	}
}

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		block.clear();
		vis.clear();
		
		vis.insert(be);
		cin>>ed>>bl;
		for(int i = 0; i < bl; i++)
		{
			int x,y;
			cin>>x>>y;
			block.insert(Point(x,y));
		}

		if (!(ed == 7 || ed == 8 || ed == 15 || ed == 16))
			cout<<"Found "<<0<<" golygon(s)."<<endl;
		else
		{
			string s = "";
			while(!ans.empty()) ans.pop();
	
			dfs(be, 0, s);
			int t = ans.size();
			while(!ans.empty())
			{
				cout<<ans.front()<<endl;
				ans.pop();
			}
			cout<<"Found "<<t<<" golygon(s)."<<endl;
		}
		if(T)
			cout<<endl;
	}
}
