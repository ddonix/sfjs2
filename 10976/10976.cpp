#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
	int k;
	while(cin>>k)
	{
		queue<pair<int, int> > res;
		int x, y, k2, n;
		int d;
		k2 = k*k;

		for(d = 1; d <= k; d++)
		{
			if(k2%d == 0)
			{
				x = k+k2/d;
				y = k+d;
				res.push(make_pair(x,y));
			}
		}
		n = res.size();
		cout<<n<<endl;
		for(int i = 0; i < n; i++)
		{
			x = res.front().first;	
			y = res.front().second;	
			res.pop();
			cout<<"1/"<<k<<" = "<<"1/"<<x<<" + 1/"<<y<<endl;
		}
	}
}
