#include <iostream>
#include <string>
using namespace std;

int maze[4][6];
string ans;
int dd;

const int bits[4] = {1, 2, 4, 8};
const char *orientation = "WNES";

const int dx[4] = { 0, -1, 0, 1};
const int dy[4] = {-1,  0, 1, 0};

int bx, by;
bool ida(int d, int x, int y, string s)
{
	if (d == dd)
	{
		if ((0 == x && !(maze[x][y] & bits[1])) || (3 == x && !(maze[x][y] & bits[3])))
		{
			cout<<s<<endl;
			return true;
		}
		if ((0 == y && !(maze[x][y] & bits[0])) || (5 == y && !(maze[x][y] & bits[2])))
		{
			cout<<s<<endl;
			return true;
		}
		return false;
	}
	else
	{
		for(int i = 0; i < 4; i++)
		{
			int nx = x+dx[i], ny = y+dy[i];
			if (nx >= 0 && nx < 4 && ny >= 0 && ny < 6)
			{
				if (!(maze[x][y] & bits[i]))
				{
					if (ida(d+1, nx, ny, s+orientation[i]))
						return true;
				}
				else
				{
					if((0 == i && !(maze[nx][ny] & bits[0])) 
									|| (1 == i && !(maze[nx][ny] & bits[1]))
									|| (2 == i && !(maze[nx][ny] & bits[2]))
									|| (3 == i && !(maze[nx][ny] & bits[3])))
					{
						int m0 = maze[x][y], m1 = maze[nx][ny];
						maze[x][y] &= ~bits[i];
						maze[nx][ny] |= bits[i];
						maze[nx][ny] &= ~bits[(i+2)%4];
						if (ida(d+1, nx, ny, s+orientation[i]))
							return true;
						maze[x][y] = m0;
						maze[nx][ny] = m1;
					}
				}
			}
		}
		return false;
	}
}

int main()
{
	while(cin>>by>>bx && bx)
	{
		bx--;
		by--;
		for(int i = 0; i < 4; i++)
			for(int j = 0; j < 6; j++)
				cin>>maze[i][j];
		for(dd = 0; dd < 30; dd++)
		{
			if (ida(0, bx, by, ans))
				break;
		}
	}
}
