#include <iostream>
#include <random>

using namespace std;

int main()
{
	for(int i = 0; i<100000; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if (i%5 == 0)
			{
				if (j%2)
					cout<<(rand()%5 ? ' ' : '_');
				else
					cout<<' ';
			}
			else
			{
				if (j%2)
					cout<<(rand()%5 ? ' ' : '_');
				else
					cout<<(rand()%5 ? ' ' : '|');
			}
		}
		cout<<"#"<<endl;
	}
	cout<<0<<endl;
}
