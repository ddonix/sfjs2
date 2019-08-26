#include <iostream>
#include <cstring>
#include <set>
using namespace std;

const long long maxll = 0x7ffffffffffffff;
const int maxk = 5;
const int maxd = 10;
long long aa, bb;
set<long long> skip;
int k, T;
int dd;

long long best;
long long ans[maxd];

long long egyptianfraction(long long a, long long b, long long f, int d)
{
	long long t = a*f-b;
	long long res = maxll;
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
		long long t3 = b*f/t;
		long long t2 = (d-1)*b*f/t+1;
		
		for(long long x = (t3 > f) ? t3: f+1; x < best && x <= t2; x++)
		{
			if(skip.count(x) < 1)
			{
				long long r = egyptianfraction(t, b*f, x, d-1);
				if (r < res)
					res = r;
				if (r <= best && best < maxll)
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
			best = maxll;
			dd = d;
			for(long long f = bb/aa; aa*f < bb*d; f++)
			{
				int i;
				if (skip.count(f) < 1)
				{
					if (egyptianfraction(aa, bb, f, d) < maxll)
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
