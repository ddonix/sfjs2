#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

int dd;
int n;
set<int> se;

bool ida(int d, int last, int cmax)
{
	if (d == dd)
		return se.count(n);
	else
	{
		if (cmax*(1<<(dd-d)) < n)
			return false;

		for(auto it1 = se.begin(); it1 != se.end(); it1++)
		{
			for(int i = 0; i <= 1; i++)
			{
				int t = last+(*it1)*(i ? -1 : 1);
				pair<set<int>::iterator, bool> p = se.insert(t);
				if (!p.second)		//已存在了
					continue;
				if (ida(d+1, t,  t > cmax ? t : cmax))
					return true;
				se.erase(p.first);
			}
		}
		return false;
	}
}

int main()
{
	while(cin>>n && n)
	{
		for(dd = 0; dd < n; dd++)
		{
			se.clear();
			se.insert(1);
			if (ida(0, 1, 1))
				break;
		}
		cout<<dd<<endl;
	}
}
