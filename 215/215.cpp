#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <sstream>

using namespace std;

const int maxr = 22;
const int maxc = 12;

int R, C;
struct Cell
{
	char s[80];
	int v;			//value
	vector<int> exp;	//r*C+c; 1000000: + , 1000001:-, < 0: 无符号数
	Cell(){}
	Cell(char *s_)
	{
		strcpy(s, s_);
	}
};

Cell sheet[maxr][maxc];
bool e[maxr*maxc][maxr*maxc];

void tp()
{
	int i, j;
	vector<int> topu;
	bool flag[maxr*maxc], running = true;
	memset(flag, 0, sizeof(flag));
	while(running)
	{
		if (topu.size() == R*C)
			break;
		running = false;
		for(i = 0; i < R*C; i++)
		{
			if (flag[i])
				continue;
			for(j = 0; j < R*C && !e[i][j]; j++);
			if(j < R*C)
				continue;
			running = true;
			topu.push_back(i);
			flag[i] = true;
			for(j = 0; j < R*C; j++)
				e[j][i] = 0;
		}
	}
	if (topu.size() == R*C)
	{
		for(int i = 0; i < R*C; i++)
		{
			int r=topu[i]/C, c=topu[i]%C;
			int v = 0;
			int add = 1;
			for(int j = 0; j < sheet[r][c].exp.size();j++)
			{
				int e = sheet[r][c].exp[j];
				if (e < 0)
					v += -e*add;
				else if (e == 1000000)
					add = 1;
				else if (e == 1000001)
					add = -1;
				else
					v += sheet[e/C][e%C].v*add;
			}
			sheet[r][c].v = v;
		}
		printf(" %6d", 0);
		for(int i = 1; i < C; i++)
			printf("%6d", i);
		printf("\n");
		for(int i = 0; i < R; i++)
		{
			printf("%c", 'A'+i);
			for(int j = 0; j < C; j++)
				printf("%6d", sheet[i][j].v);
			printf("\n");
		}
		printf("\n");
	}
	else
	{
		for(int i = 0; i < R*C; i++)
		{
			if (!flag[i])
			{
				int r=i/C, c=i%C;
				printf("%c%c: %s\n", ('A'+r), ('0'+c), sheet[r][c].s);
			}
		}
		printf("\n");
	}
}

int main()
{
	while(scanf("%d%d", &R, &C)==2 && R)
	{
		char s[80];
		int v, len;
		memset(e, 0, sizeof(e));
		for(int i = 0; i < R; i++)
			for(int j = 0; j < C; j++)
			{
				scanf("%s", s);
				int a = i*C+j, b;
				sheet[i][j] = Cell(s);
				for(int k = 0; k < strlen(s); )
				{
					if (s[k] >= 'A' && s[k] <= 'T')
					{
						b = (s[k]-'A')*C+(s[k+1]-'0');
						sheet[i][j].exp.push_back(b);
						e[a][b] = true;
						k += 2;
					}
					else if('+' == s[k])
					{
						sheet[i][j].exp.push_back(1000000);
						k++;
					}
					else if('-' == s[k])
					{
						sheet[i][j].exp.push_back(1000001);
						k++;
					}
					else
					{
						int v, p;
						for(p = k+1; p < strlen(s) && s[p] >= '0' && s[p] <= '9'; p++);
						stringstream ss(s+k);
						ss>>v;
						sheet[i][j].exp.push_back(-v);
						k = p;
					}
				}
			}
		tp();
		for(int i = 0; i < R; i++)
			for(int j = 0; j < C; j++)
				sheet[i][j].exp.clear();
	}
}
