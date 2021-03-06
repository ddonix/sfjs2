/* uva 1604: 
 * 	分析：迷宫共有9*pow(6,8)=15116544种状态.
 * 	思路：bfs。判重麻烦一点，状态集太大了。
 */

#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

//wr 0 wb 1 rw 2 rb 3 bw 4 br 5
const int ds[6][4] = {	{2, 2, 5, 5}, {4, 4, 3, 3}, {0, 0, 4, 4}, {5, 5, 1, 1}, {1, 1, 2, 2}, {3, 3, 0, 0}};
const int de[4] = {-3, 3, -1, 1};

unsigned long pa[7][9];		//pa[i][j]的含义是：方块朝向i在位置j上的值.0~5表示6种方块朝向，6表示空格
unsigned long zero[9];
unsigned long mask;
unsigned long base[9];

int vis[15116544];
unsigned long ed;
int ede;

int inline getcube(const unsigned long & p, int pos)
{
	return (p >> (pos*3)) & 0x7;
}

void inline setcube(unsigned long & p, int pos, int c)
{
	p &= zero[pos];
	p |= pa[c][pos];
}

struct State
{
	unsigned long p;	//the puzzle array
	int e;			//the position of the empty cube
	unsigned long code;		//the code
	
	State(){}

	State news(int d)
	{
		State ns;
		ns.p = p;
		ns.e = e+de[d];
		
		int c = getcube(p, ns.e);
		setcube(ns.p, ns.e, 6);
		setcube(ns.p, e, ds[c][d]);

		ns.gencode();
		return ns;
	}

	void gencode()
	{
		int b = 0;
		code = base[8]*e;
		for(int i = 0; i < 9; i++)
		{
			if (i == e)
				continue;
			code += getcube(p, i)*base[b++];
		}
	}
	
	State(int x, int y)
	{
		e = 3*x+y;
		p = pa[6][e];
		code = base[8]*(3*x+y);
	}
	
	State(int e_, unsigned long p_)
	{
		e = e_;
		p = p_;
		gencode();
	}

	State(unsigned long c)
	{
		e = c/base[8];
		code = c;
		c = c%base[8];
		p = pa[6][e];
		
		int b = 7;
		for(int i = 8; i >= 0; i--)
		{
			if (i == e)
				continue;
			p |= pa[c/base[b]][i];
			c = c%base[b];
			b--;
		}
		p |= pa[6][e];
	}
};

State be;
void initialize()
{
	unsigned long b = 1;
	for(int i = 0; i < 9; i++)
	{
		base[i] = b;
		b = b*6;
	}
	
	for(unsigned long i = 0; i < 7; i++)
		for(int j = 0; j < 9; j++)
			pa[i][j] = (i << (3*j));
	
	unsigned long z = 7;
	unsigned long m = 3;
	mask = 0;
	for(int i = 0; i < 9; i++)
	{
		zero[i] = ~z;
		z = (z <<3);
		
		mask |= m;
		m = (m << 3);
	}
}

void bfs_r()		//反向bfs
{
	queue<pair<unsigned long, int> > q;

	const unsigned char bits[8] = {0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80};
	unsigned char b = 0; 
	do 
	{
		unsigned long p = ed;
		for(int j = 0; j < ede; j++)
			if (b & bits[j])
				p |= (1 << 3*j);
		for(int j = ede+1; j < 9; j++)
			if (b & bits[j-1])
				p |= (1 << 3*j);
		State s = State(ede, p);
		q.push(make_pair(s.code, -1));
		vis[s.code] = -1;
	}while(++b != 0);

	while(!q.empty())
	{
		pair<unsigned long, int> pa = q.front();
		q.pop();
		
		State s = State(pa.first);
		int pd = pa.second;

		if (vis[s.code] == -10)
			break;

		for(int d = 0; d < 4; d++)
		{
			int x = s.e/3;
			int y = s.e%3;
			if ((pd >= 2 && (d+pd) == 5) || (pd >= 0 && pd <= 1 && (d+pd) == 1))
				continue;
			if ((0 == x && 0 == d) || (2 == x && 1 == d) || (0 == y && 2 == d) || (2 == y && 3 == d))
				continue;
			State ns = s.news(d);
			if (!vis[ns.code])
			{
				vis[ns.code] = vis[s.code]-1;
				q.push(make_pair(ns.code, d));
			}
		}
	}
}

int bfs()
{
	if (vis[be.code] < 0)
		return -vis[be.code]-1;
	
	queue<pair<unsigned long, int> > q;
	q.push(make_pair(be.code, -1));
	vis[be.code] = 1;

	while(!q.empty())
	{
		pair<unsigned long, int> pa = q.front();
		q.pop();
		
		State s = State(pa.first);
		int pd = pa.second;

		if (vis[s.code] > 21)
			continue;

		for(int d = 0; d < 4; d++)
		{
			int x = s.e/3;
			int y = s.e%3;
			if ((pd >= 2 && (d+pd) == 5) || (pd >= 0 && pd <= 1 && (d+pd) == 1))
				continue;
			if ((0 == x && 0 == d) || (2 == x && 1 == d) || (0 == y && 2 == d) || (2 == y && 3 == d))
				continue;
			State ns = s.news(d);
			if (!vis[ns.code])
			{
				vis[ns.code] = vis[s.code]+1;
				q.push(make_pair(ns.code, d));
			}
			else if (vis[ns.code] < 0)
				return vis[s.code]-vis[ns.code]-1;
		}
	}
	return -1;

}

int main()
{
	int x,y,r;
	initialize();
	while(cin>>y>>x && x)
	{
		be = State(x-1, y-1);
		ed = 0;
		for(int i = 0; i < 9; i++)
		{
			char c;
			cin>>c;
			if ('W' == c)
				ed |= pa[0][i];
			else if ('R' == c)
				ed |= pa[2][i];
			else if ('B' == c)
				ed |= pa[4][i];
			else
			{
				ed |= pa[6][i];
				ede = i;
			}
		}
		memset(vis, 0, sizeof(vis));
		bfs_r();
		r = bfs();
		cout<<r<<endl;
	}
}
