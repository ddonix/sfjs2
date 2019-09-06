/* uva 690: 流水线调度问题：10个任务如何安排开始时间，确保总的完成时间最少。
 *    思路：10个任务，第0个任务在0时开始，那么有第1和第0个任务,第2和第1个任务
 *          ...，第9和第8个任务，共计9个时间间隔需要确定。每个时间间隔的取值范围是1到
 *          一个任务的时间(1-19)。那么共有pow(19,9)个选择。
 *          暴力枚举所有可能选择。
 */
#include <iostream>
#include <set>

using namespace std;

const int maxct = 20;	//最大周期
const int taskn = 10;	//最大任务数
const int unitn = 5;	//功能单元数
const int maxans = maxct*taskn+unitn;

unsigned long rt[unitn];
int n;

unsigned long bits[20] = {	0x1,	0x2,	0x4,	0x8,
				0x10,	0x20,	0x40,	0x80,
				0x100,	0x200,	0x400,	0x800,
				0x1000,	0x2000,	0x4000,	0x8000,
				0x10000,0x20000,0x40000,0x80000};

int ans;

void dfs(int d)
{
	if (d >= ans)
		return;

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
		ans = maxans;
		dfs();
		cout<<ans<<endl;
	}
}
