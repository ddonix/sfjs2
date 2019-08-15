/*uva 1599
 *
 */
#include <cstring>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

const int maxv = 100001;
const int maxe = 200000;
const int maxc = 0x7fffffff;

int n,m;
struct E
{
	int v;
	int c;
	E(int v_, int c_):v(v_), c(c_){}
};

vector<E> G[maxv];
int vis[maxv];
int inq[maxv];

void bfs1()
{
	memset(vis, 0, sizeof(vis));
	queue<int> q;
	q.push(n);
	vis[n] = 1;
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int i = 0; i < G[u].size(); i++)
		{
			int v =  G[u][i].v;
			if(!vis[v])
			{
				vis[v] = vis[u]+1;
				if (v == 1)
					return;
				q.push(v);
			}
		}
	}
}

void bfs2()
{
	memset(inq, 0, sizeof(inq));
	queue<int>q;
	if (n == 1)
	{
		printf("0\n");
		return;
	}
	
	q.push(1);
	inq[1] = 1;
	vector<int> res;
	res.resize(vis[1]-1);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		if (u == n)
			break;
		int cmin = maxc;
		for(int i = 0; i < G[u].size(); i++)
		{
			if((vis[G[u][i].v] == vis[u]-1))
				if (cmin > G[u][i].c)
					cmin = G[u][i].c;
		}
		for(int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i].v;
			if((vis[v] == vis[u]-1) &&  !inq[v] && G[u][i].v != n && (G[u][i].c == cmin))
			{
				q.push(G[u][i].v);
				inq[G[u][i].v] = 1;
			}
		}
		
		int r = vis[1]-vis[u];
		if(res[r] == 0)
			res[r] = cmin;
		else if(res[r] > cmin)
			res[r] = cmin;
	}
	for(int i = 0; i < vis[1]-2; i++)
		printf("%d ", res[i]);
	printf("%d\n", res[vis[1]-2]);
}

int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		while(m--)
		{
			int u, v, c, i, t;
			scanf("%d%d%d", &u, &v, &c);
			if (u == v)
				continue;
			G[u].push_back(E(v, c));
			G[v].push_back(E(u, c));
		}
		bfs1();
		printf("%d\n", vis[1]-1);
		bfs2();
		for(int i = 0; i < n; i++)
			G[i].clear();
	}
}
