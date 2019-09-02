/*  uva 804: 
 *
 *
 *
 */
#include <iostream>
#include <cstring>
#include <vector>
#include <set>

using namespace std;

const int maxn = 100;
int np, nt, nf;

int place[maxn];	//place包含的token数量
int G[maxn][maxn];

struct E
{
	int p;		//place id
	int w;		//weight
	E(int p_, int w_) : p(p_), w(w_){}
};

struct Trans
{
	bool en;
	vector<E> ioe[2];	//0: input, 1:output
	Trans() {}
	void update()
	{
		for(int i = 0; i < ioe[0].size(); i++)
			if (place[ioe[0][i].p] < ioe[0][i].w)
			{
				en = false;
				return;
			}
		en = true;
	}
	void ope()
	{
		if (!en)
			return;
		for(int i = 0; i < ioe[0].size(); i++)
			place[ioe[0][i].p] -= ioe[0][i].w;
		for(int i = 0; i < ioe[1].size(); i++)
			place[ioe[1][i].p] += ioe[1][i].w;
	}

};

Trans trans[maxn];	//trans是否enable

int getET()
{
	for(int i = 0; i < nt; i++)
		if (trans[i].en)
			return i;
	return -1;
}

void update(int t)
{
	bool vis[maxn];
	for(int i = 0;i < nt; i++)
		vis[i] = false;
	for(int d = 0; d < 2; d++)
		for(int i = 0; i < trans[t].ioe[d].size(); i++)
		{
			int p = trans[t].ioe[d][i].p;
			for(int j = 0; j < nt; j++)
				if (G[j][p] && !vis[j])
				{
					trans[j].update();
					vis[j] = true;
				}
		}
}

int main()
{
	int ka = 0, p, i;
	while(cin>>np && np)
	{
		for(i = 0; i < np; i++)
			cin>>place[i];
		cin>>nt;
		for(i = 0; i < nt; i++)
		{
			while(cin>>p && p)
			{
				int d,j;
				d = (p < 0) ? 0 : 1;
				p = (p < 0) ? (-p-1) : (p-1);
				G[i][p] = 1;
				for(j = 0; j < trans[i].ioe[d].size(); j++)
				{
					if(trans[i].ioe[d][j].p == p)
					{
						trans[i].ioe[d][j].w++;
						break;
					}
				}
				if (j == trans[i].ioe[d].size())
					trans[i].ioe[d].push_back(E(p, 1));
			}
		}
		for(i = 0; i < nt; i++)
			trans[i].update();
		cin>>nf;
		for(i = 0; i < nf; i++)
		{
			int et = getET();
			if (et < 0)
			{
				cout<<"Case "<<++ka<<": dead after "<<i<<" transitions"<<endl;
				break;
			}
			else
			{
				trans[et].ope();
				update(et);
			}
		}
		if (i == nf)
			cout<<"Case "<<++ka<<": still live after "<<nf<<" transitions"<<endl;
		cout<<"Places with tokens:";
		for(i = 0; i < np; i++)
			if (place[i] > 0)
				cout<<" "<<i+1<<" "<<"("<<place[i]<<")";
		cout<<endl<<endl;
		for(i = 0; i < nt; i++)
		{
			trans[i].ioe[0].clear();
			trans[i].ioe[1].clear();
		}
	}
}
