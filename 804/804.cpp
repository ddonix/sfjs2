#include <iostream>
#include <cstring>

using namespace std;

const int maxn = 100;
int np, nt, nf;

int G[maxn][maxn];	//G[t][p] > 0: p是input的数量
					//G[t][p] < 0: p是output的数量
bool trans[maxn];	//trans是否enable
int place[maxn];	//place包含的token数量



bool isEnable(int t)
{
	for(int i = 0; i < np; i++)
		if (token[i] < G[t][i])
			return false;
	return true;
}

bool isActive()
{
	for(int i = 0; i < nt; i++)
		if (isEnable(i))
			return true;
	return false;
}

void :
void build()
{
	for(int i = 0; i < nt; i++)
		trans[i] = isEnable(i);
}

int main()
{
	int ka = 0, p;
	while(cin>>np && np)
	{
		for(int i = 0; i < np; i++)
			cin>>place[i];
		cin>>nt;
		memset(G, 0, sizeof(G));
		for(int i = 0; i < nt; i++)
		{
			while(cin>>p && p)
			{
				if (p < 0)
					G[i][-p-1]++;
				else
					G[i][p-1]--;
			}
		}
		cin>>nf;
		cout<<"Case "<<++ka<<": still live after "<<nf<<endl;
		cout<<"transitionsPlaces with tokens: 1 (1)"<<endl<<endl;
	}
}
