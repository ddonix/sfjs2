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
int res[maxv];

void bfs1()
{
	memset(vis, 0, (n+1)*sizeof(int));
	queue<int> q;
	q.push(n);
	vis[n] = 1;
	while(1)
	{
		int u = q.front();
		int l = G[u].size();
		q.pop();
		for(int i = 0; i < l; i++)
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
	queue<int>q;
	q.push(1);
	
	memset(res, 0, sizeof(int)*(vis[1]-1));
	while(!q.empty())
	{
		int u = q.front();
		int l = G[u].size();
		q.pop();
		int cmin = maxc;
		for(int i = 0; i < l; i++)
			if((vis[G[u][i].v] == vis[u]-1) && (cmin > G[u][i].c))
				cmin = G[u][i].c;
		for(int i = 0; i < l; i++)
		{
			int v = G[u][i].v;
			if((vis[v] == vis[u]-1) && v != n && (G[u][i].c == cmin))
				q.push(v);
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
		if (1 == n)
			printf("0\n0\n");
		else
		{
			bfs1();
			printf("%d\n", vis[1]-1);
			bfs2();
		}
		for(int i = 1; i <= n; i++) 
			G[i].clear();
	}
}
