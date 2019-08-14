/*uva 1599
 *思路：1.最简单的想法： 算出最短路径长度（bfs), dfs得到字典序列最小的路径
 *      优化：  
 *	暴力解法的重复计算量太大，时间超时，所以要进行优化。
 *	第一遍bfs的时候就记录所有路径，然后进行选择。
 *得到每个点到终点的最短路径（反向bfs）
 *
 */
#include <iostream>
#include <cstring>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

const int maxv = 100001;
const int maxe = 200000;

struct E
{
	int u;
	int v;
	int c;
};

map<int, set<int> > e[maxv];
map<int, set<int> > root[maxv];
vector<int> seq[maxv];

int vis[maxv];
int n;
void bfs()
{
	memset(vis, 0, sizeof(vis));
	bool running = true;
	
	root[0][0] = set<int>();
	root[0][0].insert(1);
	seq[0].push_back(0);
	for(int i = 0; running; i++)
	{
		for(int j = 0; j < seq[i].size(); j++)
		{
			for(auto it = root[i][seq[i][j]].begin();it!=root[i][seq[i][j]].end();it++)
			{
				for(auto it2 = e[*it].begin(); it2 != e[*it].end(); it2++)
				{
					for(auto it3 = (*it2).second.begin(); it3 !=  (*it2).second.end(); it3++)
					{
						if (!vis[*it3])
						{
							if (root[i+1].count((*it2).first) < 1)
								root[i+1][(*it2).first] = set<int>();
							root[i+1][(*it2).first].insert(*it3);
							vis[*it3]=i+1;
							if(*it3 == n)
								running = false;
						}
					}
				}
			}
		}
		for(auto it = root[i+1].begin(); it != root[i+1].end(); it++)
			seq[i+1].push_back((*it).first);
		sort(seq[i+1].begin(), seq[i+1].end());
	}
}

int main()
{
	while(cin>>n)
	{
		int m, t;
		cin>>m;
		map<long long, int> mp;
		while(m--)
		{
			int u, v, c, i, t;
			cin>>u>>v>>c;
			if (u == v)
				continue;
			if (u > v)
			{
				t = u;
				u = v;
				v = t;
			}
			if (mp.count((long long)u << 32|(long long)v) <1)
				mp[(long long)u << 32|(long long)v] = c;
			else if(mp[(long long)u << 32|(long long)v] > c)
				mp[(long long)u << 32|(long long)v] = c;
		}
		for(auto it = mp.begin(); it != mp.end(); it++)
		{
			int u, v, c;
			u = (*it).first>>32;
			v = (*it).first & 0xffffffff;
			c = (*it).second;
			if(e[u].count(c) < 1)
				e[u][c] = set<int>();
			e[u][c].insert(v);
			if(e[v].count(c) < 1)
				e[v][c] = set<int>();
			e[v][c].insert(u);
		}
		bfs();
	}
}
