/* uva 11214: guarding the chessboard
 * 	题意：给定一个标记了部分位置的棋牌，要求在棋盘上放置最少个皇后，使得每个标记位置都能被至少一个皇后攻击。
 * 	分析：解决两个问题：
 * 	      1.是否满足条件，即每个标记位置都能被攻击。
 * 	      2.皇后放置的策略，使得能尽早收敛到结果。
 *      思路：1.整体框架ida。
 *            2.首先根据标记位置，确定待选的位置（能攻击到标记位置的才有可能被选)
 *            3.选择策略：按行放置
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 9;

char p[maxn][maxn];
int n, m;
int dd;

unsigned long bits[20] = {	0x1,	0x2,	0x4,	0x8,
				0x10,	0x20,	0x40,	0x80,
				0x100,	0x200,	0x400,	0x800,
				0x1000,	0x2000,	0x4000,	0x8000,
				0x10000,0x20000,0x40000,0x80000};

//行，列，斜，反斜
//行（列）：行(列)值相同为一行(列)
//斜（反斜）：列值加（减）行值相同为一斜（反斜）
unsigned long xvis, yvis, svis, rsvis;

bool isok()
{
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			if ('X' == p[i][j])
			{
				if (!((xvis & bits[i]) || (yvis & bits[j]) || (svis & bits[i+j]) || (rsvis & bits[i-j+maxn])))
					return false;
			}
	return true;
}

bool ida(int d, int x, int y)
{
	if (d == dd)
		return isok();
	else
	{
		for(int i = x; i < n; i++)
			for(int j = 0; j < m; j++)
			{
				if (!((xvis & bits[i]) && (yvis & bits[j]) && (svis & bits[i+j]) && (rsvis & bits[i-j+maxn])))
				{
					unsigned long b0 = xvis, b1 = yvis, b2 = svis, b3 = rsvis;
					xvis |= bits[i];
					yvis |= bits[j];
					svis |= bits[i+j];
					rsvis |= bits[i-j+maxn];
					if (ida(d+1, i, j))
						return true;
					xvis = b0;
					yvis = b1;
					svis = b2;
					rsvis = b3;
				}
			}
		return false;
	}
}


int main()
{
	int ka = 0;
	while(cin>>n && n)
	{
		cin>>m;
		for(int i = 0; i < n; i++)
		{
			string s;
			cin>>s;
			for(int j = 0; j < m; j++)
				p[i][j] = s[j];
		}
		xvis = yvis = svis = rsvis = 0;
		if (isok())
		{
			cout<<"Case "<<++ka<<": "<<1<<endl;
			continue;
		}
		for(dd = 1; dd < 5; dd++)
		{
			xvis = yvis = svis = rsvis = 0;
			if (ida(0, 0, 0))
				break;
		}
		cout<<"Case "<<++ka<<": "<<dd<<endl;
	}
}
