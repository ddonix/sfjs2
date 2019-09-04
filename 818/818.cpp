#include <iostream>
using namespace std;

const int maxn = 15;
int n, ans;

unsigned short bits[15] = {	0x1, 	0x2, 	0x4, 	0x8,
				0x10,	0x20,	0x40,	0x80,
				0x100,	0x200,	0x400,	0x800,
				0x1000,	0x2000,	0x8000};
unsigned short g[maxn];

int main()
{
	int ka = 0;
	while(cin>>n && n)
	{
		int rep = 0;
		for(int i = 0; i < n; i++)
			g[i] = 0;
		int a,b;
		while(cin>>a>>b && -1 != a)
		{
			if ((g[a-1] & bits[b-1]) || (g[b-1] & bits[a-1]))
				rep++;
			else
			{
				g[a-1] |= bits[b-1];
				g[b-1] |= bits[a-1];
			}
		}
		cout<<"Set "<<++ka<<":Minimum links to open is "<<ans+rep<<endl;
	}
}
