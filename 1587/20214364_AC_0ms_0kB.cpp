#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

int main()
{
	int wh[12];
	int a,b,c,i;
	int a0,b0,c0;
	while(scanf("%d", &wh[0]) != EOF)
	{
		for(i = 1; i < 12; i++)
			scanf("%d", &wh[i]);
		a = wh[0];
		b = wh[1];
		if ((a == wh[2] && b == wh[3]) || (a == wh[3] && b == wh[2]))
		{
			if (wh[4] == a || wh[4] == b)
				c = wh[5];
			else if (wh[5] == a || wh[5] == b)
				c = wh[4];
			else if (wh[4] == wh[5])
				c = wh[4];
			else
				c = 0;
		}
		else
		{
			if (wh[2] == a || wh[2] == b)
				c = wh[3];
			else if (wh[3] == a || wh[3] == b)
				c = wh[2];
			else if (wh[2] == wh[3])
				c = wh[2];
			else
				c = 0;
		}
		if (c == 0)
		{
			printf("IMPOSSIBLE\n"); 
			continue;
		}

		a0 = b0 = 0;
		c0 = 1;
		for(i = 2; i < 12; i += 2)
		{
			if (((wh[i] == a && wh[i+1] == b) || (wh[i] == b && wh[i+1] == a)) && c0 < 2)
			{
				wh[i] = 0;
				wh[i+1] = 0;
				c0++;
				continue;
			}
			if (((wh[i] == a && wh[i+1] == c) || (wh[i] == c && wh[i+1] == a)) && b0 < 2)
			{
				wh[i] = 0;
				wh[i+1] = 0;
				b0++;
				continue;
			}
			if (((wh[i] == b && wh[i+1] == c) || (wh[i] == c && wh[i+1] == b)) && a0 < 2)
			{
				wh[i] = 0;
				wh[i+1] = 0;
				a0++;
				continue;
			}
		}
		if (a0 == 2 && b0 == 2 && c0 ==2)
			printf("POSSIBLE\n"); 
		else
			printf("IMPOSSIBLE\n"); 
	}
}
