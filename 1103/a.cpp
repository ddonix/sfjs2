#include <iostream>
#include <cstdio>

using namespace std;

void pc(char c)
{
	char a = 0x80;
	printf("%c: %d: ", c, c);
	for(int j = 0; j < 8; j++)
	{
		if (c & a)
			printf("%c", '1');
		else
			printf("%c", '0');
		a = a>>1;
	}
	printf("\n");
}
int main()
{
	for(char i = '0';i <= '9'; i++)
		pc(i);
	
	for(char i = 'a';i <= 'f'; i++)
		pc(i);
}
