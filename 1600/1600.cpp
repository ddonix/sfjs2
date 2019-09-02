/* uva 1600:
*  题意：在一个m*n的01迷宫中，1表示障碍，0表示可通过。k表示可以连续跨越的障碍数。要求从00到
*  (m-1, n-1)的最短路径长度。
*  思路: 普通的bfs用不了了，因为可以跨越障碍，点可以从不同地方到达，相当于有多个父结点。解决
*  思路有两个。每次当前结点的下一个结点，发现经过了。如果原先经过的时候路径比现在路径要大，那么
*  更新访问信息，并且重新入队列，以便更新子结点。另一个思路是，记录每一次到达的时候，已经跨越了
*  多少个障碍，相当于可以多次进入这个结点，但是是从不同的状态进入。第一种思路比较直观，但是时间
*  开销大。submit的时候提示runtime error。第二种思路accept。
*
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;
const int maxn = 22;
const int maxstep = 1000;

int G[maxn][maxn];
int vis[maxn][maxn][maxn];
int m, n, k;

const int dx[]={1, 0, -1,  0};
const int dy[]={0, 1, 0, -1};

struct Point
{
	int x;
	int y;
	Point(){};
	Point(int x_, int y_) : x(x_), y(y_){}
	bool isValid()
	{
		return (x >= 0 && x < m && y >= 0 && y < n);
	}

	Point next(int d)
	{
		Point p(x+dx[d], y+dy[d]);
		return p;
	}
	
	bool operator==(const Point & b)
	{
		return x == b.x && y == b.y;
	}
};

int bfs()
{
	queue<pair<Point, int> >  q;
	q.push(make_pair(Point(0,0), 0));
	vis[0][0][0] = 1;
	while(!q.empty())
	{
		Point p = q.front().first;
		int d = q.front().second;
		q.pop();
		
		if ((p.x == m-1) &&  (p.y == n-1))
			return vis[m-1][n-1][0];

		for(int i = 0; i < 4; i++)
		{
			Point next = p.next(i);
			if (next.isValid())
			{
				if (!G[next.x][next.y]) 
				{
					if (!vis[next.x][next.y][0])
					{
						q.push(make_pair(next, 0));
						vis[next.x][next.y][0] = vis[p.x][p.y][d]+1;
					}
				}
				else
				{
					if ((d < k) && !vis[next.x][next.y][d+1])
					{
						q.push(make_pair(next, d+1));
						vis[next.x][next.y][d+1] = vis[p.x][p.y][d]+1;
					}
				}
			}
		}
	}
	return 0;
}

int main()
{
	int T;
	cin>>T;
	int ka = 0;
	while(T--)
	{
		ka++;
		cin>>m>>n>>k;

		for(int i = 0; i < m; i++)
			for(int j = 0; j < n; j++)
				cin>>G[i][j];
/*		if (ka == 39)
		{
		cout<<"............."<<endl;
		cout<<m<<" "<<n<<" "<<k<<endl;
		for(int i = 0; i < m; i++)
		{
			for(int j = 0; j < n; j++)
				cout<<G[i][j]<<" ";
			cout<<endl;
		}
		}*/
		cout<<bfs()-1<<endl;
		memset(vis, 0 ,sizeof(vis));
		memset(G, 0 ,sizeof(G));
	}
}
