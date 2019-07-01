#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

int main(int argc, char **argv)
{
	unsigned int n;
	double pi = acos(-1);
	scanf("%u", &n);
	printf("%f\n", sin((double)n/180*pi));
	printf("%f\n", cos((double)n/180*pi));
	return 0;
}
