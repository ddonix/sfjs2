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

const char direction[]={'l', 'r', 'u', 'd'};
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

int bg[9], ed[9];	//begin state , end state
int bgc, edc;
int vis[362880];	//9! = 362880
int state[362880][10];	//所有state
int fa[362880];		//father	print路径
int di[362880];		//direction

int insertstate(int *s)
{
	int code = encode(s);
	if (state[code][0] < 0)
	{
		int i;
		for(i = 0; s[i]; i++);
		memcpy(state[code], s, sizeof(int)*9);
		state[code][9] = i;
	}
	return code;
}

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
	
	for(int i = 0; i < 8; i++)
		ed[i] = i+1;
	ed[8] = 0;
	edc = insertstate(ed);
}

void bfs()
{
	queue<int> q;
	bool running = true;
	int fa1, fa2;
	int ff;
	q.push(bgc);
	q.push(edc);
	vis[bgc] = 1;
	vis[edc] = 2;
	
	while(!q.empty() && running)
	{
		int code;
		code = q.front();
		q.pop();
		
		int d = di[code];
		for(int i = 0; i < 3 && running; i++)
		{
			int ncode;
			ncode = nextState(code, dd[d][i]);
			if (ncode >= 0)
			{
				if (!vis[ncode])
				{
					vis[ncode] = vis[code];
					fa[ncode] = code;
					di[ncode] = dd[d][i];
					q.push(ncode);
				}
				else
				{
					//喜相逢
					if (vis[ncode] != vis[code])
					{
						running = false;
						fa1 = (vis[code] == 1) ? code : ncode;
						fa2 = (vis[code] == 1) ? ncode : code;
						ff = (vis[code] == 1) ? dd[d][i]:(dd[d][i]+(dd[d][i]%2 ? -1 : 1));
					}
				}
			}
		}
	}
	if (running)
		printf("unsolvable\n\n");
	else
	{
		char ans[100];
		int cur;
		int len = 0;
		cur = fa1;
		while(cur != bgc)
		{
			ans[len++] = direction[di[cur]];
			cur = fa[cur];
		}
		for(int i = 0; i < len; i++)
			printf("%c", ans[len-1-i]);
		printf("%c", direction[ff]);
		cur = fa2;
		while(cur != edc)
		{
			int dd = di[cur];
			dd = (dd%2) ? dd-- : dd++;
			printf("%c", direction[dd]);
			cur = fa[cur];
		}
		printf("\n\n");
	}
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
		bgc = insertstate(bg);
		memset(vis, 0, sizeof(vis));
		bfs();
	}
}
