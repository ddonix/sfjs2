#include <iostream>
#include <vector>
using namespace std;
const int maxn = 7;

int n;
char maze[maxn+1][maxn+1];
int need[maxn+1][maxn+1];

int head[maxn*maxn*2];		// /: i*n+j  \:i*n+j+n*n

int dx[4] = {-1, -1, 0,  0};
int dy[4] = {-1,  0, 0, -1};
char dc[4] = {'\\', '/', '\\', '/'};
char ndc[4] = {'/', '\\', '/', '\\'};

bool isnul(int x, int y, int d)
{
	int nx = x+dx[d], ny = y+dy[d];
	if (nx >= 0 && nx < n && ny >= 0 && ny < n)
		return -1 == head[nx*n+ny] && -1 == head[nx*n+ny+n*n];
	return false;
}

bool iscon(int x, int y, int d)
{
	int nx = x+dx[d], ny = y+dy[d];
	if (nx >= 0 && nx < n && ny >= 0 && ny < n)
	{
		int id = nx*n+ny+ ('\\' == dc[d] ? n*n : 0);
		return -1 != head[id];
	}
	return false;
}

int gethead(int id)
{
	if (head[id] < 0)
		return -1;
	int r = id;
	while(r != head[r])
	{
		r = head[r];
	}
	return r;
}

bool isUnit(int p, char ch, int & h0, int & h1)
{
	int id = p + ('/' == ch ? 0 : n*n);
	int x = p/n, y = p%n;
	int gx0 = x,   gy0 = ('/' == ch ? y+1 : y);
	int gx1 = x+1, gy1 = ('/' == ch ? y : y+1);
	for(int d = 0; d < 4 && h0 < 0 && h1 < 0; d++)
	{
		if (h0 < 0 && iscon(gx0, gy0, d))
		{
			int nid = (gx0+dx[d])*n+(gy0+dy[d]);
			nid += (dc[d] == '/' ? 0 : n*n);
			h0 = gethead(nid);
		}
		if (h1 < 0 && iscon(gx1, gy1, d))
		{
			int nid = (gx1+dx[d])*n+(gy1+dy[d]);
			nid += (dc[d] == '/' ? 0 : n*n);
			h1 = gethead(nid);
		}
	}
	if (h0 > 0 && h1 > 0 && (h0 == h1))
		return true;
	return false;
}

bool setline(int p, char ch, int & h0, int & h1)
{
	if (-1 != head[p] || -1 != head[p+n*n])
		return false;
	if (isUnit(p, ch, h0, h1))
		return false;
	int x = p/n, y = p%n;
	int x0 = x-(('/' == ch) ? dx[3] : dx[2]), y0 = y-(('/' == ch) ? dy[3] : dy[2]);
	int x1 = x-(('/' == ch) ? dx[1] : dx[0]), y1 = y-(('/' == ch) ? dy[1] : dy[0]);
	need[x0][y0]--;
	need[x1][y1]--;
	
	bool f = true;
	int kx = x-dx[2], ky = y-dy[2];
	f = (need[kx][ky] <= -100 || 0 == need[kx][ky]) ? f : false;
	if (y == n-1)
	{
		kx = x-dx[3], ky = y-dy[3];
		f = (need[kx][ky] <= -100 || 0 == need[kx][ky]) ? f : false;
	}
	if (x == n-1)
	{
		kx = x-dx[1], ky = y-dy[1];
		f = (need[kx][ky] <= -100 || 0 == need[kx][ky]) ? f : false;
	}
	if (!f)
	{
		need[x0][y0]++;
		need[x1][y1]++;
		return false;
	}
	int id = p + ('/' == ch ? 0 : n*n);
	if (h0 < 0 && h1 < 0)
		head[id] = id;
	else if (h0 >= 0 && h1 < 0)
		head[id] = h0;
	else if (h0 < 0 && h1 >= 0)
		head[id] = h1;
	else
		head[h0] = head[id] = h1;
	return true;
}

bool unsetline(int id, int & h0, int & h1)
{
	return true;
}

bool setline(int x, int y, int d, bool con)
{
	int nx = x+dx[d], ny = y+dy[d], h0 = -1, h1 = -1;
	if (nx >= 0 && nx < n && ny >= 0 && ny < n)
		return setline(nx*n+ny, con ? dc[d] : ndc[d] ,h0, h1);
	return false;
}

void prepare()
{
	for(int i = 0; i < n+1; i++)
		for(int j = 0; j < n+1; j++)
		{
			if ('0' == maze[i][j])
			{
				for(int d=0; d < 4; d++)
					setline(i, j, d, false);
			}
		}
	bool running = true;
	while(running)
	{
		running = false;
		for(int i = 0; i < n+1; i++)
			for(int j = 0; j < n+1; j++)
			{
				if (need[i][j] > 0)
				{
					int nu = 0;
					for(int d = 0; d < 4; d++)
						nu += isnul(i, j, d) ? 1 : 0;
					if (nu == need[i][j])
					{
						running = true;
						for(int d = 0; d < 4; d++)
							setline(i, j, d, true);
					}
				}
			}
	}
}

bool dfs(int g)
{
	return false;
}

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(int i = 0; i < n+1; i++)
		{
			cin>>maze[i];
			for(int j = 0; j < n+1; j++)
				need[i][j] = isdigit(maze[i][j]) ? maze[i][j]-'0' : -100;
		}
		for(int i = 0; i < n*n*2; i++)
			head[i] = -1;
		prepare();
		dfs(0);
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				if (-1 == head[i*n+j] && -1 == head[i*n+j+n*n])
					cout<<'0';
				else 
					cout<<(-1 == head[i*n+j] ? '\\' : '/');
			}
			cout<<endl;
		}
		for(int i = 0; i < n+1; i++)
		{
			for(int j = 0; j < n+1; j++)
				cout<<need[i][j]<<' ';
			cout<<endl;
		}

	}
}
