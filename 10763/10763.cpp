#include <iostream>
#include <set>
using namespace std;

int main()
{
	int n;
	while(cin>>n && n)
	{
		int a,b;
		set<long long> s;
		long long t;
		
		if (n%2)
		{
			cout<<"NO"<<endl;
			for(int i = 0; i < n; i++) cin>>a>>b;
			continue;
		}
		for(int i = 0; i < n; i++)
		{
			cin>>a>>b;
			t = (long long)b << 32 | (long long)a;
			if (s.count(t))
			{
				s.erase(t);
			}
			else
			{
				t = (long long)a << 32 | (long long)b;
				s.insert(t);
			}
		}
		if (s.size())
			cout<<"NO"<<endl;
		else
			cout<<"YES"<<endl;
	}
	return 0;
}
