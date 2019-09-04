#include <iostream>
#include <queue>
#include <set>
#include <cstring>
using namespace std;

const int maxn = 15;
int n, ans;

unsigned short bits[16] = {	0x1, 	0x2, 	0x4, 	0x8,
				0x10,	0x20,	0x40,	0x80,
				0x100,	0x200,	0x400,	0x800,
				0x1000,	0x2000,	0x4000, 0x8000};
unsigned short g[maxn];
unsigned short gp[maxn][maxn];
int vis[maxn];

int inline getdegree(unsigned short b)
{
	int d = 0;
	for(int i = 0; i < n; i++)
		d += (b & bits[i]) ? 1 : 0;
	return d;
}

bool isok(unsigned short b)
{
	unsigned short ng[maxn];
	int degree[maxn];
	int dcount = 0;
	
	set<int> bset;			//break set	断开点
	for(int v = 0; v < n; v++)
	{
		if (b & bits[v])
		{
			ng[v] = 0;
			degree[v] = 0;
			bset.insert(v);
		}
		else
		{
			ng[v] = g[v] & ~b;
			degree[v] = getdegree(ng[v]);
			dcount += degree[v];
			if (degree[v] > 2)	//不能有度大于2的点
				return false;
		}
	}
	//到此，所有结点的度为0,1,2.
	//判断有无环
	
	bool vis[maxn];
	memset(vis, 0, sizeof(bool)*n);
	for(int v = 0; v < n; v++)
	{
		if (degree[v] < 2)
			continue;
		if (!vis[v])
		{
			vis[v] = true;
			int j, nv1, nv2, pv, cv;
			for(j = 0; j < n && !(ng[v] & bits[j]); j++);
			nv1 = j;
			for(j += 1; j < n && !(ng[v] & bits[j]); j++);
			nv2 = j;
			
			for(int t = 0; t < 2; t++)
			{
				cv = (t ? nv1 : nv2);
				pv = v;
				vis[cv] = true;
				while(1)
				{
					int j;
					for(j = 0; j < n && !(ng[cv] & bits[j]); j++);
					if (j == pv)
						for(j = pv+1; j < n && !(ng[cv] & bits[j]); j++);
				
					if (j == n)
						break;
					if (vis[j])
						return false;
					vis[j] = true;
					pv = cv;
					cv = j;
				}
			}
		}
	}
	return (dcount + bset.size()*4 >= (n-1)*2);
}

void bfs()
{
	queue<unsigned short> q;
	q.push(0);

	while(!q.empty())
	{
		unsigned short b = q.front();
		q.pop();
		if (isok(b))
		{
			ans = 0;
			for(int i = 0; i < n; i++)
				ans += (b & bits[i]) ? 1 : 0;
			return;
		}
		int i;
		for(i = n-1; i >= 0 && !(b & bits[i]); i--);
		for(int j = i+1; j < n; j++)
		{
			unsigned short nb = b | bits[j];
			q.push(nb);
		}
	}
}

int main()
{
	int ka = 0;
	while(cin>>n && n)
	{
		for(int i = 0; i < n; i++)
			g[i] = 0;
		int a,b;
		while(cin>>a>>b && -1 != a)
		{
			g[a-1] |= bits[b-1];
			g[b-1] |= bits[a-1];
		}
		for(int v = 0; v < n; v++)
			for(int i = 0; i < n; i++)
				gp[v][i] = ((i == v) ? 0 : (g[i] & ~bits[v]));
		
		memset(vis, 0, sizeof(bool)*n);
		ans = maxn;
		bfs();
		cout<<"Set "<<++ka<<": Minimum links to open is "<<ans<<endl;
	}
}
