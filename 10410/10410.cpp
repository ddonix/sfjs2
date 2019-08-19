#include <iostream>
#include <vector>

using namespace std;
const int maxn = 1001;

int root;
int n;

int bfs[maxn];
int dfs[maxn];

vector<int> ch[maxn];

int buildtree(int b0)
{
	int i, c0, c1, r = bfs[b0];
	if (b0 >= n)
		return 0;
	if (b0 >= n-1)
		return bfs[b0];
	c0 = bfs[b0+1];
	for(int i = 0; i < n; i++)
	{
		if (dfs[i] == c0)
		{
			if (i < n-1)
				c1 = dfs[i+1];
			else
				c1 = c0;
			break;
		}
	}
	for(i = b0+1; i < n && bfs[i] != c1; i++)
		ch[r].push_back(bfs[i]);
	buildtree(i);
}

int main()
{
	int root;
	for(int i = 1; i < maxn; i++)
		ch[i].clear();
	while(cin>>n && n)
	{
		for(int i = 0; i < n; i++)
			cin>>bfs[i];
		for(int i = 0; i < n; i++)
			cin>>dfs[i];
		buildtree(0);
		for(int i = 1; i <= n; i++)
		{
			cout<<i<<":";
			for(int j = 0; j < ch[i].size();j++)
				cout<<" "<<ch[i][j];
			cout<<endl;
		}
		for(int i = 1; i <= n; i++)
			ch[i].clear();
	}
}
