#include <iostream>
#include <queue>

using namespace std;
int main()
{
	int a[3];
	a[0] = 100;
	queue<int *> q;
	q.push(a);
	a[0] = 120;
	cout<<(q.front())[0]<<endl;
}
