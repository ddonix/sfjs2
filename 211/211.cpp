#include <cstdio>
#include <cstring>
#include <set>

using namespace std;

const int domino[29][2] = { {0,0},	{0,0}, {0,1}, {0,2}, {0,3}, {0,4}, {0,5}, {0,6},
					{1,1}, {1,2}, {1,3}, {1,4}, {1,5}, {1,6}, {2,2},
					{2,3}, {2,4}, {2,5}, {2,6}, {3,3}, {3,4}, {3,5},
					{3,6}, {4,4}, {4,5}, {4,6}, {5,5}, {5,6}, {6,6}};

int pip[7][8];

void initialize()
{
	int n[7];
	for(int i = 0; i < 7; i++)
		n[i] = 0;
	for(int i = 1; i <= 28; i++)
	{
		pip[domino[i][0]][n[domino[i][0]]++] = i;
		pip[domino[i][1]][n[domino[i][1]]++] = i;
	}
}

int maze[7][8];

int ans[7][8];		//答案
int na;			//答案个数

int dx[4] = { 0, 0, -1, 1};
int dy[4] = {-1, 1,  0, 0};

bool vis[29];

//p:当前考虑的位置
//d:已经完成的
void dfs(int p, int d)
{
	if (28 == d)
	{
		na++;
		for(int i = 0; i < 7; i++)
		{
			for(int j = 0; j < 8; j++)
				printf("  %2d", ans[i][j]);
			printf("\n");
		}
		printf("\n\n");
	}
	else
	{
		int x = p/8;
		int y = p%8;
		for(int i = 0; i < 4; i++)
		{
			int nx = x+dx[i];
		       	int ny = y+dy[i];
			if (nx < 0 || nx >= 7 || ny < 0 || ny >= 8)
				continue;
			if (ans[nx][ny])
				continue;
			for(int i = 1; i <= 28; i++)
			{
				if (!vis[i] && ( (domino[i][0] == maze[x][y] && domino[i][1] == maze[nx][ny]) 
						|| (domino[i][0] == maze[nx][ny] && domino[i][1] == maze[x][y])))
				{
					ans[x][y] = i;
					ans[nx][ny] = i;
					vis[i] = true;
					int np;
					for(np = p+1; np < 56 && ans[np/8][np%8]; np++);
					dfs(np, d+1);
					ans[x][y] = 0;
					ans[nx][ny] = 0;
					vis[i] = false;
				}
			}
		}
	}
}

int main()
{
	int ka;
	initialize();
	while(scanf("%d", &maze[0][0]) == 1)
	{
		for(int j = 1; j < 8; j++)
			scanf("%d", &maze[0][j]);
		for(int i = 1; i < 7; i++)
			for(int j = 0; j < 8; j++)
				scanf("%d", &maze[i][j]);
		printf("Layout #%d:\n\n\n", ++ka);
		for(int i = 0; i < 7; i++)
		{
			for(int j = 0; j < 8; j++)
				printf("   %d", maze[i][j]);
			printf("\n");
		}
		printf("\n");
		printf("Maps resulting from layout #%d are:\n\n\n", ka);

		memset(ans, 0, sizeof(ans));
		memset(vis, 0, sizeof(vis));
		na = 0;
		dfs(0, 0);
		printf("There are %d solution(s) for layout #%d.\n\n\n\n\n\n", na, ka);
	}
}
