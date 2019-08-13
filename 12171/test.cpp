#include <iostream>
#include <random>

using namespace std;

int main()
{
	cout<<1000<<endl;
	for(int i = 0; i<1000; i++)
	{
		int n = 3;
		cout<<n<<endl;
		for(int j = 0; j < n; j++)
		{
			for(int k = 0; k < 5; k++)
				cout<<rand()%5+1<<" ";
			cout<<rand()%5+1<<endl;
		}
	}
}
