/*uva 1572:Self-Assembly
 * 关键：
 */
#include <iostream>
using namespace std;

const int N = 52;
int G[N][N];
int vis[52];		//0:还没试 -1:正在测试 1：测试失败

void connect(char a, char f, char a1, char f1)
{
	int u, v;
	if (a == '0' || a1 == '0')
		return;
	u = (a-'A')*2 + ((f == '+') ? 0 : 1);
	v = ((a1-'A')*2 + ((f1 == '+') ? 0 : 1))^1;
	G[u][v] = 1;
}

bool dfs(int u)
{
	vis[u] = -1;
	for(int i = 0; i < 52; i++)
	{
		if (G[u][i])
		{
			if (vis[i] < 0)	
				return true;
			else if(!vis[i] && dfs(i))
				return true;
		}
	}
	vis[u] = 1;
	return false;
}

int main()
{
	int n;
	bool bound;
	while(cin>>n)
	{
		sizeof(G, 0, sizeof(G));
		
		while(n--)
		{
			char s[9];
			cin>>s;
			cout<<s<<endl;
			for(int i = 0; i < 4; i++)
				for(int j = 0; j < 4; j++)
					if (i != j)
						connect(s[i*2], s[i*2+1], s[j*2], s[j*2+1]);
		}
		bound = true;
		sizeof(vis, 0, sizeof(vis));
		for(int i = 0; i < 52 && bound; i++)
		{
			if (!vis[i] && dfs(i))
				bound = false;
		}
		if (bound)
			cout<<"bounded"<<endl;
		else
			cout<<"unbounded"<<endl;
	}
}
