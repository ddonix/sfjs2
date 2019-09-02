#include <iostream>

using namespace std;


const int maxn = 102;

char pic[maxn][maxn];

int cid = 0;
int idd[maxn][maxn];
int n, m;

void dfs(int i, int j, int id)
{
	if(i < 0 || i >= m || j < 0 || j >= n || (idd[i][j] != 0) || (pic[i][j] != '@')) 
		return;
	idd[i][j] = id;
	for(int ii = -1; ii <= 1; ii++)
		for(int jj = -1; jj <= 1; jj++)
		{
			if (ii || jj)
				dfs(i+ii, j+jj, id);
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
				if ('@' == pic[i][j] && (0 == idd[i][j]))
				{
					dfs(i, j, ++cid);
				}
			}
		cout<<cid<<endl;
	}
}
