#include <iostream>

using namespace std;


const int maxn = 102;

char pic[maxn][maxn];

int cid = 0;
int idd[maxn][maxn];
int n, m;

void dfs(int i, int j, int id)
{
	if('*' == pic[i][j])
	{
		idd[i][j] = -1;
		return;
	}
	if(idd[i][j] != 0)
		return;
	id = (id == 0) ? ++cid : id;
	idd[i][j] = id;
	for(int jj = -1; jj <= 1; jj++)
	{
		if ((i > 0) && ('@' == pic[i-1][j+jj]))
		{ 
			idd[i][j] = id;
			dfs(i-1, j+jj, id);
		}
		if ((i < n-1) && ('@' == pic[i+1][j+jj]))
		{
			idd[i][j] = id;
			dfs(i+1, j+jj, id);
		}
	}
	if ((j > 0) && ('@' == pic[i][j-1]))
	{
		idd[i][j] = id;
		dfs(i, j-1, id);
	}
	if ((j < n-1) && ('@' == pic[i][j+1]))
	{
		idd[i][j] = id;
		dfs(i, j+1, id);
	}
}

int main()
{
	while(cin>>m>>n && m != 0)
	{
		for(int i = 0; i < m; i++)
			scanf("%s", pic[i]);
		
		cid = 0;
		for(int i = 0; i < m; i++)
			for(int j = 0; j < n; j++)
				idd[i][j] = 0;
		
		for(int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
			{
				if ('@' == pic[i][j] && 0 == idd[maxn][maxn])
				{
					dfs(i, j, 0);
				}
			}
		cout<<cid<<endl;
	}
}
