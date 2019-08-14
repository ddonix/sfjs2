#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;
 
int G[100][100];
int vis[100];
 
char str[30];
 
int getID(char a1, char a2)
{
	return (a1 - 'A')*2 + (a2 == '+' ? 1:0);
}
 
void connect(char a1, char a2, char b1, char b2)
{
	if(a2 == '0' || b2 == '0')	return ;
	int u = getID(a1, a2)^1;
	int v = getID(b1, b2);
	G[u][v] = 1;
}
 
bool dfs(int u)
{
	vis[u] = -1;
	for(int i = 0; i < 52; i++)
	{
		if(G[u][i] && vis[i] < 0)	return true;
		if(G[u][i] && !vis[i] && dfs(i))  return true;
	}
	vis[u] = 1;
	return false;
}
 
bool solve()
{
	for(int i = 0; i < 52; i++)
	if(!vis[i])
		if(dfs(i))	return true;
	return false;
}
		
int main()
{
	//freopen("ztest.txt","r",stdin);
	//freopen("zans.txt","w",stdout);
	int n;
	while(scanf("%d", &n) == 1 && n)
	{
		memset(vis, 0, sizeof(vis));
		memset(G, 0, sizeof(G));
		for(int k = 1; k <= n; k++)
		{
			scanf("%s", str);
			//printf("%s\n",str);
			for(int i = 0; i < 4; i++)
			for(int j = 0; j < 4; j++)
			if(i != j)
				connect(str[i*2], str[i*2+1], str[j*2], str[j*2+1]);
		}
		if(solve())
			printf("unbounded\n");
		else
			printf("bounded\n");
	}
	return 0;
}
