#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

int main()
{
	char s0[1000000], s1[1000000];
	int i,j;
	while(scanf("%s", s0) != EOF)
	{
		scanf("%s", s1);
	
		j = 0;
		for(i = 0; s0[i] != 0; i++) 
		{
			while(s1[j] != s0[i] && s1[j] != 0)
			{
				j++;
			}
			if (s1[j] == 0)	
			{
				break;
			}
			else
				j++;
		}
		if (s0[i] == 0)
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}
