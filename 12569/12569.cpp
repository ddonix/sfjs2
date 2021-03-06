/* uva 12569: Planning mobile robot on Tree(EASY Version)
 * 	题意：连通无环图（树）(4 <= n <= 15)某个结点上有一个机器人，需要将机器人移动到一个特定目的结点。一次只能挪动到
 * 	      相邻结点。有些结点上有石子(0 <=m  <= n-2)，移动的时候遇到石子档路，就不能移动。需要移动石子。石子也是一
 * 	      次移动到相邻位置。遇到档路的，不能移动。
 * 	      要求移动的次数最少，输出移动的顺寻。如果有多个答案，任意输出一个。
 * 	分析：乍一看很难题！
 * 	      15个结点，每个结点有3种状态（机器人，石子，其他).最多有pow(3,15)=14348907种状态.
 * 	      考虑排列组合，15个结点，1个机器人，m个石子，那么总的状态应该是A(15,1)*C(14,m)种，最大为
 * 	      A(15,1)*C(14,7)=51480种。Hash
 * 	思路：
 * 	      1.暴力解法，bfs枚举所有移动.
 * 	      2.图的表示，采用邻接矩阵。
 * 	      3.设计一个好的Hash函数.15个结点,每个结点有无石头，设为1或者0.机器人位置×pow(2,15).
 * 	      15*pow(2,15)=491520。数组开的下!
 */
#include <iostream>
#include <cstring>
#include <string>
#include <queue>
#include <stack>
#include <sstream>
using namespace std;

const int maxn = 15;
int n, m;
int be, ed;

//启示状态
//3种状态：0：无机器人，无石子, 1: 机器人， 2：石子
int bv[maxn];		

bool G[maxn][maxn];

signed char vis[491520];
unsigned long bits[16] = {	0x1,	0x2,	0x4,	0x8, 0x10,	0x20,	0x40,	0x80,
				0x100,	0x200,	0x400,	0x800, 0x1000,	0x2000,	0x4000,	0x8000};

//最后的状态，用来进行结果输出
int pre[491520];
int edc;

int dhash(int *v)
{
	int code = 0;
	for(int i = 0; i < n; i++)
	{
		if (1 == v[i])
			code += (i<<15);
		else if(2 == v[i])
			code += bits[i];
	}
	return code;
}

void rhash(int code, int *v)
{
	for(int i = 0; i < n; i++)
		v[i] = 0;
	v[code >> 15] = 1;
	for(int i = 0; i < n; i++)
		if (code & bits[i])
			v[i] = 2;
}

void printproc()
{
	stack<int> sta;
	int code = edc;
	while(code != -1)
	{
		sta.push(code);
		code = pre[code];
	}
	int v1[maxn],v2[maxn];
	code = sta.top();
	sta.pop();
	rhash(code, v1);
	
	while(!sta.empty())
	{
		int v2[maxn];
		int dd[2];
		code = sta.top();
		sta.pop();
		rhash(code, v2);
		for(int i = 0, d = 0; i < n && d < 2; i++)
		{
			if (v2[i] != v1[i])
				dd[d++] = i;
		}
		if (v1[dd[0]])
			cout<<dd[0]+1<<' '<<dd[1]+1<<endl;
		else
			cout<<dd[1]+1<<' '<<dd[0]+1<<endl;
		for(int i = 0; i < n; i++)
			v1[i] = v2[i];
	}

}

int bfs()
{
	queue<int> q;
	int code = dhash(bv);
	q.push(code);
	vis[code] = 1;
	pre[code] = -1;

	while(!q.empty())
	{
		code = q.front();
		q.pop();

		if (code >>15 == ed)
		{
			edc = code;
			return vis[code]-1;
		}
		int v[maxn];
		rhash(code, v);
		for(int i = 0; i < n; i++)
		{
			if (v[i] != 0)
			{
				for(int j = 0; j < n; j++)
				{
					if (j == i || v[j] || !G[i][j])
						continue;
					int ncode;
					v[j] = v[i];
					v[i] = 0;
					ncode = dhash(v);
					v[i] = v[j];
					v[j] = 0;
					
					if (!vis[ncode])
					{
						vis[ncode] = vis[code]+1;
						pre[ncode] = code;
						q.push(ncode);
					}
				}
			}
		}
	}
	return -1;
}

int main()
{
	int T,r;
	string s;
	
	cin>>T;
	cin.ignore(1024, '\n');
	getline(cin, s);
	for(int ka = 1; ka <= T; ka++)
	{
		stringstream ss(s);
		ss>>n>>m>>be>>ed;
		be--;
		ed--;

		memset(bv, 0, sizeof(bv));
		memset(G, 0, sizeof(G));
		bv[be] = 1;
		for(int i = 0; i < m; i++)
		{
			int o;
			cin>>o;
			bv[o-1] = 2;
		}
		cin.ignore(1024, '\n');
		while(1)
		{
			if (!getline(cin, s) || (s.find(' ', s.find(' ')+1) != string::npos))
				break;
			int v, u;
			stringstream s1(s);
			s1>>v>>u;
			G[v-1][u-1] = true;
			G[u-1][v-1] = true;
		}

		memset(vis, 0, sizeof(vis));
		memset(pre, 0, sizeof(pre));
		cout<<"Case "<<ka<<": ";
		r = bfs();
		cout<<r<<endl;
		if (r > 0)
			printproc();
		cout<<endl;
	}
}
