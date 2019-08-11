#include <iostream> 
#include <vector>
#include <stack>
#include <queue>
#include <cstring>

using namespace std;


int maze[10][10][4][4];
int idx[10][10][4];

struct Node
{
	int r;
	int c;
	int direct;
	Node(){}
	Node(int rr, int cc, int d) : r(rr), c(cc), direct(d) {}
};

Node father[10][10][4];

pair<int, int> spos;
pair<int, int> epos;
char sdirect;
int edirect;

bool bfs()
{
	queue<pair<pair<int,int>, int> > q;
	if('N' == sdirect) q.push(make_pair(make_pair(spos.first-1, spos.second), 0));
	if('S' == sdirect) q.push(make_pair(make_pair(spos.first+1, spos.second), 1));
	if('W' == sdirect) q.push(make_pair(make_pair(spos.first, spos.second-1), 2));
	if('E' == sdirect) q.push(make_pair(make_pair(spos.first, spos.second+1), 3));
	while(!q.empty())
	{
		int r, c, direct;
		pair<pair<int,int>, int>  w = q.front();
		q.pop();
		r = w.first.first;
		c = w.first.second;
		direct = w.second;
		
		
		if (idx[r][c][direct])
			continue;
		
		idx[r][c][direct] = 1;
		if (w.first == epos)
		{
			edirect = direct;
			return true;
		}
		
		if(maze[r][c][direct][0]) 
		{
			q.push(make_pair(make_pair(r-1, c), 0));
			father[r-1][c][0] = Node(r,c,direct);
		}
		if(maze[r][c][direct][1]) 
		{
			q.push(make_pair(make_pair(r+1, c), 1));
			father[r+1][c][1] = Node(r,c,direct);
		}
		if(maze[r][c][direct][2])
		{
			q.push(make_pair(make_pair(r, c-1), 2));
			father[r][c-1][2] = Node(r,c,direct);
		}
		if(maze[r][c][direct][3]) 
		{
			q.push(make_pair(make_pair(r, c+1), 3));
			father[r][c+1][3] = Node(r,c,direct);
		}
	}
	return false;
}

void print_trace()
{
	stack<Node> trace;
	pair<int, int> p,p1;
	int direct, t;

	p = epos;
	direct = edirect;
	while(p != spos)
	{
		trace.push(p);
		p.first = father[p1.first][p1.second][direct].r;
		p.second = father[p1.first][p1.second][direct].c;
		direct = father[p1.first][p1.second][direct].direct;
	}
	cout<<"()()"<<endl;
}

int main()
{
	string name;
	while(cin>>name && name != "END")
	{
		cin>>spos.first>>spos.second>>sdirect>>epos.first>>epos.second;
		//clear maze and idx
		memset(maze, 0, sizeof(maze));
		memset(idx, 0, sizeof(idx));
		
		int r, c;
		//read maze
		while(cin>>r && r != 0)
		{
			cin>>c;
			string s;
			while(cin>>s && s!="*")
			{
				if('N' == s[0])
				{
					maze[r][c][0][1] = false;
					for(int i = 1; i < s.length(); i++)
					{
						if ('F' == s[i]) maze[r][c][0][0] = true;
						if ('L' == s[i]) maze[r][c][0][2] = true;
						if ('R' == s[i]) maze[r][c][0][3] = true;
					}
				}
				if('S' == s[0])
				{
					maze[r][c][1][0] = false;
					for(int i = 1; i < s.length(); i++)
					{
						if ('F' == s[i]) maze[r][c][1][1] = true;
						if ('L' == s[i]) maze[r][c][1][3] = true;
						if ('R' == s[i]) maze[r][c][1][2] = true;
					}
				}
				else if('W' == s[0])
				{
					maze[r][c][2][3] = false;
					for(int i = 1; i < s.length(); i++)
					{
						if ('F' == s[i]) maze[r][c][2][2] = true;
						if ('L' == s[i]) maze[r][c][2][1] = true;
						if ('R' == s[i]) maze[r][c][2][0] = true;
					}
				}
				else
				{
					maze[r][c][3][2] = false;
					for(int i = 1; i < s.length(); i++)
					{
						if ('F' == s[i]) maze[r][c][3][3] = true;
						if ('L' == s[i]) maze[r][c][3][0] = true;
						if ('R' == s[i]) maze[r][c][3][1] = true;
					}
				}
			}
		}
		
		cout<<name<<endl;
		memset(idx, 0, sizeof(idx));
		memset(father, 0, sizeof(father));
		if (bfs())
			print_trace();
		else
			cout<<"No Solution Possibl"<<endl;
	}
}