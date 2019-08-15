/* uva 11853:Paintball
* 思路：如果障碍物隔绝了南北，那么不能从东到西。
* 反之如果不能从东到西，则隔绝了南北。
* 对攻击范围达到北边界的所有敌人，分别作dfs或者bfs，看看能否到达南边界。
*/
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

const int maxn = 1001;
struct Oppo
{
	double x,y;
	double r;
	double t;
	double rr;
	Oppo(){};
	Oppo(double x1, double y1, double r1):x(x1), y(y1), r(r1)
	{
		t = x*x+y*y;
		rr = r*r;
	}
};

Oppo oppo[maxn];
bool vis[maxn];

bool dfs(int u)
{
	return true;
}

int main()
{
	int n;
	while(scanf("%d", &n)==1)
	{
		double x,y,r;
		bool nsc;	//north south connect
		for(int i = 0; i < n; i++)
		{
			scanf("%lf%lf%lf", &x, &y, &r);
			oppo[i] = Oppo(x, y, r);
		}
		memset(vis, 0, n*sizeof(int));
		nsc = false;
		for(int i = 0; i < n; i++)
		{
			if (!vis[i] && (oppo[i].r+y) >= 1000)
			{
				vis[i] = 2;
				if (nsc = dfs(i))//= ==
					break;
			}
		}
		if(nsc)
			printf("IMPOSSBILE\n");
		else
		{
			double wn=1000, en=1000;
			for(int i = 0; i < n; i++)
			{
				if ((oppo[i].y+oppo[i].r) >= 1000)
				{
					if (oppo[i].r >= oppo[i].x)
					{
					
					}
					else if (oppo[i].r >= (1000-oppo[i].x))
					{
					
					}
				}
			}
			printf("%.2lf %.2lf %.2lf %.2lf\n", 0.0, wn, 1000.0, en);
		}
	}
}
