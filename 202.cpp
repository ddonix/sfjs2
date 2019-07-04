#include <iostream>
#include <cstdio>
#include <cstdlib>

int main()
{
	int a,b,a0; //a/b
	bool first = true;

	int zs;
	int xs1[10001];
	int xs2[10001];
	int l;

	while(scanf("%d %d", &a, &b) != EOF)
	{
		if (true == first)
			first = false;
		else
			printf("\n");
		
		zs = a/b;

		a0 = a%b;
		if (a0 == 0)
		{
			zs = a/b;
			xs1[0] = 0;
			
			xs2[0] = '0';
			xs2[1] = 0;
			l = 1;
		}
		
		

		printf("%d/%d = %d.%s(%s)\n", a, b, zs, xs1, xs2);
		printf("%3d = number of digits in repeating cycle\n", l);
	}
	return 0;
}
