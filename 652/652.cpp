/* 该双向广搜了
 *
 *
 */
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

int fact[9];

const char direction[]={'r', 'l', 'd', 'u'};
const int dx[] = {0,  0, -1, 1};
const int dy[] = {-1, 1,  0, 0};
const int dd[4][3] = {{0,2,3}, {1,2,3}, {0,1,2}, {0,1,3}};


int encode(int *s)	//encode
{
	int code = 0;
	for(int i = 8; i > 0; i--)
	{
		int m = 0;
		for(int j = 0; j < i; j++)
			if (s[j] > s[i]) m++;
		code += fact[i]*m;
	}
	return code;
}

int bg[9];		//begin state
int bgc, edc;
bool vis[362880];	//反向bfs 9! = 362880
int state[362880][10];	//所有state
int fa[362880];		//反向 father	print路径
int di[362880];		//反向 direction

int nextState(int code, int d)
{
	int p,np,ncode,nx,ny;
	p = state[code][9];
	nx =  p/3+dx[d];
	ny =  p%3+dy[d];
	if (nx < 0 || nx > 2 || ny < 0 || ny > 2)
		return -1;
	np = nx*3+ny;
	
	state[code][p] = state[code][np];
	state[code][np] = 0;
	ncode = encode(state[code]);
	if (state[ncode][0] < 0)
	{
		memcpy(state[ncode], state[code], sizeof(int)*9);
		state[ncode][9] = np;
	}
	state[code][np] = state[code][p];
        state[code][p] = 0;
	return ncode;
}

void printans(int code)
{
	char ans[100];
	int cur;
	int len = 0;
	cur = code;
	while(cur != edc)
	{
		printf("%c", direction[di[cur]]);
		cur = fa[cur];
	}
	printf("\n");
}


//打表
void bfs_r()
{
	queue<int> q;
	q.push(edc);
	vis[edc] = true;
	
	while(!q.empty())
	{
		int code;
		code = q.front();
		q.pop();
		
		int d = di[code];
		for(int i = 0; i < 3; i++)
		{
			int ncode;
			ncode = nextState(code, dd[d][i]);
			if (ncode >= 0 && !vis[ncode])
			{
				vis[ncode] = true;
				fa[ncode] = code;
				di[ncode] = dd[d][i];
				q.push(ncode);
			}
		}
	}
}

void init()
{
	int b = 1;
	for(int i = 1; i < 9; i++)
	{
		b *=  i;
		fact[i] = b;
	}
	for(int i = 0; i < 362880; i++)
		state[i][0] = -1;
	
	int ed[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
	edc = encode(ed);
	for(int i = 0; i < 9; i++)
		state[edc][i] = ed[i];
	state[edc][9] = 8;
	
	memset(vis, 0, sizeof(vis));
	bfs_r();
}

int main()
{
	int T;
	char c[2];
	init();
	scanf("%d", &T);
	while(T--)
	{
		for(int i = 0; i < 9; i++)
		{
			scanf("%s", c);
			bg[i] = (c[0] == 'x' ? 0 : c[0]-'0');
		}
		bgc = encode(bg);
		if (!vis[bgc])
			printf("unsolvable\n");
		else
			printans(bgc);
		if (T)
			printf("\n");
	}
}
