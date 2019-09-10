/* uva 12569: Planning mobile robot on Tree(EASY Version)
 * 	题意：连通无环图（树）(4 <= n <= 15)某个结点上有一个机器人，需要将机器人移动到一个特定目的结点。一次只能挪动到
 * 	      相邻结点。有些结点上有石子(0 <=m  <= n-2)，移动的时候遇到石子档路，就不能移动。需要移动石子。石子也是一
 * 	      次移动到相邻位置。遇到档路的，不能移动。
 * 	      要求移动的次数最少，输出移动的顺寻。如果有多个答案，任意输出一个。
 * 	分析：这是一道难题！
 * 	      1.连通无环图，那么从起点到终点只有一条路径，如果路径上没有石子，那么机器人可以直接移动到目的。
 * 	      2. 
 * 	思路：没思路！
 * 	      1.暴力解法，枚举所有移动.
 * 	      2.图的表示，采用邻接矩阵。
 * 	      3.IDA.
 * 	      4.移动策略：
 * 	      5.剪枝：
 */
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
using namespace std;

const int maxn = 15+1;
int n, m;
int be, ed;

int v[maxn];		//每个结点有3种状态：0：无机器人，无石子, 1: 机器人， 2：石子
bool G[maxn][maxn];

int main()
{
	int T;
	string s;
	
	cin>>T;
	cin.ignore(1024, '\n');
	getline(cin, s);
	for(int ka = 1; ka <= T; ka++)
	{
		stringstream ss(s);
		ss>>n>>m>>be>>ed;
		cout<<n<<" "<<m<<" "<<be<<" "<<ed<<endl;

		memset(v, 0, sizeof(v));
		memset(G, 0, sizeof(G));
		v[be] = 1;
		for(int i = 0; i < m; i++)
		{
			int o;
			cin>>o;
			v[o] = 2;
			cout<<o<<endl;
		}
		cin.ignore(1024, '\n');
		while(1)
		{
			if (!getline(cin, s))
				break;
			if (s.find(' ', s.find(' ')+1) != string::npos)
				break;
			int v, u;
			stringstream s1(s);
			s1>>v>>u;
			G[v][u] = true;
			G[u][v] = true;
			cout<<v<<" -- "<<u<<endl;
		}
	}
}
