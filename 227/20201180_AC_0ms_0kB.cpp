#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int main(int argc, char **argv)
{
	char puzzle[5][8];
	char ill,temp;
	int x=-1,y=-1;
	int c;
	bool f = true;
	
	c = 1;
	while(1)
	{
		f = true;
		x = -1;
		y = -1;
		for(int i = 0; i < 5; i++)
		{
			gets(puzzle[i]);
			if (puzzle[i][0] == 0)
			{
				i--;
				continue;
			}
			if (0 == i) 
			{ 
				if (puzzle[0][0] == 'Z')
					return 0;
			}
			if (x == -1)
			{
				for(int j = 0; j < 5; j++)
					if (puzzle[i][j] == ' ' || puzzle[i][j] == 0)
					{
						x = i;
						y = j;
						if(puzzle[i][j] == 0)
							puzzle[i][j] = ' ';
						break; }
			}
		}
		while(1)
		{
			scanf("%c", &ill);
			if ('0' == ill)
				break;
			if (f == false)	
				continue;
			switch(ill)
			{
				case 'A':
					if(x == 0)
						f = false;
					else
					{
						puzzle[x][y]=puzzle[x-1][y];
						x--;
					}
					break;

				case 'B':
					if(x == 4)
						f = false;
					else
					{
						puzzle[x][y]=puzzle[x+1][y];
						x++;
					}
					break;
				
				case 'L':
					if(y == 0)
						f = false;
					else
					{
						puzzle[x][y]=puzzle[x][y-1];
						y--;	
					}
					break;

				case 'R':
					if(y == 4)
						f = false;
					else
					{
						puzzle[x][y]=puzzle[x][y+1];
						y++;
					}
					break;

				default:
					break;
			}
			puzzle[x][y] = ' ';
		}
		if(c > 1)
			printf("\n");
		printf("Puzzle #%d:\n", c++);
		if (f == false)
			printf("This puzzle has no final configuration.\n");
		else
		{
			for(int i = 0; i < 5; i++)
			{
				printf("%c %c %c %c %c\n", 
					puzzle[i][0], puzzle[i][1], puzzle[i][2], puzzle[i][3], puzzle[i][4]);
			}
		}
	}
}
