/* uva 11853:Paintball
* 思路：如果障碍物隔绝了南北，那么不能从东到西。
* 反之如果不能从东到西，则隔绝了南北。
* 对攻击范围达到北边界的所有敌人，分别作dfs或者bfs，看看能否到达南边界。
*/
#include <cstdio>
#include <cmath>
using namespace std;

const int maxn = 1001;
struct Oppo
{
	double x,y;
	double r;
	Oppo(){}
	Oppo(double x1, double y1, double r1):x(x1), y(y1), r(r1){}
};

Oppo oppo[maxn];
bool vis[maxn];

int main()
{
	int n;
	while(scanf("%d", &n)==1)
	{
		for(int i = 0; i < n; i++)
		{
			scanf("%lf%lf%lf", &oppo[i].x, &oppo[i].y, &oppo[i].r);
			printf("%lf%lf%lf\n", oppo[i].x, oppo[i].y, oppo[i].r);
		}
	}
}
