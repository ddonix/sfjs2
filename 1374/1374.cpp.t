#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 1001;
int dd;
int n;

bool se[maxn*2];
bool ida(int d)
{
	if (d == dd)
		return se[maxn+n];
	else
	{
		int ma;
		for(ma = maxn+1000; ma >= maxn+1 && se[ma]; ma--);
		if ((ma-maxn) * (1<<(dd-d)) < n)
			return false;
		
		for(int i = maxn+1000; i >= maxn-1000; i--)
			for(int j = i; j >= maxn-1000; j--)
			{
				if (!se[i] || !se[j] || i == maxn || j == maxn)
					continue;
				
				int t = maxn+(i-maxn)+(j-maxn);
				if (t != maxn && !se[t])
				{
					se[t] = true;
					if (ida(d+1))
						return true;
					se[t] = false;
				}
				t = maxn+(i-maxn)-(j-maxn);
				if (t != maxn && !se[t])
				{
					se[t] = true;
					if (ida(d+1))
						return true;
					se[t] = false;
				}
			}
		return false;
	}
}

int main()
{
	while(cin>>n && n)
	{
		memset(se, 0, sizeof(se));
		se[maxn+1] = true;
		for(dd = 0; dd < n; dd++)
			if (ida(0))
				break;
		cout<<dd<<endl;
	}
}
