#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int main()
{
	int c;
	
	int N;
	int code[1000];
	int guess[1000];

	int a,b;

	int i,j;
	c = 1;
	while(1)
	{
		scanf("%d", &N);
		if (0 == N)
			break;
		
		for(i = 0; i < N; i++)
			scanf("%d", code+i);

		printf("Game %d:\n", c++);
		while(1)
		{
			for(i = 0; i < N; i++)
				scanf("%d", guess+i);
			if (guess[0] == 0)
				break;

			a = b = 0;
			for(i = 0; i < N; i++)
				if (guess[i] == code[i])
				{
					a++;
					guess[i] = 0;
				}
			for(i = 0; i < N; i++)
				if (guess[i] != 0)
				{
					for(j = 0; j < N; j++)
					{
						if (guess[j] == code[i])
						{
							b++;
							guess[j]=-1;
							break;
						}
					}
				}
			printf("    (%d,%d)\n", a, b);
			
		}
	}

}
