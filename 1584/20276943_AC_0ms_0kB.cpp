#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int main()
{
	int T;
	char seq[101],min;
	bool flag[100];

	int l;
	int i,j,n,c;

	scanf("%d", &T);
	while(T-- >0)
	{
		scanf("%s", seq);
		l = strlen(seq);

		for( i = 0; i < l; i++)
			flag[i] = true;
		n = l;
		
		for(i = 0; (i < l) && (n > 1); i++)
		{
			min = 'T';
			for(j = 0; (j < l) && (min != 'A'); j++)
			{
				if(true == flag[j])
				{
					if (seq[(j+i)%l] < min)
						min = seq[(j+i)%l];
				}
			}
			c=0;
			for(j = 0; j < l; j++)
			{
				if(true == flag[j])
				{
					if (seq[(j+i)%l] > min)
					{
						flag[j] = false;
					}
					else
					{
						c++;
					}
				}
			}
			n = c;
		}
		for(i = 0; i < l; i++)
			if (true == flag[i])
				break;
		for(j = 0; j < l; j++)
			printf("%c", seq[(j+i)%l]);
		printf("\n");
	}
}
