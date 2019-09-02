#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

const int maxn = 21;

bool G[maxn][maxn];
bool vis[maxn];
bool con[maxn];

int n;

int ed;
queue<deque<int> > ans;

//判断连通性
bool bfs()
{
	memset(con, 0, sizeof(con));
	queue<int> q;
	q.push(1);
	con[1] = true;
	while(!q.empty())
	{
		int v = q.front();
		q.pop();

		for(int i = 1; i <=n; i++)
			if (!con[i] && G[v][i])
			{
				con[i] = true;
				q.push(i);
			}
	}
	return con[ed];
}

//求解所有路径
void dfs(int v, deque<int> & q)
{
	if (v == ed)
	{
		ans.push(q);
		return;
	}
	for(int i = 2; i <= n; i++)
	{
		if (!vis[i] && con[i] && G[v][i])
		{
			q.push_back(i);
			vis[i] = true;
			dfs(i, q);
			vis[i] = false;
			q.pop_back();
		}
	}
}


int main()
{
	int ka = 0;
	while(cin>>ed)
	{
		int v1, v2;
		memset(G, 0, sizeof(G));
		n = 0;
		while(cin>>v1>>v2 && v1)
		{
			G[v1][v2] = true;
			G[v2][v1] = true;
			n = v1 > n ? v1 : n;
			n = v2 > n ? v2 : n;
		}

		cout<<"CASE "<<++ka<<":"<<endl;
		if (!bfs())
			cout<<"There are "<<0<<" routes from the firestation to streetcorner "<<ed<<"."<<endl;
		else
		{
			while(!ans.empty()) ans.pop();
			deque<int> q;
			q.push_back(1);
			vis[1] = true;
			
			memset(vis, 0, sizeof(vis));
			dfs(1, q);
			int r = ans.size();
			while(!ans.empty())
			{
				deque<int> & q = ans.front();
				cout<<q.front();
				q.pop_front();
				while(!q.empty())
				{
					cout<<" "<<q.front();
					q.pop_front();
				}
				cout<<endl;
				ans.pop();
			}
			cout<<"There are "<<r<<" routes from the firestation to streetcorner "<<ed<<"."<<endl;
		}
	}
}
