#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>


char map[256];

int main()
{
	char buff[100000], c;
	int l,i,n;
	bool rp, ms;
	memset(map, 0, 256);
	map['A'] = 'A';
	map['E'] = '3';
	map['H'] = 'H';
	map['I'] = 'I';
	map['J'] = 'L';
	map['L'] = 'J';
	map['M'] = 'M';
	map['O'] = 'O';
	map['S'] = '2';
	map['T'] = 'T';
	map['U'] = 'U';
	map['V'] = 'V';
	map['W'] = 'W';
	map['X'] = 'X';
	map['Y'] = 'Y';
	map['Z'] = '5';
	map['1'] = '1';
	map['2'] = 'S';
	map['3'] = 'E';
	map['5'] = 'Z';
	map['8'] = '8';
	const char *output[4] = {" -- is a mirrored palindrome.", " -- is a regular palindrome.",
				" -- is a mirrored string.", " -- is not a palindrome."};
	
	while(scanf("%s", buff) != EOF)
	{
		l = strlen(buff);
		rp = ms = true;
		if(l%2)
		{
			c = buff[l/2];
			if (map[c] != c)
				ms = false;
		}
		n = l/2;
		for(i = 0; i < n; i++)
		{
			c = buff[i];
			

			if (c != buff[l-i-1])
				rp = false;
			if (map[c] != buff[l-i-1])
				ms = false;

			if(!(rp || ms))
				break;
		}
		if(rp && ms)
			printf("%s%s\n\n", buff, output[0]);
		else if (rp)
			printf("%s%s\n\n", buff, output[1]);
		else if (ms)
			printf("%s%s\n\n", buff, output[2]);
		else
			printf("%s%s\n\n", buff, output[3]);

	}
	return 0;
}
