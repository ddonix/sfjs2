#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int maxrc = 16;
int r, c;
string ans;
int l;		//l = ans.length()

char maze[maxrc][maxrc];
int  con[maxrc][maxrc];

bool vis[maxrc][maxrc];

int dx[4] = {-1, 1,  0, 0};
int dy[4] = { 0, 0, -1, 1};

void prep()
{
	for(int i = 0; i < r; i++)
		for(int j = 0; j < c; j++)
		{
			con[i][j] = ('#' == maze[i][j]) ? 0 : -1;
			vis[i][j] = false;
		}
	for(int i = 0; i < r; i++)
		for(int j = 0; j < c; j++)
		{
			if (con[i][j] < 0)
			{
				vis[i][j] = true;
				con[i][j] = 1;
				queue<int> q;
				q.push(i*c+j);
				while(!q.empty())
				{
					int x = q.front()/c, y = q.front()%c;
					q.pop();
					for(int k = 0; k < 4; k++)
					{
						int nx = x+dx[k], ny = y + dy[k];
						if (nx >= 0 && nx < r && ny >= 0 && ny < c 
									&& ('#' != maze[nx][ny]) && !vis[nx][ny])
						{
							con[i][j]++;
							vis[nx][ny] = true;
							q.push(nx*c+ny);
						}
					}
				}
				for(int i1 = 0; i1 < r; i1++)
					for(int j1 = 0; j1 < c; j1++)
					{
						if (vis[i1][j1])
						{
							vis[i1][j1] = false;
							con[i1][j1] = con[i][j];
						}
					}
			}
		}
}

void dfs(int d, string a, int x, int y)
{
	d++;
	a += maze[x][y];
	if (d > l)
	{
		l = d;
		ans = a;
	}
	else if (d == l && (ans < a))
		ans = a;

	for(int i = 0; i < 4; i++)
	{
		int nx = x + dx[i], ny = y + dy[i];
		if (nx >= 0 && nx < r && ny >= 0 && ny < c && ('#' != maze[nx][ny]) && !vis[nx][ny])
		{
			vis[nx][ny] = true;
			dfs(d, a, nx, ny);
			vis[nx][ny] = false;
		}
	}
}

int main()
{
	while(cin>>r>>c && r)
	{
		for(int i = 0; i < r; i++)
			cin>>maze[i];
		l = 0;
		ans = "";
		prep();
		for(int i = 0; i < r; i++)
			for(int j = 0; j < c; j++)
				if (con[i][j] > 0 && con[i][j] >= l)
				{
					cout<<con[i][j]<<endl;
					memset(vis, 0, sizeof(vis));
					vis[i][j] = true;
					dfs(0, "", i, j);
				}
		cout<<ans<<endl;
	}
}
