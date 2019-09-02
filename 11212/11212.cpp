#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int maxn = 10;
int n;

int p[maxn];
int dd;

bool isok(int *p)
{
	for(int i = 1; i < n; i++)
		if (p[i+1] != p[i] +1)
			return false;
	return true;
}

int getneed(int *p)
{
	int ne = 0;
	for(int i = 1; i < n; i++)
	{
		if (p[i+1] != p[i] +1)
			ne++;
	}
	return ne;
}

void cut(int b, int e, int d)
{
	int l[3][2];
	int temp[maxn];
	for(int i = b; i <= e; i++)
		temp[i] = p[i];
	int k = b;
	for(int i = e+1; i <= d; i++)
		p[k++] = p[i];
	for(int i = b; i <= e; i++)
		p[k++] = temp[i];
	for(int i = d+1; i <= n; i++)
		p[k++] = p[i];
}

bool ida(int d)
{
	if (d == dd)
		return isok(p);
	else
	{
		if (getneed(p) > 3*(dd-d))
			return false;
		int back[maxn];
		for(int i = 1; i <= n; i++)
			back[i] = p[i];
		for(int i = 1; i <= n; i++)
			for(int j = i; j <=n; j++)
			{
				for(int k = j+1; k <= n; k++)
				{
					if (k >= (i-1) && k <= j)
						continue;
					cut(i, j, k);
					if (ida(d+1))
						return true;
					for(int l = i; l <= n; l++)
						p[l] = back[l];
				}
			}
	}
	return false;
}

int main()
{
	int ka=0;
	while(cin>>n && n)
	{
		p[0] = 0;
		for(int i = 1; i <=n; i++)
			cin>>p[i];
		for(dd = 0; dd <= n; dd++)
			if (ida(0))
				break;
		cout<<"Case "<<++ka<<": "<<dd<<endl;
	}
}
