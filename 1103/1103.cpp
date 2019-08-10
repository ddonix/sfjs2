#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

const int maxn = 202;

int pic[maxn][maxn];
int idx[maxn][maxn];
int cid = 0;

int bm[16][4];

int m, n;

void dfs(int i, int j, int id)
{
	if(i < 0 || i >= m || j < 0 || j >= n || idx[i][j] || !pic[i][j])
		return;
	idx[i][j] = id;
	for(int ii = -1; ii <= 1; ii++)
		for(int jj = -1; jj <= 1; jj++)
		{
			if (ii || jj)
				dfs(i+ii, j+jj, id);
		}
}

char dfs2(int i, int j)
{
	return 'A';
}

int main()
{
	int ka = 1;
	for(char i = 0; i < 16; i++)
	{
		if(i & 0x8) bm[i][0] = 1;
		if(i & 0x4) bm[i][1] = 1;
		if(i & 0x2) bm[i][2] = 1;
		if(i & 0x1) bm[i][3] = 1;
	}
	while(cin>>m>>n && m != 0)
	{
		string s;
		queue<pair<int, int> > q;
		for(int i = 0; i < m; i++)
		{
			cin>>s;
			for(int j = 0; j < n; j++)
				memcpy(&pic[i][j*4] , bm[(s[j] >= '0' && s[j] <= '9') ? (s[j]-'0') : (10+s[j]-'a')], 4*sizeof(int));
		}
		n *= 4;
	
		cid = 0;
		memset(idx, 0, sizeof(idx));	
		for(int i = 0; i < m; i++)
			for(int j = 0; j < n; j++)
			{
				if (pic[i][j] && (idx[i][j] == 0))
				{
					dfs(i, j, ++cid);
					q.push(make_pair(i,j));
				}
			}
		cout<<"Case "<<ka++<<": ";
		while(!q.empty())
		{
			pair<int, int> p = q.front();
			q.pop();
			char t = dfs2(p.first, p.second);
			cout<<t;
		}
		cout<<endl;
	}
}
