#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

int main(int argc, char **argv)
{
	unsigned long a, b, c;
	unsigned long temp;
	scanf("%u %u %u", &a, &b, &c);
	if (a < b)
	{
		if (b > c)
		{
			temp = b;
			b = c;
			c = temp;
		}
	}
	else
	{
		if (a > c)
		{
			if (b > c)
			{
				temp = a;
				a = c;
				c = temp;
			}
		}
		else if(c < a)
		{
			temp = c;
			c = a;
			a = b;
			b = temp;
		}
		else
		{
			temp = c;
			c = a;
			a = temp;
		}
	}
	printf("%d %d %d", a, b, c);
	return 0;
}
