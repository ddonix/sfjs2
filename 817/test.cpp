#include <iostream>
#include <random>

using namespace std;

int main()
{
	int a, b, t;
	t = 100;
	for(int i = 0; i < t; i++)
	{
		a = rand()%9+1;
		for(int i = 0; i < a; i++)
			cout<<rand()%10;
		cout<<"="<<endl;
	}
	cout<<"="<<endl;
}
