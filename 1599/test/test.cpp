#include <iostream>
#include <random>

using namespace std;

int main()
{
	int T = 1;
	while(T--)
	{
		int n = 100000;
		int m = 200000-2;
		cout<<n<<" "<<m<<endl;
		for(int i = 1; i < n; i++)
		{
			int a, b, c;
			c = rand()%100000;
			cout<<i<<" "<<i+1<<" "<<c<<endl;
			c = rand()%100000;
			cout<<i<<" "<<i+1<<" "<<c<<endl;
		}
	}
}
