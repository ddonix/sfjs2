#include <iostream>
#include <set>

using namespace std;

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		int min, max, middle;
		int x,y;
		set<long long> s;
		cin>>n;

		min = 10000;
		max = -10000;
		for(int i = 0; i < n; i++)
		{
			cin>>x>>y;
			if (x > max)
				max = x;
			if (x < min)
				min = x;
			s.insert(x | (long long) y << 32);
		}
		if((min+max)%2)
		{
			cout<<"NO"<<endl;
			continue;
		}
		else
		{
			bool flag = true;
			middle = min+max;
			cout<<middle<<endl;
			set<long long>::iterator it = s.begin();
			while(it++ != s.end())
			{
				long long t = *it, t1;
				int l;
				
				l = int(t & 0xffffffff);
				if (l == middle)	
					continue;
				cout<<t;
				if (s.count((long long)(middle-l) | (t & 0xffffffff00000000)) < 1)
				{
					flag = false;
					cout<<"NNN "<<l<<" "<<middle-l<<endl;
					break;
				}
			}
			if (flag)
				cout<<"YES"<<endl;
			else
				cout<<"NO"<<endl;
		}
	}
}
