#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

const int maxn = 102;
int re[maxn][maxn];

int m,n;

int bfs()
{
	
}

int main()
{
	while(cin>>n>>m && n != 0)
	{
		memset(re, 0, sizeof(re));
		
		for(int i = 0; i < m; i++)
		{
			int b, a;
			cin>>b>>a;
			re[b][a] = 1;
		}
		
		
		
		for(int i = 1; i < n; i++)
			cout<<i<<" ";
		cout<<n<<endl;
	}
}
