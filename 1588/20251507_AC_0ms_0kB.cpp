#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>


int ml,dl;
unsigned long long mg[2], dg[2],dg_backup[2];

int set(unsigned long long g[], const char *buff)
{
	int i,n,l;
	unsigned long long t;
	
	l = strlen(buff);
	
	g[0] = g[1] = 0;
	n = (l <= 64) ? l : 64;
	
	t = 1;
	for(i = 0; i < n; i++)
	{
		if(buff[i] == '2')
			g[0] |= t;
		t = t<<1;
	}
	if (l > 64)
	{
		t = 1;
		for(i = 64; i < l; i++)
		{
			if(buff[i] == '2')
				g[1] |= t;
			t = t<<1;
		}
	}
	return l;
}

void move_right(unsigned long long g[])
{
	g[1] = g[1] << 1;
	if (g[0] & 0x8000000000000000)
		g[1] |= 0x1;
	g[0] = g[0] << 1;
}

void move_left(unsigned long long g[])
{
	g[0] = g[0] >> 1;
	if (g[1] & 0x1)
		g[0] |= 0x8000000000000000;
	g[1] = g[1] >> 1;
}


int main()
{
	int r,c,ca;
	int i,j,k;
	char buff0[101], buff1[101];

	char format[130];
	while(scanf("%s %s", buff0, buff1) != EOF)
	{
		if (strlen(buff0) > strlen(buff1))
		{
			ml = set(mg, buff0);
			dl = set(dg, buff1);
		}
		else
		{
			ml = set(mg, buff1);
			dl = set(dg, buff0);
		}
		dg_backup[0] = dg[0];
		dg_backup[1] = dg[1];

		for(i = 0; (mg[0] & dg[0]) || (mg[1] & dg[1]);i++)
			move_right(dg);
		
		if (i <= (ml-dl))
		{
			printf("%d\n", ml);
		}
		else
		{
			for (j = 1; j <= dl; j++)
			{
				move_left(dg_backup);
				if ((0 == (mg[0] & dg_backup[0])) && (0 == (mg[1] & dg_backup[1])))
					break;
			}
			if((ml+j) < (dl+i))
				printf("%d\n", ml+j);
			else
				printf("%d\n", dl+i);
		}
	}
	return 0;
}
