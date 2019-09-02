#include <iostream>
using namespace std;

int n, v1, p1, v2, p2;
int ans;


void enumerate(int type, int num)
{
	int pp;
	if (2 == type)
	{
		for(int i = 0; i <= num; i++)
		{
			pp = i*p2;
			if ((n-i*v2)>=v1)
				pp += ((n-i*v2)/v1)*p1;
			ans = (pp > ans) ? pp : ans;
		}
	}
	else
	{
		for(int i = 0; i <= num; i++)
		{
			pp = i*p1;
			if ((n-i*v1)>=v2)
				pp += ((n-i*v1)/v2)*p2;
			ans = (pp > ans) ? pp : ans;
		}
	}

}

int algo()
{
	int pp = 0;
	int t1, t2;
	if (n < v1*v1 && n < v2*v2 && n < v1*v2) 
	{
		if (v1 > v2)
			enumerate(1, n/v1);
		else
			enumerate(2, n/v2);
	}
	else if (p1*v1 >= p2*v1)
		enumerate(2, n/v2 < (v1-1) ? n/v2 : (v1-1));
	else
		enumerate(1, n/v1 < (v2-1) ? n/v1 : (v2-1));
}

int main()
{
	int T;
	cin>>T;
	for(int ka = 1; ka <= T; ka++)
	{
		cin>>n>>v1>>p1>>v2>>p2;
		ans = 0;
		algo();
		cout<<"Case #"<<ka<<": "<<ans<<endl;
	}
}
