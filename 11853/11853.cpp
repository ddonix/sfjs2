/* uva 11853:Paintball
* 思路：如果障碍物隔绝了南北，那么不能从东到西。
* 反之如果不能从东到西，则隔绝了南北。
* 对攻击范围达到北边界的所有敌人，分别作dfs或者bfs，看看能否到达南边界。
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 1000;
struct Oppo
{
	double x,y;
	double r;
	double t;
	double rr;
	bool ne;	//含北界
	bool se;	//含南界
	Oppo(){};
	Oppo(double x1, double y1, double r1):x(x1), y(y1), r(r1)
	{
		t = x*x+y*y;
		rr = r*r;
		ne = (y+r) >= 1000 ? true : false;
		se = r >= y? true : false;
		ws = es = -1;	//如果接触东西界，南边的接触点y轴值
	}
	
	double ws;
	double es;
	void cws()
	{
		ws = y - pow((rr-x*x), 0.5);
	}
	void ces()
	{
		es = y - pow((rr-(1000-x)*(1000-x)), 0.5);
	}
	bool isCon(const Oppo & b) const
	{
		return (t+b.t) <= (rr+b.rr+2*(r*b.r+x*b.x+y*b.y)) ? true : false;
	}
};

int n;
Oppo oppo[maxn];
int G[maxn][maxn];
bool vis[maxn];

bool cmp_w(int u, int v)
{
	return  oppo[u].ws <= oppo[v].ws; 
}

bool cmp_e(int u, int v)
{
	return  oppo[u].es <= oppo[v].es;
}

//能否到南界
bool dfs(int u, bool s)
{
	if((s && oppo[u].se) || (!s && oppo[u].ne))
		return true;
	for(int i = 0; i < n; i++)
	{
		if(!vis[i])	//!vis[i]  ==> i != u
		{
			if (!G[u][i])
				G[u][i] = G[i][u] = (oppo[u].isCon(oppo[i]) ? 1 : -1);
			if (1 == G[u][i])
			{
				vis[i] = 1;
				if(dfs(i, s))
					return true;
			}
		}
	}
	return false;
}

int main()
{
	while(scanf("%d", &n)==1)
	{
		double x,y,r;
		bool nsc;	//north south connect
		for(int i = 0; i < n; i++)
		{
			scanf("%lf%lf%lf", &x, &y, &r);
			oppo[i] = Oppo(x, y, r);
		}
		nsc = false;
		
		memset(vis, 0, n*sizeof(int));
		for(int i = 0; i < n; i++)
			memset(G[i], 0, sizeof(int)*n);
		
		for(int i = 0; i < n; i++)
		{
			if (!vis[i] && oppo[i].ne)
			{
				vis[i] = 1;
				if (nsc = dfs(i, true))
					break;
			}
		}
		if(nsc)
			printf("IMPOSSBILE\n");
		else
		{
			vector<int> w, e;
			double wn=1000, en=1000;
			for(int i = 0; i < n; i++)
			{
				if(oppo[i].r >= oppo[i].x)
				{
					oppo[i].cws();
					w.push_back(i);
				}
				else if(oppo[i].r >= (1000-oppo[i].x))
				{
					oppo[i].ces();
					e.push_back(i);
				}
			}
			sort(w.begin(), w.end(), cmp_w);
			sort(e.begin(), e.end(), cmp_e);
			memset(vis, 0, sizeof(n)*n);
			for(auto it = w.begin(); it != w.end(); it++)
			{
				if (dfs(*it, false))
				{
					wn = oppo[*it].ws;
					break;
				}
			}
			memset(vis, 0, sizeof(n)*n);
			for(auto it = e.begin(); it != e.end(); it++)
			{
				if (dfs(*it, false))
				{
					en = oppo[*it].es;
					break;
				}
			}
			printf("%.2lf %.2lf %.2lf %.2lf\n", 0.0, wn, 1000.0, en);
		}
	}
}
