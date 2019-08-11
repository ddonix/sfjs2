#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

struct Node
{
	int b;			//before
	vector<Node *> a;	//after
	Node() : b(0)
	{
		a.resize(0);
	}
};

struct Tree
{
	Node *root;
	bool enable;

	Tree() : root(0), enable(false) {}
	void init(int b, int a)
	{
		root = new Node();
		enable = true;
		
		root->b = b;
		Node * t = new Node();
		t->b = a;
		root->a.push_back(t);
	}
	
	//type含义
	//0: b,a 之前存在过
	//1:b存在，a不存在
	//2:b不存在，a存在
	int insert(int b, int a, int type)
	{
		return 0;
	}

	//type含义
	//0: b,a 之前存在过
	//1:b存在，a不存在
	//2:b不存在，a存在
	int insert(Tree * tr, int b, int a, int type)
	{
		return 0;
	}
};

const int maxn = 102;
int re[maxn][maxn];
Tree trees[maxn];
map<int, Tree *> mp;

int m,n;
int nt = 0;

int insert(int b, int a)
{
	if (mp.count(b) < 1)
	{
		if (mp.count(a) < 1)
		{
			mp[b] = &trees[nt];
			mp[a] = &trees[nt++];
			mp[b]->init(b, a);
		}
		else
		{
			mp[b] = mp[a];
			mp[a]->insert(b, a);
		}
	}
	else
	{
		if (mp.count(a) < 1)
		{
			mp[a] = mp[b];
			mp[b]->insert(b, a);
		}
		else
		{
			if (mp[b] == mp[a])
				mp[b]->insert(b, a);
			else
			{
				mp[b]->insert(mp[a], b, a);
				mp[a]->enable = false;
				mp[a] = mp[b];
			}
		}
	}
	return 0;
}

int main()
{
	while(cin>>n>>m && n != 0)
	{
		memset(re, 0, sizeof(re));
		mp.clear();
		nt = 0;
		
		for(int i = 0; i < m; i++)
		{
			int b, a;
			cin>>b>>a;
			re[b][a] = 1;
			insert(b, a);
		}
		
		for(int i = 1; i < n; i++)
			cout<<i<<" ";
		cout<<n<<endl;
	}
}
