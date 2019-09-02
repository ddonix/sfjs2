#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int maxn = 102;

int re[maxn][maxn];
int cu[maxn];

int t = 0;
int m,n;

int main()
{
	while(cin>>n>>m && n != 0)
	{
		memset(re, 0, sizeof(re));
		memset(cu, 0, sizeof(cu));
		t = 0;
		
		for(int i = 0; i < m; i++)
		{
			int b, a;
			cin>>b>>a;
			re[b][a] = 1;
		}
		
		bool flag = true;
		t = 0;
		while(flag && t < n)
		{
			int b, a;
			queue<int> q;
			for(a = 1; a <= n; a++)
			{
				for(b = 1; b <= n; b++)
				{
					if (re[b][a] == 1)
						break;
				}
				if (b > n)
				{
					if (0 == cu[a])
					{
						cout<<a<<" ";
						t++;
						cu[a] = 1;
						q.push(a);
					}
				}
			}
			while(!q.empty())
			{
				int a1 = q.front();
				q.pop();
				for(int a2= 1; a2 <= n; a2++)
					re[a1][a2] = 0;
			}
		}
		cout<<endl;
	}
}
