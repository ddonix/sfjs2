#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

int main(int argc, char **argv)
{
	int n;
	scanf("%d", &n);
	printf("%.2f", n > 3 ? (double)95*n*0.85 : 95*n);
	return 0;
}
