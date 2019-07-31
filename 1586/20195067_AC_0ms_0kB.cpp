#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int main(int argc, char **argv)
{
	int t,i,j,temp, l;
	char c, buff[84];
	int map[256];

	int a;
	int n[4];
	double saw[4];
	
	map['C'] = 10;
	map['H'] = 11;
	map['O'] = 12;
	map['N'] = 13;
	map[0] = 14;
	
	for(c='0';c <= '9';c++)
		map[c]=c-'0';
	
	saw[0]=12.01;
	saw[1]=1.008;
	saw[2]=16.00;
	saw[3]=14.01;

	scanf("%d", &t);
	for(i = 0; i < t; i++)
	{
		memset(buff, 0, 84);
		scanf("%s", buff);

		n[0]=n[1]=n[2]=n[3]=0;
		for(j = 0; buff[j] != 0; )
		{
			a = map[buff[j]]-10;
			if(map[buff[j+1]] >= 10)
			{
				n[a]++;
				j++;
			}
			else
			{
				if(map[buff[j+2]] >= 10)
				{
					n[a] += map[buff[j+1]];
					j += 2;
				}
				else
				{
					n[a] += 10*map[buff[j+1]] + map[buff[j+2]];
					j += 3;
				}
			}
		}
		printf("%.3f\n", saw[0]*n[0]+saw[1]*n[1]+saw[2]*n[2]+saw[3]*n[3]);
	}
}
