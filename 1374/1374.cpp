#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

int dd;
int n;
set<int> se;

bool ida(int d, int cmax)
{
	if (d == dd)
		return se.count(n);
	else
	{
		if (cmax*(1<<(dd-d)) < n)
			return false;
		
		pair<set<int>::iterator, bool> p;
		int t = cmax*2;
		auto it = se.insert(t).first;
		if (ida(d+1, t))
			return true;
		se.erase(it);
		for(auto it1 = se.begin(); it1 != se.end(); it1++)
		{
			if (*it1 == cmax)
				continue;
			for(int i = 0; i < 1; i++)
			{
				int t = cmax+(*it1)*(i ? -1 : 1);
				p = se.insert(t);
				if (!p.second)
					continue;
				if (ida(d+1, cmax > t ? cmax : t))
					return true;
				se.erase(p.first);
			}
		}
		for(auto it = se.begin(); it != se.end(); it++)
			for(auto it1 = se.begin(); it1 != se.end(); it1++)
			{
				if (*it == cmax || *it1 == cmax)
					continue;
				for(int i = 0; i < 1; i++)
				{
					int t = (*it)+(*it1)*(i ? -1 : 1);
					p = se.insert(t);
					if (!p.second)
						continue;
					if (ida(d+1, cmax > t ? cmax : t))
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
			if (ida(0, 1))
				break;
		}
		cout<<dd<<endl;
	}
}
