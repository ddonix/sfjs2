#include <iostream>
#include <cstring>

using namespace std;
const int maxn = 17;

bool prime[maxn*2];
int n;

int ring[maxn];
int vis[maxn];

void pr(int cur)
{
	if (cur == n)
	{
		for(int i = 0; i < n-1; i++)
			cout<<ring[i]<<" ";
		cout<<ring[n-1]<<endl;
	}
	else
	{
		for(int i = 1; i <= n; i++)
		{
			if (!vis[i])
			{
				if (prime[ring[cur-1]+i])
				{
					if (cur != n-1 || (cur == n-1 && prime[1+i]))
					{
						vis[i] = 1;
						ring[cur] = i;
						pr(cur+1);
						vis[i] = 0;
					}
				}
			}
		}
	}
}

int main()
{
	int ka = 0;
	bool first = true;
	memset(prime, 0, sizeof(prime));
	prime[2] = prime[3] = prime[5] = prime[7] = prime[11] = prime[13] = true;
	prime[17] = prime[19] = prime[23] = prime[29] = prime[31] = true;
	
	ring[0] = 1;
	vis[1] = 1;
	while(cin>>n)
	{
		if(first)
			first = false;
		else
			cout<<endl;
		
		cout<<"Case "<<++ka<<":"<<endl;
		if (n == 1)
			cout<<"1"<<endl;
		else if (n == 2)
			cout<<"1 2"<<endl;
		else
		{
			for(int i = 1; i < n; i++) ring[i] = 0;
			for(int i = 2; i <= n; i++) vis[i] = 0;
			pr(1);
		}
	}
}
