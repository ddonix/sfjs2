#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
using namespace std;

const int maxn = 6;
const int maxnode = 100;
double r;
int n;
int s[maxn];

struct Node 
{
	int w;
	double le;
	double re;
	Node():w(0), le(0), re(0){}
};
Node nodepool[maxnode];

int nn; 
int newNode(int l, int r)
{
	int res = ++nn;
	nodepool[res].w = nodepool[l].w + nodepool[r].w;
	nodepool[res].le = nodepool[l].le+(double)nodepool[r].w/(double)(nodepool[l].w+nodepool[r].w);
	nodepool[res].re = nodepool[r].re+(double)nodepool[l].w/(double)(nodepool[l].w+nodepool[r].w);
	return res;
}

//删除最后一个结点
int deleteNode()
{
	nodepool[nn].w = 0;
	nodepool[nn].le = nodepool[nn].re = 0;
	return --nn;
}

double ans = r;
bool vis[maxnode];

void scale(int len)
{
	double e;
	vector<int> v;
	int l;
	for(int i = 1; i <= len; i++)
		if (vis[i])
			v.push_back(i);
	l = v.size();
	if (l == 1)
	{
		e = nodepool[v[0]].le+nodepool[v[0]].re;
		if (e < r && e > ans)
			ans = e;
	}
	else
	{
		for(int i = 0; i < l-1; i++)
			for(int j = i+1; j < l; j++)
			{
				int l = v[i], r=v[j];
				int next = newNode(l, r);
				vis[v[i]] = false;
				vis[v[j]] = false;
				vis[next] = true;
				scale(next);
				deleteNode();
				vis[v[i]] = true;
				vis[v[j]] = true;
				vis[next] = false;
				
				next = newNode(r, l);
				vis[v[i]] = false;
				vis[v[j]] = false;
				vis[next] = true;
				scale(next);
				deleteNode();
				vis[v[i]] = true;
				vis[v[j]] = true;
				vis[next] = false;
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
			cin >> nodepool[i].w;
			vis[i] = true;
		}
		nn = n;
		scale(6);
		if (ans == r)
			cout<<"-1"<<endl;
		else
			cout<<ans<<endl;
	}
}
