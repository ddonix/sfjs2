#include <iostream>
#include <string>
using namespace std;

int maze[4][6];
char ans[32];
int dd;

const int bits[4] = {1, 2, 4, 8};
const char *orientation = "WNES";

const int dx[4] = { 0, -1, 0, 1};
const int dy[4] = {-1,  0, 1, 0};


int solve(int x, int y)
{
	if (0 == x && !(maze[x][y] & bits[1])) return 1;
	if (3 == x && !(maze[x][y] & bits[3])) return 3;
	if (0 == y && !(maze[x][y] & bits[0])) return 0;
	if (5 == y && !(maze[x][y] & bits[2])) return 2;
	return -1;
}

bool ida(int d, int x, int y, int pre)
{
	if (d == dd)
	{
		int o = solve(x,y);
		if (o < 0)
			return false;
		ans[d] = orientation[o];
		return true;
	}
	else
	{
		for(int i = 0; i < 4; i++)
		{
			int nx = x+dx[i], ny = y+dy[i];
			if (nx >= 0 && nx < 4 && ny >= 0 && ny < 6)
			{
				if (pre >= 0 && i != pre && 0 == (pre+i)%2)
					continue;
				ans[d] = orientation[i];
				if (!(maze[x][y] & bits[i]))
				{
					if (ida(d+1, nx, ny, i))
						return true;
				}
				else if(!(maze[nx][ny] & bits[i]))
				{
					int m0 = maze[x][y], m1 = maze[nx][ny];
					maze[x][y] &= ~bits[i];
					maze[nx][ny] |= bits[i];
					maze[nx][ny] &= ~bits[(i+2)%4];
					ans[d] = orientation[i];
					if (ida(d+1, nx, ny, -1))
						return true;
					maze[x][y] = m0;
					maze[nx][ny] = m1;
				}
			}
		}
		return false;
	}
}

int main()
{
	int x, y;
	while(cin>>y>>x && x)
	{
		x--;
		y--;
		for(int i = 0; i < 4; i++)
			for(int j = 0; j < 6; j++)
				cin>>maze[i][j];
		for(dd = 0; dd < 30; dd++)
		{
			if (ida(0, x, y, -1))
				break;
		}
		ans[dd+1] = 0;
		cout<<ans<<endl;
	}
}
