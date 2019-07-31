#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>



int main(int argc, char **argv)
{
	int t;
	int ca, i,j,k;

	int m,n;
	char dna[50][1001];

	char rdna[1001];
	int num[4];
	int min;

	scanf("%d", &t);
	for(ca = 0; ca < t; ca++)
	{
		scanf("%d %d", &m, &n);
		for(i = 0; i < m; i++)
			scanf("%s", dna[i]);
		
		min = 0;
		for(j =0; j < n; j++)
		{
			num[0] = num[1] = num[2] = num[3] = 0;
			for(i = 0; i < m; i++)	
			{
				switch(dna[i][j])
				{
					case 'A':
						num[0]++;
					break;
					
					case 'C':
						num[1]++;
					break;
					
					case 'G':
						num[2]++;
					break;
					
					default:
						num[3]++;
					break;
				}
			}
			if (num[0] >= num[1] && num[0] >= num[2] && num[0] >= num[3])
			{
				rdna[j] = 'A';
				min += m-num[0];
			}
			else if (num[1] >= num[0] && num[1] >= num[2] && num[1] >= num[3])
			{
				rdna[j] = 'C';
				min += m-num[1];
			}
			else if (num[2] >= num[0] && num[2] >= num[1] && num[2] >= num[3])
			{
				rdna[j] = 'G';
				min += m-num[2];
			}
			else
			{
				rdna[j] = 'T';
				min += m-num[3];
			}
		}
		rdna[n] = 0;
		printf("%s\n", rdna);
		printf("%d\n", min);
	}
}
