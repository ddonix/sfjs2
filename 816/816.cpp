#include <iostream>
#include <vector>

using namespace std;

struct Node
{
	bool walk[4][4];
	void clear()
	{
		for(int i = 0; i < 4; i++)
			for(int j = 0; j < 4; j++)
				walk[i][j] = false;
	}
};

Node maze[10][10];

pair<int, int> spos;
pair<int, int> epos;
char sdirect;

void dfs(int r, int c, int d)
{
}

int main()
{
	string name;
	while(cin>>name && name != "END")
	{
		cin>>spos.first>>spos.second>>sdirect>>epos.first>>epos.second;
		//clear maze
		for(int i = 1; i <=9; i++)
			for(int j = 1; j <=9; j++)
				maze[i][j].clear();
		
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
					maze[r][c].walk[0][1] = false;
					for(int i = 1; i < s.length(); i++)
					{
						if ('F' == s[i]) maze[r][c].walk[0][0] = true;
						if ('L' == s[i]) maze[r][c].walk[0][2] = true;
						if ('R' == s[i]) maze[r][c].walk[0][3] = true;
					}
				}
				if('S' == s[0])
				{
					maze[r][c].walk[1][0] = false;
					for(int i = 1; i < s.length(); i++)
					{
						if ('F' == s[i]) maze[r][c].walk[1][1] = true;
						if ('L' == s[i]) maze[r][c].walk[1][3] = true;
						if ('R' == s[i]) maze[r][c].walk[1][2] = true;
					}
				}
				else if('W' == s[0])
				{
					maze[r][c].walk[2][3] = false;
					for(int i = 1; i < s.length(); i++)
					{
						if ('F' == s[i]) maze[r][c].walk[2][2] = true;
						if ('L' == s[i]) maze[r][c].walk[1][1] = true;
						if ('R' == s[i]) maze[r][c].walk[1][0] = true;
					}
				}
				else
				{
					maze[r][c].walk[3][2] = false;
					for(int i = 1; i < s.length(); i++)
					{
						if ('F' == s[i]) maze[r][c].walk[3][3] = true;
						if ('L' == s[i]) maze[r][c].walk[3][0] = true;
						if ('R' == s[i]) maze[r][c].walk[3][1] = true;
					}
				}
			}
		}
		
		cout<<name<<endl;
		cout<<"No Solution Possibl"<<endl;
	}
}
