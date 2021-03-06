/* uva 690: 流水线调度问题：10个任务如何安排开始时间，确保总的完成时间最少。
 *    思路：10个任务，第0个任务在0时开始，那么有第1和第0个任务,第2和第1个任务
 *          ...，第9和第8个任务，共计9个时间间隔需要确定。每个时间间隔的取值范围是1到
 *          一个任务的时间(1-19)。那么共有pow(19,9)个选择。
 *          暴力枚举所有可能选择。dfs枚举
 *          剪枝策略：最优胜剪枝+最大预期剪枝
 *          如何判断是否冲突：每一个任务，只考虑与他前面的任务的冲突，而且之考虑在他开始
 *          之前，还没结束的任务。
 */
#include <iostream>
#include <set>
using namespace std;

const int maxct = 19;	//最大周期
const int taskn = 10;	//最大任务数
const int unitn = 5;	//功能单元数
const int maxans = maxct*taskn+unitn;

unsigned long rt[unitn];
int n;
int g;	

unsigned long bits[20] = {	0x1,	0x2,	0x4,	0x8,
				0x10,	0x20,	0x40,	0x80,
				0x100,	0x200,	0x400,	0x800,
				0x1000,	0x2000,	0x4000,	0x8000,
				0x10000,0x20000,0x40000,0x80000};

struct Unit
{
	unsigned long u[5];	//某个时刻起算一个周期内，各unit占用情况
	Unit()
	{
		u[0] = u[1] = u[2] = u[3] = u[4] = 0;
	}
};

int ans;

//d:当前深度，即已经开始了的任务
//c:前一个任务开始时间
//u:前一个任务开始时间计算起，一个周期内各单元占用情况
void dfs(int d, int c, Unit u)
{
	if (c+(10-d)*g >= ans)
		return;
	if (d == 10)
	{
		ans = c;
		return;
	}
	for(int i = 1; i <= n; i++)
	{
		Unit nu;
		int j;
		for(j = 0; j < 5; j++)
		{
			if ((u.u[j] >> i) & rt[j])
				break;
		}
		if (j < 5)
			continue;
		for(j = 0; j < 5; j++)
			nu.u[j] = (u.u[j] >> i) | rt[j];
		dfs(d+1, c+i, nu);
	}
}

int main()
{
	while(cin>>n && n)
	{
		char c;
		for(int i = 0; i < 5; i++)
		{
			rt[i] = 0;
			for(int j = 0; j < n; j++)
			{
				cin>>c;
				rt[i] |= (c == 'X') ? bits[j] : 0;
			}
		}
		for(g = 1; g <= maxct; g++)
		{
			int j;
			for(j = 0; j < 5; j++)
			{
				unsigned long u = (rt[j] >> g);
				if (u & rt[j])
					break;
			}
			if (j == 5)
				break;
		}
		ans = maxans;
		dfs(0, 0, Unit());
		cout<<ans+n-1<<endl;
	}
}
