#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;


const int maxn = 10;
int R, C;
struct Point
{
	int r;
	int c;
	Point():r(0), c(0){}
	Point(int r_, int c_) : r(r_), c(c){}
	bool isValid()
	{
		return r >= 1 && r <= R && c >= 1 && c <= C;
	}
};

int dielayout[7][5] =  {{0, 0, 0, 0, 0}, 
						{6, 5, 4, 3, 2},
						{5, 1, 3, 6, 4},
						{4, 6, 5, 1, 2},
						{3, 2, 1, 5, 6},
						{2, 4, 6, 3, 1},
						{1, 2, 3, 4, 5}};
struct Die
{
	int t;
	int f;
	Die move(int d)		//0:l, 1:r, 2:u, 3:d
	{
		
	}
};

int maze[maxn][maxn];
Point sp;
Die sd;
Point vis[maxn][maxn][6][6];

int bfs()
{
}

int main()
{
	string s;
	while(cin>>s && s != "END")
	{
		cin>>R>>C;
		cin>>sp.r>>sp.c;
		cin>>sd.t>>sd.f;
		for(int r = 1; r <= R; r++)
			for(int c = 1; c <= C; c++)
				cin>>maze[r][c];
		cout<<s<<endl;
	}
}
