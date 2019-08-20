#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <sstream>

using namespace std;

const int maxr = 20;
const int maxc = 10;

int R, C;

struct Cell
{
	int v;			//value
	vector<int> exp;	//r*C+c; 10000: + , 10001:-, < 0: 无符号数
	char s[76];
	Cell() : v(10001){}
	Cell(int v_) : v(v_) {}
	Cell(char *s_) : v(10001) 
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
	bool flag[R*C], running = true;
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
		for(int i = 0; i < topu.size(); i++)
		{
			int r = topu[i]/C, c = topu[i]%C;
			printf("(%d, %d)\n", topu[i]/C, topu[i]%C);
		}
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
	}
}

int main()
{
	while(scanf("%d%d", &R, &C)==2 && R != 0)
	{
		char s[76];
		int v;
		memset(e, 0, sizeof(e));
		for(int i = 0; i < R; i++)
			for(int j = 0; j < C; j++)
			{
				scanf("%s", s);
				if (!(s[0] >= 'A' && s[0] <= 'T'))
				{
					stringstream ss(s);
					ss>>v;
					sheet[i][j] = Cell(v);
				}
				else
				{
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
							sheet[i][j].exp.push_back(10000);
							k++;
						}
						else if('-' == s[k])
						{
							sheet[i][j].exp.push_back(10001);
							k++;
						}
						else
						{
							int v, p;
							for(p = k+1; s[p] >= '0' && s[p] <= '9'; p++);
							stringstream ss(s+k);
							ss>>v;
							sheet[i][j].exp.push_back(-v);
							k = p;
						}
					}
				}
			}
		tp();
		for(int i = 0; i < R; i++)
			for(int j = 0; j < C; j++)
				sheet[i][j].v = 10001;
	}
}
