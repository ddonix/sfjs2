#include <iostream>
#include <cstring>
#include <set>
using namespace std;

const int maxk = 5;
const int maxd = 10;
int aa, bb, k, T;
set<int> skip;

int best;
int dd;
int ans[maxd];

int maxx = 0;

int egyptianfraction(int a, int b, int f, int d)
{
	int t = a*f-b;
	int res = 0x7fffffff;
	if (d == 1)
	{
		if (t == 0)
		{
			if (f < best)
			{
				ans[dd-1] = f;
				best = f;
			}
			return f;
		}
		return res;
	}
	else
	{
		if (t <= 0 || b*f <= 0)
			return res;
		int t3 = (double)b*(double)f/(double)t;
		int t2 = (double)(d-1)*(double)b*(double)f/(double)t+1;
		
		for(int x = (t3 > f) ? t3: f+1; x < best && x <= t2; x++)
		{
			if(skip.count(x) < 1)
			{
				int r = egyptianfraction(t, b*f, x, d-1);
				if (r < res)
					res = r;
				if (r <= best && best < 0x7fffffff)
					ans[dd-d] = f;
			}
		}
		return res;
	}
}

int main()
{
	int ka = 1;
	cin>>T;
	for(; ka <= T; ka++)
	{
		cin>>aa>>bb>>k;
		skip.clear();
		for(int i = 0; i < k; i++)
		{
			int temp;
			cin>>temp;
			skip.insert(temp);
		}
		cout<<"Case "<<ka<<": "<<aa<<"/"<<bb<<"=";
		bool ok = true;
		int d;
		for(d = 1; d < maxd && ok; d++)
		{
			best = 0x7fffffff;
			dd = d;
			for(int f = bb/aa; aa*f < bb*d; f++)
			{
				int i;
				if (skip.count(f) < 1)
				{
					if (egyptianfraction(aa, bb, f, d) < 0x7ffffff)
						ok = false;
				}
			}
		}
		cout<<"1/"<<ans[0];
		for(int i = 1; i < d-1; i++)
			cout<<"+1/"<<ans[i];
		cout<<endl;
	}
}
