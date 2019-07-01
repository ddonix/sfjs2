#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

int main(int argc, char **argv)
{
	int a0,a1,a2;
	double average;

	scanf("%d %d %d", &a0, &a1, &a2);
	printf("%.3lf\n", double(a0+a1+a2)/3.0);

	return 0;
}
