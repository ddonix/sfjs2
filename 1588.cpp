#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>


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
	return n;
}

int left(unsigned long long g[])
{
	g[0] = g[0] << 1;
	if (g[1] & 1)

}


int main()
{
	int r,c,ca;
	int ml,dl;
	char buff0[101], buff1[101];
	unsigned long long mg[2], dg[2];

	while(scanf("%s %s", buff0, buff1) != EOF)
	{
		ml = set(mg, buff0);
		dl = set(dg, buff1);
		printf("%x\n%x\n", mg[0], dg[0]);
	}
	return 0;
}
