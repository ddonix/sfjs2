#include <iostream>
#include <cstdio>
#include <cstdlib>

int main()
{
	int r,c, ca;
	char puzzle[10][12];
	int i,j,k;
	int p[10][10];
	int qs;
	ca = 1;
	while(1)
	{
		scanf("%d", &r);
		if(0 == r)
			return 0;
		scanf("%d", &c);
		for(i = 0; i < r; i++)
			scanf("%s", puzzle[i]);
	
		qs = 1;
		for(i = 0; i < r; i++)
		{
			for(j = 0; j < c; j++)
			{
				p[i][j] = 0;
				if (puzzle[i][j] == '*')
				{
					p[i][j] = -1;
					continue;
				}
					
				if(i == 0 || j == 0)
				{
					p[i][j] = qs++;	
				}
				else
				{
					if (puzzle[i-1][j] == '*')
						p[i][j] = qs++;
					else if (puzzle[i][j-1] == '*')
						p[i][j] = qs++;
				}
			}
		}



		if(ca != 1)
			printf("\n");
		printf("puzzle #%d:\n", ca++);
		printf("Across\n");
		for(i = 0; i < r; i++)
			for(j = 0; j < c; )
			{
				if(p[i][j] > 0)
				{
					printf("%3d.", p[i][j]);
					while(j < c && p[i][j] >= 0)
					{
						printf("%c", puzzle[i][j]);
						j++;
					}
					printf("\n");
				}
				j++;
			}
		printf("Down\n");
		for(i = 0; i < r; i++)
			for(j = 0; j < c; j++)
			{
				if(p[i][j] > 0)
				{
					printf("%3d.", p[i][j]);
					for(k = i; k < r; k++)
					{
						if (p[k][j] >= 0)
						{
							printf("%c", puzzle[k][j]);
							p[k][j] = -1;
						}
						else
							break;
					}
					printf("\n");
				}
			}
	}
	return 0;
}
