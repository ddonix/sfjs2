#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 10000;

int main()
{
	int N, Q, x, a[maxn], kase = 1;

	while (scanf("%d %d", &N, &Q) != EOF)
	{
		if (0 == N or 0 == Q)
			break;
		for(int i = 0; i < N; i++)
			scanf("%d", a+i);
		sort(a, a+N, less<int>());
		printf("CASE# %d:\n", kase++);
		for(int i = 0; i < Q; i++)
		{
			scanf("%d", &x);
			int p = lower_bound(a, a+N, x)-a;
			if (N == p or a[p] != x)
				printf("%d not found\n", x);
			else
				printf("%d found at %d\n", x, p+1);

		}

	}
	
}
