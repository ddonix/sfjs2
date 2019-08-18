/* uva 1600:
*  思路：关键是如何确定下个结点。如果可以跨越障碍物，那么就可以拐弯了。先横着走，再竖着走。
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
