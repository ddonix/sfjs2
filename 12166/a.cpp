#include <iostream>
#include <map>

using namespace std;
int main()
{
	map<int,int> a;
	cout<<a.count(0)<<endl;
	a[0]++;
	cout<<a[0]<<endl;
}
