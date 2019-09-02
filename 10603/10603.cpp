/* uva 10603:到水问题
*  思路：优先队列，每次到水量最少的先出队列。
*  有个疑问：如何证明每次都是当前倒水量最少的先出队列，能保证先达到目标状态。
*  			 有没有这种可能，a,b下一此改变都能满足，当前到水量a小于b，但是a+da却大雨b+da？
*  可以在优先级里进行一些策略：第一：到水量不同，到水量小的优先。到水量相同，距离目标近的优先。
*  距离目标相同，下一次改变量小的优先。这就有个循环的问题了。
*  本题在实现中，在找下一个状态的时候，直接就改变state pool了，而没有先看是否vis。下次一定注意。
*  在bfs函数中，这点很容易注意。但是，如果bfs中包含了函数，函数中一定要注意不能改变state pool.
*  调试一个多小时才发现这个问题！！！
*
*/
#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 201*201+1;

int cap[3]; 
int D;
int dp, amount;

struct State
{
	int m[3];
	int am;
	int d;
	
	bool update()
	{
		bool up = false;
		if (d > dp || (d == dp && am < amount))
		{
			dp = d;
			amount = am;
		}
		return dp == D;
	}
};

const int ope[6] = {1, 2, 10, 12, 20, 21};//0-->1, 0-->2, 1-->0, 1-->2, 2-->0, 2-->1
State state[maxn];
bool vis[maxn];

int pour(int id, int d)
{
	State & s = state[id];
	int so = d/10;
	int de = d%10;
	if (s.m[so] == 0 || s.m[de] == cap[de])
		return -1;
	State ns = s;
	if (ns.m[so] <= (cap[de]-ns.m[de]))
	{
		ns.am += ns.m[so];
		ns.m[de] += ns.m[so];
		ns.m[so] = 0;
	}
	else
	{
		ns.am += cap[de]-ns.m[de];
		ns.m[so] -= cap[de]-ns.m[de];
		ns.m[de] = cap[de];
	}
	ns.d = 0;
	for(int i = 0; i < 3; i++)
		if (ns.m[i] <= D && ns.m[i] > ns.d)
			ns.d = ns.m[i];
	
	int nid = ns.m[0]*(cap[1]+1)+ns.m[1];
	if (!vis[nid])
		state[nid] = ns;	//bug在此！调试了一个多小时！！！
	return nid;
}

struct cmp
{
	bool operator()(int a, int b)
	{
		if (state[a].am == state[b].am)
			return state[a].d < state[b].d;
		return state[a].am > state[b].am;
	}
};

void bfs() 
{
	priority_queue<int, vector<int>, cmp > q;
	int id;
	q.push(0);
	vis[0] = true;
	dp = 0;
	amount = 0;
	while(!q.empty())
	{
		id = q.top();
		q.pop();
	
		if (state[id].update())
			return;

		for(int i = 0; i < 6; i++)
		{
			int nid = pour(id, ope[i]);
			if (nid > 0 && !vis[nid])
			{
				vis[nid] = true;
				q.push(nid);
			}
		}
	}
}

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>cap[0]>>cap[1]>>cap[2]>>D;
		for(int i = 0; i < (cap[0]+1)*(cap[1]+1); i++)
		{
			state[i].d = state[i].am = state[i].m[0] = state[i].m[1] = state[i].m[2] = 0;
			vis[i] = false;
		}
		state[0].m[2] = cap[2];
		if (cap[2] <= D)
			state[0].d = cap[2];
		else
			state[0].d = 0;
		bfs();
		cout<<amount<<" "<<dp<<endl;
	}
}
