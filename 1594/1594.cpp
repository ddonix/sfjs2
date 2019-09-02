#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main()
{
	int t;
	int n;
	cin>>t;
	while(t--)
	{
		vector<int> v;
		set<vector<int>> s;
		cin>>n;
		v.resize(n);
		for(int i = 0; i < n; i++) cin>>v[i];
		for(int i = 0; i < 1000; i++)
		{
			int v0 = v[0];
			int j;
			for(j = 0; j < n-1; j++)
				v[j] = (v[j+1] > v[j]) ? (v[j+1] - v[j]):(v[j]-v[j+1]);
			v[n-1] = (v[n-1] > v0) ? (v[n-1] - v0) : (v0 - v[n-1]);
			for(j = 0; j < n && 0 == v[j]; j++);
			if (j == n)
			{
				cout<<"ZERO"<<endl;
				break;
			}
			else if(s.count(v) == 1)
			{
				cout<<"LOOP"<<endl;
				break;
			}
			else
				s.insert(v);
		}
	}
}
