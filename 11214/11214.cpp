/* uva 11214: guarding the chessboard
 * 	题意：给定一个标记了部分位置的棋牌，要求在棋盘上放置最少个皇后，使得每个标记位置都能被至少一个皇后攻击。
 * 	分析：解决两个问题：
 * 	      1.是否满足条件，即每个标记位置都能被攻击。
 * 	      2.皇后放置的策略，使得能尽早收敛到结果。
 *      思路：1.整体框架ida。
 *            2.运算采用位运算，方便判断是否满足条件.
 *            3.首先根据标记位置，确定待选的位置（能攻击到标记位置的才有可能被选
 *            4.选择策略：每次从待选位置中选择攻击标记数量最多的先选择.
 *            5.剪枝策略: 待选前面几项的数量和，比剩余标记还要少.
 *	      6.棋盘最多81=9*9个位置，用一个128位unsigned long long表示
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 9;

unsigned long long bits[maxn*maxn];
unsigned long long ed;			//标记的棋盘
unsigned long long queen[maxn*maxn];
int n, m;
int dd;

int getsetb(const unsigned long long &a)
{
	int r = 0;
	for(int i = 0; i < n*m; i++)
		if (a & bits[i])
			r++;
	return r;
}

void initialize_g()
{
	unsigned long long b = 1;
	for(int i = 0; i < maxn*maxn; i++)
	{
		bits[i] = b;
		b = (b << 1);
	}
}

void initialize()
{
	for(int x = 0; x < n; x++)
		for(int y = 0; y < m; y++)
		{
			unsigned long long a = 0;
			for(int i = 0; i < m; i++)
				a |= bits[x*m+i];
			for(int i = 0; i < n; i++)
				a |= bits[i*m+y];
			for(int i = -max(n,m)+1; i < max(n,m); i++)
			{
				if (x+i >= 0 && x+i < n && y+i >= 0 && y+i< m)
					a |= bits[(x+i)*m+(y+i)];
				if (x+i >= 0 && x+i < n && y-i >= 0 && y-i < m)
					a |= bits[(x+i)*m+(y-i)];
			}
			queen[x*m+y] = (a & ed);
		}
}

struct Queen
{
	int q;
	unsigned long long a;
	int an;

	Queen(int q_, unsigned long long & b)
	{
		q = q_;
		a = (b & queen[q]);
		an = getsetb(a);
	}

	bool operator<(const Queen & right)
	{
		return an > right.an;
	}
};

unsigned long long vis;
bool ida(int d, unsigned long long b)
{
	if (d == dd)
	{
		if (b == 0)
			return (b == 0);
		return (b == 0);
	}
	else
	{
		vector<Queen> v;
		for(int i = 0; i < n*m ; i++)
			if (!(vis & bits[i]))
				v.push_back(Queen(i, b));
		
		sort(v.begin(), v.end());
		int rn = getsetb(b);
		int r = 0;
		for(int i = 0; i < (dd-d); i++)
			r += v[i].an;
		if (r < rn)
			return false;
		for(int i = 0; i < v.size(); i++)
		{
			vis |= bits[v[i].q];
			if (ida(d+1, b & (~v[i].a)))
				return true;
			vis &= ~bits[v[i].q];
		}
		return false;
	}
}


int main()
{
	int ka = 0;
	initialize_g();
	while(cin>>n && n)
	{
		cin>>m;
		ed = 0;
		for(int i = 0; i < n; i++)
		{
			string s;
			cin>>s;
			for(int j = 0; j < m; j++)
				if ('X' == s[j])
					ed |= bits[i*m+j];
		}
		initialize();
		for(dd = 0; dd < 2*maxn; dd++)
		{
			vis = 0;
			if (ida(0, ed))
				break;
		}
		cout<<"Case "<<++ka<<": "<<dd<<endl;
	}
}
