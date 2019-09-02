#include <iostream>
#include <cstdio>
#include <cstdlib>

int main()
{
	int a,b,a0; //a/b

	int zs;

	char xs1[10001];
	char xs2[10001];

	int lt[3001];

	int l,i,j, begin, end;


	while(scanf("%d %d", &a, &b) != EOF)
	{
		for(i = 0; i < 10001; i++)
			xs1[i] = xs2[i] = 0;
		for(i = 0; i < 3001; i++)
			lt[i] = -1;
		
		begin = end = -1;
		
		zs = a/b;
		a0 = a%b;
		for(i = 0; i < 10001; i++)
		{
			if (a0 == 0)
				break;
			if (lt[a0] != -1)
			{
				begin = lt[a0];
				end = i-1;
				break;
			}
			lt[a0] = i;
			
			a0 *= 10;
			if (a0 < b)
			{
				xs1[i] = '0';
			}
			else
			{
				xs1[i] = a0/b+'0';
				a0 = a0%b;
			}
		}
		if (a0 == 0)
		{
			xs2[0] = '0';
			l = 1;
		}
		else
		{
			if (end >= 50)
			{
				for(i = begin; i < 50; i++)
					xs2[i-begin] = xs1[i];
				xs2[i-begin] = '.';
				xs2[i-begin+1] = '.';
				xs2[i-begin+2] = '.';
			}
			else
			{
				for(i = begin; i <= end; i++)
					xs2[i-begin] = xs1[i];

			}
			
			xs1[begin] = 0;
			l = end-begin+1;
		}
		printf("%d/%d = %d.%s(%s)\n", a, b, zs, xs1, xs2);
		printf("   %d = number of digits in repeating cycle\n\n", l);
	}
	return 0;
}
