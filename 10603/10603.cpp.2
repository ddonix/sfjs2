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
		state[nid] = ns;
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
