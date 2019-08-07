#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int quantum;
int itime[5];

struct Program
{
	queue<string> statement;
	int state;	//0:
	int time;	//
};
int main()
{
	int np;
	while(cin>>np)
	{
		for(int i = 0; i < 5; i++)
			cin>>itime[i];
		cin>>quantum;
		vector<Program> program;
		vector<int> ready;
		
		program.resize(np);
		
		for(int i = 0; i < np; i++)
		{
			string s;
			do
			{
				cin>>s;
				program[i].statement.push(s);
			}while("end" != s);
			ready
		}
	}
}
