/* uva 1354: 天平难题
*  思路：枚举二叉树。
*  难点：剪枝，防止重复枚举.思路：将所有叶子分为左右两个子集，枚举子集。
*
*/

#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

const int maxn = 6;
const int maxnode = 100;
double r;
int n;

struct Node 
{
	int w;
	bool left;
	double e;	
	double le;
	double re;
	Node():w(0){}
};
Node node[maxnode];
bool vis[maxnode];

int nn; 
void newNode(int l, int r)
{
	
	double t1, t2;
	node[++nn].w = node[l].w + node[r].w;
	t1 = (double)node[r].w/(double)node[nn].w;
	t2 = (double)node[l].w/(double)node[nn].w;

	node[nn].le = max(t1+node[l].le, node[r].le-t2);
	node[nn].re = max(t2+node[r].re, node[l].re-t1);
	node[nn].e = node[nn].le + node[nn].re;
	node[nn].left = node[l].left;
	vis[nn] = true;
}

//最大的小于房间宽的天平宽，初始化为0
double ans;

void scale(int residue)
{
	vector<int> v;
	int i;
	v.resize(residue);
	
	for(int i = 0, j = 1; i < residue; j++)
		if (vis[j]) 
			v[i++] = j;
	if (residue == 1)
	{
		double e;
		e = node[v[0]].e;
		if (e < r && e > ans)
			ans = e;
	}
	else
	{
		for(int i = 0; i < residue-1; i++)
		{
			if (node[v[i]].e >= r)
				continue;
			for(int j = i+1; j < residue; j++)
			{
				if (node[v[j]].e >= r)
					continue;
				if (residue > 2 && (node[v[i]].left != node[v[j]].left))
					continue;
				for(int k = 0; k < ((residue > 2) ? 2 : 1); k++)
				{
					int l = k ? v[i]:v[j], r = k ? v[j] : v[i];
					newNode(l, r);
					vis[v[i]] = vis[v[j]] = false;
					scale(residue-1);
					vis[nn--] = false;
					vis[v[i]] = vis[v[j]] = true;
				}
			}
		}
	}
}

int main()
{
	int T;
	cin >> T;
	while (T--) {
		cin >> r;
		cin >> n;
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= n; i++)
		{
			cin >> node[i].w;
			node[i].le = node[i].re = node[i].e = 0;
			vis[i] = true;
		}
		nn = n;
		ans = -1;
		
		if (n == 1)
		{
			if (r > 1)
				ans = 0.0;
		}
		else
		{
			node[n].left = false;			//最后一个元素总是在右子树
			for(int i = 1; i < (1 << (n-1)); i++)
			{
				for(int j = 1; j < n; j++)
				{
					if ( (1<<(j-1)) & i)
						node[j].left = true;
					else
						node[j].left = false;
				}
				nn = n;
				memset(vis, 0, sizeof(vis));
				for (int i = 1; i <= n; i++) vis[i] = true;
				scale(n);
			}
		}
		cout<<setprecision(16)<<setiosflags(ios::fixed)<<ans<<endl;
	}
}
