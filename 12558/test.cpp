#include <iostream>
#include <random>

using namespace std;

int main()
{
	int a, b, t;
	t = 10000;
	cout<<t<<endl;
	for(int i = 0; i < t; i++)
	{
		a = rand()%1000+1;
		b = a+rand()%1000+1;
		cout<<a<<" "<<b<<" "<<0<<endl;
	}
}
