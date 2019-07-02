#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int main(int argc, char **argv)
{
	char buff[5];
	int i,j,k,n,m;
	int res[10];
	scanf("%d", &n);
	for(i = 0; i < n; i++)
	{
		scanf("%d", &m);
		for(j = 0; j < 10; j++)
			res[j] = 0;
		for(j = 1; j <= m; j++)
		{
			sprintf(buff, "%d", i);
			for(k = 0; buff[k] != 0; k++)
				res[buff[k]-'0']++;
		}
		for(j = 0; j < 9; j++)
			printf("%d ", res[i]);
		printf("%d\n", res[9]);
	}
}
