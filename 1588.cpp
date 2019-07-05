#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>


int ml,dl;
unsigned long long mg[2], dg[2],dg_backup[2];

void print(unsigned long long g[])
{
	int i,l,n;
	unsigned long long t;
	l = (g == mg) ? ml : dl;
	n = (l <= 64) ? l : 64;
	t = 0x1;
	for (i = 0; i < n; i++)
	{
		if (g[0] & t)
			printf("%c", '1');
		else
			printf("%c", '0');
		t = t << 1;
	}
	t = 0x1;
	for(i = 64; i < l - 64; i++)
	{
		if (g[1] & t)
			printf("%c", '1');
		else
			printf("%c", '0');
		t = t << 1;
	
	}
	printf("\n");

}

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

void move_right()
{
	dg[1] = dg[1] << 1;
	if (dg[0] & 0x8000000000000000)
		dg[1] |= 0x1;
	dg[0] = dg[0] << 1;
}

void move_left()
{
	dg[0] = dg[0] >> 1;
	if (dg[1] & 0x1)
		dg[0] |= 0x8000000000000000;
	dg[1] = dg[1] >> 1;
}


int main()
{
	int r,c,ca;
	int i,j,k;
	char buff0[101], buff1[101];

	char format[130];
	while(scanf("%s %s", buff0, buff1) != EOF)
	{
		ml = set(mg, buff0);
		dl = set(dg, buff1);
		dg_backup[0] = dg[0];
		dg_backup[1] = dg[1];

		for(i = 0; i < ml; i++)
		{
			if ((0 == (mg[0] & dg[0])) && (0 == (mg[1] & dg[1])))
				break;
			move_right();
		}
		if (i < (ml-dl))
		{
			r = ml;
			printf("%d\n", r);
		}
		else
		{
			r = i+dl;
			for (j = 0; j < ml; j++)
			{
				if ((0 == (mg[0] & dg[0])) && (0 == (mg[1] & dg[1])))
					break;
				move_left();
			}
			if (j < (i-(ml-dl)))
				printf("%d\n", ml+j);
			else
		}
	}
	return 0;
}
