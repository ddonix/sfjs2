#include <iostream>
using namespace std;

const int maxn = 10;
int w,h, n;

int ans;

struct Polyom
{
	int p[maxn];
	int n,s,w,e;
};

Polyom po;
int polyomino(int d)
{
	if (d == n)
	{
		ans++;
		return true;
	}
	else
	{
		int pre = po[d-1];
	}
}


int main()
{
	while(cin>>n>>w>>h)
	{
		ans = 0;
		po.n = po.s = po.w = po.e = 0;
		polyomino(1);
		cout<<ans<<endl;
	}
}
