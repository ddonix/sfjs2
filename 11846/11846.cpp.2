#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 20;
const int maxk = 26;
int n, g;
char maze[maxn][maxn];
char ans[maxn][maxn];
char t[maxn][maxn];

bool dfs(int p, char ch)
{
	if (ans[p/n][p%n] != '.')
	{
		while(++p < n*n && (ans[p/n][p%n] != '.'))
		{}
		if (p == n*n)
			return true;
		return dfs(p, ch+1);
	}
	else
	{
		int x = p/n, y = p%n;
		for(int i = 1; i <= 9; i++)
			for(int j = 1; j <= 9; j++)
			{
				if (i*j > 9 || i*j < 2)
					continue;
				int p1 = -1;
				int nn = 0;
				for(int i1 = x; i1 < x+i && nn < 2; i1++)
					for(int j1 = y; j1 < y+j && nn < 2; j1++)
					{
						if (maze[i1][j1] != '.')
						{
							nn++;
							p1 = (maze[i1][j1]-'0' == i*j) ? (i1*n+j1) : p1;
						}
					}
				if (nn == 1 && p1 != -1)
				{
					for(int xx = 0; xx < n; xx++)
					{
						for(int yy = 0; yy < n; yy++)
							cout<<ans[xx][yy];
						cout<<endl;
					}
					cout<<endl<<endl;
					
					bool f = true;
					for(int i1 = x; i1 < x+i && f; i1++)
						for(int j1 = y; j1 < y+j && f; j1++)
							if (ans[i1][j1] != '.')
								f = false;
					if (!f)
						continue;
					for(int i1 = x; i1 < x+i && f; i1++)
						for(int j1 = y; j1 < y+j && f; j1++)
							ans[i1][j1] = ch;
					int np = -1;
					while(++np < n*n && ans[np/n][np%n] != '.')
					{}
					if (np == n*n)
						return true;
					else
					{
						if (dfs(np, ch+1))
							return true;
						for(int i1 = x; i1 < x+i; i1++)
							for(int j1 = y; j1 < y+j; j1++)
								ans[i1][j1] = '.';
					}
				}
			}
		return false;
	}
}

int main()
{
	while(cin>>n>>g && n)
	{
		for(int i = 0; i < n; i++)
			cin>>maze[i];
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
					ans[i][j] = '.';

		dfs(0, 'A');
		for(int i = 0; i < n; i++)
			cout<<ans[i]<<endl;
	}
}
