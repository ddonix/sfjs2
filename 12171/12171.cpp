/*
* 审题：要考虑完全被包裹起来的情况，所以体积的计算也要bfs。
* 此题要floodfill
*/

#include <iostream> 
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 50;
const int EDGE = 1024;
const int maxd = 102; 
int ad[3][maxd];			//离散化坐标
int adn[3];					//离散化坐标个数

int vis[maxd][maxd][maxd];
int grid[maxd][maxd][maxd];	//0:空气	//1：铜

int cube[maxn][6];

struct Index
{
	int x,y,z;
	Index(int xx, int yy, int zz) : x(xx), y(yy), z(zz){}
};

int area;
int volume;
int dx[] = {1,-1, 0, 0, 0, 0};
int dy[] = {0, 0, 1,-1, 0, 0};
int dz[] = {0, 0, 0, 0, 1,-1};
void bfs()
{
	area = 0;
	volume = 0;
	memset(vis, 0, sizeof(vis));
	queue<Index> q;
	
	q.push(Index(0,0,0));
	vis[0][0][0] = 1;

	while(!q.empty())
	{
		Index ind = q.front();
		q.pop();
		int x, y, z;
		x = ind.x;
		y = ind.y;
		z = ind.z;
	
		if (0 == grid[x][y][z])
			volume += (ad[0][x+1]-ad[0][x])*(ad[1][y+1]-ad[1][y])*(ad[2][z+1]-ad[2][z]);
        for(int i=0; i<6; i++)
		{
            int tx, ty, tz;
            tx = x + dx[i];
            ty = y + dy[i];
            tz = z + dz[i];
            if(tx<0 || tx>=adn[0]-1 || ty<0 || ty>=adn[1]-1 || tz<0 || tz>=adn[2]-1)
                continue;
            if(grid[tx][ty][tz] == 1)
			{
            	if (i < 2)
					area += (ad[1][y+1]-ad[1][y])*(ad[2][z+1]-ad[2][z]);
            	else if (i < 4)
					area += (ad[0][x+1]-ad[0][x])*(ad[2][z+1]-ad[2][z]);
            	else
					area += (ad[0][x+1]-ad[0][x])*(ad[1][y+1]-ad[1][y]);
			}
			else if(grid[tx][ty][tz] == 0 && vis[tx][ty][tz] == 0)
			{
                q.push(Index(tx, ty, tz));
                vis[tx][ty][tz] = 1;
            }
        }
    }
	volume = EDGE*EDGE*EDGE - volume;
}

int n;
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>n;
		volume = 0;
		for(int i = 0; i < n; i++)
		{
			int a[6];
			cin>>a[0]>>a[1]>>a[2]>>a[3]>>a[4]>>a[5];
			volume += a[3]*a[4]*a[5];
			for(int j = 0; j < 3; j++)
			{
				ad[j][2*i+1] = cube[i][j] = a[j];
				ad[j][2*i+2] = cube[i][3+j] = a[3+j]+a[j];
			}
		}
		for(int i = 0; i < 3; i++)
		{
			ad[i][0] = 0;
			sort(ad[i], ad[i]+2*n+1);
			adn[i] = unique(ad[i], ad[i]+2*n+1)-ad[i];
			ad[i][adn[i]++] = EDGE;
		}

		//关键步骤：根据n个铜cube填充grid
		//这个步骤如果不做，下步判断接触面积将极其麻烦
		memset(grid, 0, sizeof(grid));
		for(int c = 0; c < n; c++)
		{
			int x0, x1, y0, y1, z0, z1;
			x0 = lower_bound(ad[0], ad[0]+adn[0], cube[c][0])-ad[0];
			x1 = lower_bound(ad[0], ad[0]+adn[0], cube[c][3])-ad[0];
			y0 = lower_bound(ad[1], ad[1]+adn[0], cube[c][1])-ad[1];
			y1 = lower_bound(ad[1], ad[1]+adn[0], cube[c][4])-ad[1];
			z0 = lower_bound(ad[2], ad[2]+adn[0], cube[c][2])-ad[2];
			z1 = lower_bound(ad[2], ad[2]+adn[0], cube[c][5])-ad[2];
			for(int i = x0; i < x1; i++)
				for(int j = y0; j < y1; j++)
					for(int k = z0; k < z1; k++)
						grid[i][j][k] = 1;
		}
		bfs();
		cout<<area<<" "<<volume<<endl;
	}
}
