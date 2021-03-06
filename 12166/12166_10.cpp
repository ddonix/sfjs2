/* uva 12166:Equilibrium Mobile
*  描述：字符串形式给定一个叶子结点带权重的二叉树天平，要求天平平衡的情况下，最少要改动多少叶子的权重。
*  思路：二叉树的结构确定的情况下，任意一个叶子结点的权重确定了，要使得二叉树平衡，那么其他叶子结点的权重就同时确定了。
	这道题的关键是两步，确定二叉树的结构（使用stack)，确定叶子权重的更新方法。
	进一步分析可以发现，最深的叶子权重最小，其他叶子的权重都是他的2的幂次倍。
	深度每少1，权重2倍。进一步理解题意，最少要改动多少个叶子的权重，其实就是最多可以保留多少个叶子的权重!
	如果一个都不能保留，就是全部改动。可以一个个的试着保留，然后看保留那个改动的最少，这样就能得到答案了。
	结果超时，换个思路。把每个叶子移动到最底层,然后看哪个数的数量最多。这是一个求数组中的众数问题。 移动之前，先排除那些不是底层相应幂次的值，也排除那些会导致顶层叶子超出1000000000的值。
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <stack>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;
const int maxn = 65538;
struct Node
{
	int w;				//weight. 叶子结点的权重，非叶子结点w无意义。
	int d;				//depth. 根为1(方便判断深度是否设定)
	int f;				//father
	
	Node() : d(0){}
	Node(int w_) : w(w_), d(0){}
};

Node node[maxn];

int nt = 0;
int nn = maxn;

int newNode(int w)
{
	node[++nt].w = w;
	return nt;
}

int newNode(int l, int r)
{
	node[r].f = node[l].f = --nn;
	return nn;
}

int mind, maxd;
void makedepth(int r)
{
	node[r].d = 1;
	for(int i = 1; i <= nt; i++)
	{
		if(node[node[i].f].d)
			node[i].d = node[node[i].f].d+1;
		else
		{
			int d = 1;
			int j = node[i].f;
			while(!node[j].d)
			{
				j = node[j].f;
				d++;
			}
			node[i].d = node[j].d+d;
			node[node[i].f].d = node[i].d-1;
		}
		if (node[i].d < mind)
			mind = node[i].d;
		if (node[i].d > maxd)
			maxd = node[i].d;
	}
}

//单个结点的情况进入之前排除
int buildtree(char s[])
{
	stack<int> st;
	int r;
	int len = strlen(s);
	for(int i = 0; i < len; i++)
	{
		if(']' == s[i])
		{
			int ch[2];
			for(int j = 0; j < 2; j++)
			{
				ch[j] = st.top(); 
				st.pop();
				if (ch[j] < 0)
					ch[j] = -ch[j];
				else
				{
					ch[j] = newNode(ch[j]);
				}
			}
			st.push(-newNode(ch[1], ch[0]));
		}
		else if(s[i] >= '1' && s[i] <= '9')
		{
			stringstream ss(s+i);
			int w;
			ss>>w;
			st.push(w);
			for(i += 1; s[i] >= '0' && s[i] <= '9'; i++);
			i--;
		}
	}
	return -st.top();
}

const int mp2[16] = { 0, 1, 3, 7, 
				15, 31, 63,127, 
				255, 511, 1023, 2047, 
				4095, 8191, 16383, 32767};

map<int, int> mp1;

void printtree(int r)
{
	int res=0;
	for(int i = 1; i <= nt; i++)
	{
		int d = node[i].d;
		int w = node[i].w ;
		
		if (((mp2[maxd-d] & w) != 0) || ((long long)(w << (d-mind)) >= 1000000000))
			continue;
		w = (w >> (maxd-d));
		if (mp1.count(w)<1)
			mp1[w] = 1;
		else
			mp1[w]++;
	}
	for(auto it = mp1.begin(); it != mp1.end(); it++)
		if (res < (*it).second)
			res = (*it).second;
	printf("%d\n", nt-res);
}

int main()
{
	int T;
	char s[1000000];
	scanf("%d", &T);
	while(T--)
	{
		int r, res;
		scanf("%s", s);
		if (s[0] >= '1' && s[0] <= '9')
		{
			printf("0\n");
			continue;
		}
		r = buildtree(s);
		makedepth(r);
		printtree(r);
		
		for(int i = nn; i < maxn; i++)
			node[i].d = 0;
		for(int i = 1; i <= nt; i++)
			node[i].d = 0;
		nn = maxn;
		nt = 0;
		mind=16;
		maxd = 0;
		mp1.clear();
	}
}
