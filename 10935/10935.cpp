#include <iostream>
#include <queue>

using namespace std;

int main()
{
	int n;
	queue<int> que;
	while(cin>>n && n != 0)
	{
		int a,b;
		for(int i = 1; i <= n; i++)
		{
			que.push(i);
		}
		cout<<"Discarded cards:";
		for(int i = 0; i < n-1; i++)
		{
			a = que.front();
			que.pop();
			b = que.front();
			que.pop();
			que.push(b);
			cout<<" "<<a;
			if (i < n-2)
				cout<<",";
			else
				cout<<endl;
		}
		if (1 == n)
			cout<<endl;
		cout<<"Remaining card: "<<que.front()<<endl;
		que.pop();
	}
}
