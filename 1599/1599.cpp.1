#include <iostream>
#include <cstring>
#include <map>
#include <set>
#include <queue>


using namespace std;

const int maxv = 100001;
const int maxe = 200000;

struct V
{
	int v;
	int c;
};

map<int, int> G[maxv];
int vis[maxv];

int n;		//number of the V

int bfs1()
{
	memset(vis, 0, sizeof(vis));
	vis[1] = 0;
	queue<long long int> q;
	q.push((long long int)0 << 32 |  (long long int)1);
	while(!q.empty())
	{
		long long int p = q.front();
		q.pop();
		int u, d;
		u = p & 0xffffffff;
		d = int(p >> 32);
		
		if (u == n)
			return d;
		for(auto it = G[u].begin(); it != G[u].end(); it++)
		{
			int v = (*it).first;
			if (!vis[v])
			{
				q.push((long long int)(d+1)<<32|(long long int)v);
				vis[v] = 1;
			}
		}

	}
}

void bfs2()
{
	
}


int main()
{
	while(cin>>n)
	{
		int m;
		cin>>m;
		while(m--)
		{
			int r1, r2, c;
			cin>>r1>>r2>>c;
			if(G[r1].count(r2)<1)
				G[r1][r2]=c;
			else if(G[r1][r2] > c)
				G[r1][r2] = c;
		}
		cout<<bfs1()<<endl;
		for(int i = 0; i < n; i++)
			G[i].clear();
	}
}
