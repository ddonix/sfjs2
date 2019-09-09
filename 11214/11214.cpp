/* uva 11214: guarding the chessboard
 * 	题意：给定一个标记了部分位置的棋牌，要求在棋盘上放置最少个皇后，使得每个标记位置都能被至少一个皇后攻击。
 * 	分析：解决两个问题：
 * 	      1.是否满足条件，即每个标记位置都能被攻击。
 * 	      2.皇后放置的策略，使得能尽早收敛到结果。
 *      思路：1.整体框架ida。
 *            2.选择策略：放一粒皇后，标记攻击的行列斜反斜，然后每次找还没有被攻击的行列斜反斜放皇后。快速收敛。
 */
#include <iostream>
#include <cstring>
using namespace std;
const int maxn = 9;

char p[maxn][maxn];
int n, m;
int dd;

//行，列，斜，反斜
//行（列）：行(列)值相同为一行(列)
//斜（反斜）：列值加（减）行值相同为一斜（反斜）
bool xvis[maxn], yvis[maxn], svis[maxn*2], rsvis[maxn*2];

bool isok()
{
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			if (('X' == p[i][j]) && (!(xvis[i] || yvis[j] || svis[i+j] || rsvis[i-j+maxn])))
				return false;
	return true;
}

bool ida(int d, int x, int y)
{
	if (d == dd)
		return isok();
	else
	{
		for(int i = x; i < n; i++)
			for(int j = (i == x) ? y+1 : 0; j < m; j++)
			{
				if (!(xvis[i] && yvis[j] && svis[i+j] && rsvis[i-j+maxn]))
				{
					bool f0 = xvis[i], f1 = yvis[j], f2 = svis[i+j], f3 = rsvis[i-j+maxn];
					xvis[i] = yvis[j] = svis[i+j] = rsvis[i-j+maxn] = true;
					if (ida(d+1, i, j))
						return true;
					xvis[i] = f0;
					yvis[j] = f1;
					svis[i+j] = f2;
					rsvis[i-j+maxn] = f3;
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
		memset(xvis, 0, sizeof(xvis));
		memset(yvis, 0, sizeof(yvis));
		memset(svis, 0, sizeof(svis));
		memset(rsvis, 0, sizeof(rsvis));
		if (isok())
		{
			cout<<"Case "<<++ka<<": "<<1<<endl;
			continue;
		}
		for(dd = 1; dd < 5; dd++)
		{
			if (ida(0, 0, -1))
				break;
		}
		cout<<"Case "<<++ka<<": "<<dd<<endl;
	}
}
