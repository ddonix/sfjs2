/* uva 1604: 
 * 	分析：迷宫共有9*pow(6,8)=15116544种状态.
 * 	思路：双向bfs。判重麻烦一点，状态集太大了.
 * 
 */
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

//wr 0 wb 1
//rw 2 rb 3
//bw 4 br 5
int ds[6][2] = {{2, 5}, {4, 3}, {0, 4}, {5, 1}, {1, 2}, {3, 0}};
int dx[] = {-1, 1,  0, 0};
int dy[] = { 0, 0, -1, 1};
int base[9];

int vis[15116544];

int ed[3][3];
struct State
{
	int p[3][3];
	int x,y;
	
	int code;
	State(){}

	State news(int d)
	{
		State ns;
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
				ns.p[i][j] = p[i][j];
		ns.x += dx[d];
		ns.y += dy[d];
		ns.p[ns.x][ns.y] = 6;
		ns.p[x][y] = ds[p[ns.x][ns.y]][d/2];
		ns.gencode();
	}

	bool isok()
	{
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
			      if((p[i][j]>>1) != ed[i][j])
				       return false;
		return true;
	}
	
	void gencode()
	{
		int b = 0;
		code = base[8]*(3*x+y);
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
			{
				if (i == x && j == y)
					continue;
				code += p[i][j]*base[b++];
			}
	}
	
	State(int x_, int y_)
	{
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
				p[i][j] = 0;
		x = x_;
		y = y_;
		p[x][y] = 6;
		code = base[8]*(3*x+y);
	}

	State(int c)
	{
		int e = c/base[8];
		code = c;
		c = c%base[8];
		x = e/3;
		y = e%3;
		int b = 7;
		for(int i = 2; i >= 0; i--)
			for(int j = 2; j >= 0; j--)
			{
				if (i == x && j == y)
					continue;
				p[i][j] = c/base[b];
				c = c%base[b];
				b--;
			}
	}
		
};

State be;

void initialize()
{
	int b = 1;
	for(int i = 0; i < 9; i++)
	{
		base[i] = b;
		b = b*6;
	}
}

int bfs()
{
	queue<int> q;
	q.push(be.code);
	vis[be.code] = 1;

	while(!q.empty())
	{
		State s = State(q.front());
		q.pop();

		if (s.isok())
			return vis[s.code]-1;

		if (vis[s.code] > 30)
			return -1;

		for(int d = 0; d < 4; d++)
		{
			if (s.x+dx[d] < 0 || s.x+dx[d] > 2 || s.y+dy[d] < 0 || s.y+dy[d] > 2)
				continue;
			State ns = s.news(d);
			if (!vis[ns.code])
			{
				vis[ns.code] = vis[s.code]+1;
				q.push(ns.code);
			}
		}
	}
	return -1;
}

int main()
{
	int x,y,r;
	initialize();
	while(cin>>y>>x && x)
	{
		be = State(x-1, y-1);
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
			{
				char c;
				cin>>c;
				if ('W' == c)
					ed[i][j] =  0;
				else if ('R' == c)
					ed[i][j] =  1;
				else if ('B' == c)
					ed[i][j] =  2;
				else
					ed[i][j] =  3;
			}

		memset(vis, 0, sizeof(vis));
		r = bfs();
		cout<<r<<endl;
	}
}
