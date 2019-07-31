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
		int mp;
		int time;
		bool flag;
		list<int> l;
		list<int>::iterator it;
		
		cin>>n>>m;
		for(int i = 0; i < n; i++)
		{
			cin>>t;
			if (i == m)
			{
				mp = t;
				t += 10;
			}
			l.push_back(t);
		}
		time = 0;
		flag = true;
		while(flag)
		{
			t = l.front();
			it = l.begin();
			for(it++; it != l.end(); it++)
			{
				if (*it > mp)
					break;
			}

		}
		cout<<time<<endl;
	}
}
