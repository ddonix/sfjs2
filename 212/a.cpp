#include <iostream>
#include <queue>

using namespace std;

int main()
{
	priority_queue<int, vector<int>, less<int> > q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(1);
	q.push(4);
	while(!q.empty())
	{
		int a = q.top();
		cout<<a<<endl;
		q.pop();
	}
}
