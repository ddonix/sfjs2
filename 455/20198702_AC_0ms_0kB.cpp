#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int main(int argc, char **argv)
{
	char buff[81];
	char p[81];
	int n,r,l;
	int i,j;

	scanf("%d", &n);
	scanf("\n");
	for (i = 0; i < n; i++)
	{
		scanf("%s", buff);
		scanf("\n");
		l = strlen(buff);

		for(r=1; r <= 80; r++)
		{
			p[r-1]=buff[r-1];
			p[r] = 0;
			for(j = r; j < l; j += r)
			{
				if(0 != strncmp(buff + j, p, r))
					break;
			}
			if (j >= l)
				break;
		}
		printf("%d\n", r);
		if(i < n-1)
			printf("\n");
	}
}
