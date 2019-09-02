#include <iostream>
#include <string>
#include <cstring>
#include <queue>
using namespace std;

const int maxe = 30;
const int hmaxb = maxe*(maxe+2);
const int maxb = maxe*(maxe+2)/2;

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
Point be(hmaxb,hmaxb);

//p :当前位置
//st:当前走几步
//e :当前走了多少步
//s :之前路径

string dir = "nsew";
int dx[] = {0,  0, 1, -1};
int dy[] = {1, -1, 0,  0};

bool vis[maxe*(maxe+2)][maxe*(maxe+2)];

bool visit(Point p, int e, int d)
{
	int x = p.x, y=p.y;
	for(int i = 1; i <= e; i++)
	{
		if (x+i*dx[d] == be.x && y+i*dy[d] == be.y && i == e)
			return true;
		if (vis[x+i*dx[d]][y+i*dy[d]])
			return false;
	}
	for(int i = 1; i <= e; i++)
		vis[x+i*dx[d]][y+i*dy[d]] = true;
	return true;
}

void unvisit(Point p, int e, int d)
{
	int x = p.x, y=p.y;
	for(int i = 1; i <= e; i++)
		vis[x+i*dx[d]][y+i*dy[d]] = false;
}

void dfs(Point p, int e, string trace)
{
	if (p == be && e != 0)
	{
		ans.push(trace);
		return;
	}
	else
	{
		if (e == ed)
			return;
		int d1, d2;
		if (trace.empty())
		{
			d1 = 0; 
			d2 = 3;
		}
		else
		{
			if (trace.back() == 'n' || trace.back() == 's')
			{
				d1 = 2;
				d2 = 3;
			}
			else
			{
				d1 = 0;
				d2 = 1;
			}
		}
		for(int i = d1; i <= d2; i++)
		{
			if (visit(p, e+1, i))	//访问
			{
				Point np = Point(p.x + dx[i]*(e+1), p.y+dy[i]*(e+1));
				dfs(np, e+1, trace+dir[i]);
				unvisit(p, e+1, i);
			}
		}
	}
}

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>ed>>bl;
		cout<<__LINE__<<endl;
		memset(vis, 0, sizeof(vis));
		cout<<__LINE__<<endl;
		for(int i = 0; i < bl; i++)
		{
			int x,y;
			cin>>x>>y;
			cout<<be.x+x<<" "<<be.y+y<<endl;
			vis[be.x + x][be.y + y] = true;
			cout<<__LINE__<<endl;
		}
		cout<<__LINE__<<endl;

		string s = "";
		while(!ans.empty()) ans.pop();
	
		cout<<__LINE__<<endl;
		vis[be.x][be.y] = true;
		dfs(be, 0, s);
		cout<<__LINE__<<endl;
		int t = ans.size();
		while(!ans.empty())
		{
			cout<<ans.front()<<endl;
			ans.pop();
		}
		cout<<__LINE__<<endl;
		cout<<"Found "<<t<<" golygon(s)."<<endl;
		cout<<__LINE__<<endl;
		if(T)
			cout<<endl;
	}
}
