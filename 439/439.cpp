#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int dr[] = {-2,-1, 1, 2,  2,  1, -1, -2};
int dc[] = { 1, 2, 2, 1, -1, -2, -2, -1};
struct Position
{
	int r;
	int c;
	Position(){}
	Position(int r_, int c_) : r(r_), c(c_){}
	Position(string s)
	{
		r = s[1]-'1';
		c = s[0]-'a';
	};

	Position next(int i)
	{
		Position p = Position(r+dr[i], c+dc[i]);
		return p;
	}

	bool isValid()
	{
		return (r >= 0 && r < 8) && (c >= 0 && c < 8);
	}
	bool operator==(const Position & b)
	{
		return (r == b.r) && (c == b.c);
	}
};

int vis[8][8];

Position b, e;
int bfs()
{
	memset(vis, 0, sizeof(vis));
	queue<Position> q;
	
	q.push(b);
	vis[b.r][b.c] = 1;
	
	while(!q.empty())
	{
		Position p = q.front();
		q.pop();
		if(p == e)
			return vis[e.r][e.c];
		for(int i = 0; i < 8; i++)
		{
			Position n = p.next(i);
			if (n.isValid())
			{
				if (!vis[n.r][n.c])
				{
					q.push(n);
					vis[n.r][n.c] = vis[p.r][p.c]+1;
				}
			}
		}
	}
}

int main()
{
	string s1,s2;
	while(cin>>s1>>s2)
	{
		b = Position(s1);
		e = Position(s2);
		cout<<"To get from "<<s1<<" to "<<s2<<" takes "<<bfs()-1<<" knight moves."<<endl;
	}
}
