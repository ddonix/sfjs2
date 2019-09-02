#include <iostream>
#include <list>

using namespace std;

int main()
{
	int ka;
	cin>>ka;
	while(ka--)
	{
		int n,m,t;
		int mp,maxp;
		int time;
		bool flag;
		list<int> l;
		list<int>::iterator it;
		
		cin>>n>>m;
		maxp = 1;
		for(int i = 0; i < n; i++)
		{
			cin>>t;
			if(t > maxp)
				maxp = t;
			if (i == m)
			{
				mp = t;
				t = -t;
			}
			l.push_back(t);
		}
		time = 0;
		flag = true;
		while(flag)
		{
			t = l.front();
			l.pop_front();
			if(t < 0)
			{
				if (mp >= maxp)
				{
					time++;
					flag = false;
					break;
				}
				else
				{
					l.push_back(t);
				}
			}
			else
			{
				if (t >= maxp)
				{
					time++;
					maxp = 1;
					for(it = l.begin(); it != l.end(); it++)
					{
						int p = (*it > 0) ? *it : -1*(*it);
						if(p > maxp) 
							maxp = p;
					}
				}
				else
				{
					l.push_back(t);
				}
			}

		}
		cout<<time<<endl;
	}
}
