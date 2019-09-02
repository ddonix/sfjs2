#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main()
{
	bool flag = false;
	char buff[10000];
	char c;
	int i;
	while(cin.getline(buff, 10000))
	{	
		i = 0;
		while(buff[i])
		{
			if(buff[i] == '\"')
			{
				if (flag == true)
					printf("%s", "''");
				else
					printf("%s", "``");
				flag = !flag;
			}
			else
				printf("%c", buff[i]);
			i++;
		}
		printf("\n");
	}
}
