#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int digitsum(int a)
{
	int m[6] = {100000, 10000, 1000, 100, 10, 1};
	int r = a;
	for(int i = 0; a; i++)
	{
		r += a/m[i];
		a = a%m[i];
	}
	return r;
}


int main()
{
	int T;
	int n;
	int i,j;
	int m[100045];
	int ff;
	memset(m, 0, sizeof(m));

	for(int i = 1; i < 100000; i++)
	{
		j = digitsum(i);
		if (i == 99937)
		{
			ff = 0;
		}
		if (0 == m[j])
		{
			m[j] = i;
		}
	}
	scanf("%d", &T);
	for(i=0; i < T; i++)
	{
		scanf("%d", &n);
		printf("%d\n", m[n]);
	}
}

