#include <iostream>

#include <vector>

using namespace std;

int main()
{
	vector<int> a;
	cout<<(a.begin() == a.end())<<endl;
	a.insert(a.end(), 10);
	cout<<a.front()<<endl;
}

