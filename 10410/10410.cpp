#include <iostream>
#include <vector>
#include <stack>

using namespace std;
const int maxn = 1001;
int n;

int pos[maxn];

vector<int> ch[maxn];

int main()
{
	int root, u, x;
	for(int i = 1; i < maxn; i++)
		ch[i].clear();
	while(cin>>n && n)
	{
		stack<int> sta;
		for(int i = 1; i <= n; i++)
		{
			cin>>u;
			pos[u] = i;
		}
		cin>>root;
		sta.push(root);
		for(int i = 1; i< n; i++)
		{
			cin>>x;
			while(true)
			{
				u = sta.top();
				if (u == root || pos[u]+1 < pos[x])
				{
					ch[u].push_back(x);
					sta.push(x);
					break;
				}
				sta.pop();
			}
		}
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
