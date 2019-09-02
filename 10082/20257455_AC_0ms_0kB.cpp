#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

int main()
{
	const char *map[5] = {"‘QAZ ", "‘1234567890-=", "QWERTYUIOP[]\\", "ASDFGHJKL;'","ZXCVBNM,./"};
	
	char buff[10000];
	char *t;
	int i,j;

	while(cin.getline(buff, 10000))
	{	
		i = 0;
		while(buff[i])
		{
			t = strchr((char *)map[0], buff[i]);
			if (t)
				printf("%c", buff[i]);
			else
			{
				for(j = 1; j < 5; j++)
				{
					t = strchr((char *)map[j], buff[i]);
					if (t)
					{
						printf("%c", t[-1]);
					}
				}
			}
			i++;
		}
		printf("\n");
	}
}
