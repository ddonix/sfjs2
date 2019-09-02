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
	int l[4][2];
	int temp[maxn];
	if (d == 0)
	{
		l[0][0] = b;
		l[0][1] = e;
		l[1][0] = 1;
		l[1][1] = b-1;
		l[2][0] = e+1;
		l[2][1] = n;
	}
	else if (d == n)
	{
		l[0][0] = 1;
		l[0][1] = b-1;
		l[1][0] = e+1;
		l[1][1] = n;
		l[2][0] = b;
		l[2][1] = e;
	}
	else
	{
		if (d < b)
		{
			l[0][0] = 1;
			l[0][1] = d;
			l[1][0] = b;
			l[1][1] = e;
			l[2][0] = d+1;
			l[2][1] = b-1;
			l[3][0] = e+1;
			l[3][1] = n;
		}
		else
		{
			l[0][0] = 1;
			l[0][1] = b-1;
			l[1][0] = e+1;
			l[1][1] = d;
			l[2][0] = b;
			l[2][1] = e;
			l[3][0] = d+1;
			l[3][1] = n;
		}
	}
	int k = 1;
	for(int i = 0; i < 4 && k <= n; i++)
	{
		for(int j = l[i][0]; j <= l[i][1] && k <= n; j++)
		{
			temp[k] = p[j];
			k++;
		}
	}
	for(int i = 1; i <= n; i++)
		p[i] = temp[i];
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
					for(int l = 1; l <= n; l++)
						p[l] = back[l];
				}
			}
	}
	return false;
}

int main()
{
	int i, ka=0, b=1;
	while(cin>>n && n)
	{
		p[0] = 0;
		for(i = 1; i <=n; i++)
			cin>>p[i];
		for(i = 0; i <= n; i++)
		{
			dd = i;
			if (ida(0))
				break;
		}
		cout<<"Case "<<++ka<<": "<<i<<endl;
	}
}
