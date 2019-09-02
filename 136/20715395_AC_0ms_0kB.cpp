#include <iostream>
#include <queue>
#include <vector>
#include <set>


using namespace std;

int main()
{
	set<long long> s;
	long long t,t0;
	long long arr[3] = {2,3,5};


	priority_queue<long long, vector<long long>, greater<long long>> que;
	
	que.push((long long)1);
	s.insert((long long)1);
	for(int i = 1; ;i++)
	{
		t = que.top();
		que.pop();
		if (1500 == i)
		{
			cout<<"The 1500'th ugly number is "<<t<<"."<<endl;
			return 0;
		}
		for(int j = 0; j < 3; j++)
		{
			t0 = t*arr[j];
			if (0 == s.count(t0))
			{
				s.insert(t0);
				que.push(t0);
			}
		}
	}
}
