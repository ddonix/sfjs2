#include <iostream> 
#include <cstdio> 
#include <cstdlib> 
#include <cmath>
#include <cstring>

int main()
{
	double M[10][31];
	long long E[10][31];

	char MM[10][31][100];
	char EE[10][31][100];
	char temp[200];

	double t,m;
	long long e;
	int i,j;
	for(i=0; i <= 9; i++)
		for(j=1; j <= 30; j++)
		{
			m = 1-pow(2,-1-i);
			e = pow(2, j)-1;

			t = log10(m)+e*log10(2);
			E[i][j] = t;
			M[i][j] = pow(10, t-E[i][j]);
		}
	double a;
	long long b;
	while(1)
	{
		scanf("%s", temp);
		*strchr(temp, 'e') = ' ';
		sscanf(temp, "%lf %d", &a, &b);
		if (a == 0 && b==0)
			break;
        	while(a < 1) 
		{
			a *= 10;
			b -= 1;
		}
		int ii,jj;
		double c=100;
		for(i = 0; i <= 9; i++)
			for(j = 1; j <= 30; j++)
			{
				if (b == E[i][j])
				{
					if (fabs(a-M[i][j]) < c)
					{
						ii = i;
						jj = j;
						c = fabs(a-M[i][j]);
					}
				}
			}
		printf("%d %d\n", ii, jj);
	}
}
