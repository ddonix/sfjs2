
#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<string>
#include<map>
#include<sstream>
#include<queue>
#include<cctype>
using namespace std;
typedef long long ll;
const int maxn = 100 + 30;
const int maxm = 50 + 5;
int g[maxn][maxn][maxn];
int x[maxn], y[maxn], z[maxn];
const int dx[] = { 1, -1, 0, 0, 0, 0 };
const int dy[] = { 0, 0, 1, -1, 0, 0 };
const int dz[] = { 0, 0, 0, 0, 1, -1 };
map<int, int>X, Y, Z;
int n;
ll space, vol, air;
int xnum, ynum, znum;
int mx, my, mz;
struct rec
{
	int id;
	int x0, y0, z0, x, y, z;
	bool operator <(const rec&b)
	{
		return x0 < b.x0 || (x0 == b.x0&&y0 < b.y0) || (x0 == b.x0&&y0 == b.y0&&z0 < b.z0);
	}
}r[maxm];
struct coord
{
	int x, y, z;
	coord(int i, int j, int k) :x(i), y(j), z(k){}
};
 
void draw(int pos, int id)
{
	int x1 = X[r[pos].x0], x2 = X[r[pos].x + r[pos].x0];
	int y1 = Y[r[pos].y0], y2 = Y[r[pos].y + r[pos].y0];
	int z1 = Z[r[pos].z0], z2 = Z[r[pos].z + r[pos].z0];
	for (int i = x1; i < x2; i++)
	for (int j = y1; j < y2; j++)
	for (int k = z1; k < z2; k++)
		g[i][j][k] = id;
}
 
 
int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		air = 0;
		cin >> n;
		memset(g, 0, sizeof(g));
		memset(x, 0, sizeof(x));
		memset(y, 0, sizeof(y));
		memset(z, 0, sizeof(z));
		for (int i = 0; i < n; i++)
		{
			scanf("%d%d%d%d%d%d", &r[i].x0, &r[i].y0, &r[i].z0, &r[i].x, &r[i].y, &r[i].z);
			r[i].id = i + 1;
			x[i * 2 + 1] = r[i].x0, x[i * 2 + 2] = r[i].x + r[i].x0;
			y[i * 2 + 1] = r[i].y0, y[i * 2 + 2] = r[i].y + r[i].y0;
			z[i * 2 + 1] = r[i].z0, z[i * 2 + 2] = r[i].z + r[i].z0;
		}
		sort(r, r + n);
		sort(x + 1, x + n * 2 + 1);
		sort(y + 1, y + n * 2 + 1);
		sort(z + 1, z + n * 2 + 1);
		xnum = unique(x + 1, x + n * 2 + 1) - (x + 1);
		ynum = unique(y + 1, y + n * 2 + 1) - (y + 1);
		znum = unique(z + 1, z + n * 2 + 1) - (z + 1);
		x[0] = y[0] = z[0] = -1;
		vol = 0;
		space = 0;
		for (int i = 1; i <= xnum; i++)
			X[x[i]] = i;
		for (int i = 1; i <= ynum; i++)
			Y[y[i]] = i;
		for (int i = 1; i <= znum; i++)
			Z[z[i]] = i;
		for (int i = 0; i < n; i++)
			draw(i, r[i].id);
		vector<coord>q;
		q.push_back(coord(0, 0, 0));
		while (!q.empty())
		{
			coord cd = q.back(); q.pop_back();
			int i = cd.x, j = cd.y, k = cd.z;
			for (int d = 0; d < 6; d++)
			{
				int nx = i + dx[d];
				int ny = j + dy[d];
				int nz = k + dz[d];
				if (nx >= 0 && ny >= 0 && nz >= 0 && nx <= xnum  && ny <= ynum  & nz <= znum  && !g[nx][ny][nz])
				{
					g[nx][ny][nz] = -1;
					q.push_back(coord(nx, ny, nz));
				}
			}
		}
		for (int i = 1; i < xnum;i++)
		for (int j = 1; j < ynum;j++)
		for (int k = 1; k < znum; k++)
		{
			int l1 = x[i + 1] - x[i], l2 = y[j + 1] - y[j], l3 = z[k + 1] - z[k];
			if (g[i][j][k] != -1)vol += l1*l2*l3;
			for (int d = 0; d < 6;d++)
			if (g[i][j][k] != -1 && g[i + dx[d]][j + dy[d]][k + dz[d]] == -1)
				space += dx[d] ? l2*l3 : dy[d] ? l1*l3 : l1*l2;
		}
		cout << space << ' ' << vol << endl;
	}
	return 0;
}
