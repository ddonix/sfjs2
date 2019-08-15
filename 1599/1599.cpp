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
int vis1[maxv];
int res[maxv];
bool vis2[maxv];

void bfs1()
{
	memset(vis1, 0, (n+1)*sizeof(int));
	queue<int> q;
	q.push(n);
	vis1[n] = 1;
	while(1)
	{
		int u = q.front();
		int l = G[u].size();
		q.pop();
		for(int i = 0; i < l; i++)
		{
			int v =  G[u][i].v;
			if(!vis1[v])
			{
				vis1[v] = vis1[u]+1;
				if (v == 1)
					return;
				q.push(v);
			}
		}
	}
}

void bfs2()
{
	memset(vis2,0,n+1);
	queue<int>q;
	queue<int> t;
	q.push(1);
	for(int i = 0; i < vis1[1]-1; i++)
		res[i] = maxc;
	while(!q.empty())
	{
		int u = q.front();
		int l = G[u].size();
		q.pop();
		if (vis2[u])
			continue;
		vis2[u] = true;
		int cmin = maxc;
		for(int i = 0; i < l; i++)
			if((vis1[G[u][i].v] == vis1[u]-1) && !vis2[G[u][i].v] && (cmin > G[u][i].c))
				cmin = G[u][i].c;
		for(int i = 0; i < l; i++)
		{
			int v = G[u][i].v;
			if((vis1[v] == vis1[u]-1) && !vis2[v] && (G[u][i].c == cmin))
				q.push(v);
		}
		int r = vis1[1]-vis1[u];
		if(res[r] > cmin) res[r] = cmin;
	}
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
			bfs2();
			printf("%d\n%d", vis1[1]-1, res[0]);
			for(int i = 1; i < vis1[1]-1; i++)
				printf(" %d", res[i]);
			printf("\n");
		}
		for(int i = 1; i <= n; i++) 
			G[i].clear();
	}
}
