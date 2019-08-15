#include <iostream>
#include <random>

using namespace std;

int main()
{
	int T = 1;
	while(T--)
	{
		int n = 10000+rand()%10000;
		int m = 100000+rand()%100000;
		for(int i = 0; i < m; i++)
		{
			int a, b, c;
			a = 1+rand()%n;
			b = 1+rand()%n;
			c = rand()%1000000;
			cout<<a<<" "<<b<<" "<<c<<endl;
		}
	}
}
