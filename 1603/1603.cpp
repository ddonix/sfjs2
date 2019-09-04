#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <cstring>
using namespace std;

const int maxn = 5;
const int maxm = 2*(maxn+1)*maxn;
const int maxsq = 55;
const int maxss[5] = {1, 5, 14, 30, 55};

unsigned long long bits[maxsq];
unsigned long long square[maxn][maxsq];	//每个正方形对应的火柴编号
unsigned long long mts[maxn][maxm];	//每个火柴对应的正方形编号

int n;
int dd;

int inline axistoi0(int x, int y)
{
	return x*(2*n+1)+y;
}

int inline axistoi1(int x, int y)
{
	return x*(2*n+1)+y+n;
}

void initializeg()
{
	unsigned long long b = 0x1;
	for(int i = 0;i < maxm; i++)
	{
		bits[i] = b;
		b = (b << 1);
	}
	
	memset(square, 0, sizeof(square));
	memset(mts, 0, sizeof(mts));
	for(n = 1; n <= maxn; n++)
	{
		int ns = 0;
		for(int x = 0; x < n; x++)
			for(int y = 0; y < n; y++)
			{
				for(int l = 1; l <= n; l++)
				{
					if (x + l > n || y + l > n)
						break;
					for(int k = 0; k < l; k++)
					{
						int e[4] = {axistoi0(x,y+k), axistoi0(x+l,y+k), axistoi1(x+k,y),axistoi1(x+k,y+l)};
						square[n-1][ns] = bits[e[0]]|bits[e[1]]|bits[e[2]]|bits[e[3]];
						for(int k1 = 0; k1 < 4; k1++)
							mts[n-1][e[k1]] |= bits[ns];
					}
					ns++;
				}
			}
	}
}

//d: 当前移动了次数
//pre: 前一次移动的火柴编号
//sv: 正方形状态
//mv: 火柴状态
bool ida(int d, int pre, unsigned long long sv, unsigned long long mv)
{
	if (d == dd)
		return sv == 0;
	else
	{
		unsigned long long tm = mv;
		int need = 0;
		for(int s = 0; s < maxss[n-1]; s++)
		{
			if((sv & bits[s]) && ((square[n-1][s] & tm) == square[n-1][s]))
			{
				need++;
				tm &= ~square[n-1][s];
			}
		}
		if (need+d > dd)
			return false;
		for(int s = 0; s < maxss[n-1]; s++)
		{
			if (!(sv & bits[s]))
				continue;
			for(int m = pre+1; m < 2*(n+1)*n; m++)
			{
				if ((mv & bits[m]) && (square[n-1][s] & bits[m]))
				{
					unsigned long long nmv = (mv & ~bits[m]);
					unsigned long long nsv = sv;
					for(int k = 0; k < maxss[n-1]; k++)
						if (mts[n-1][m] & bits[k])
							nsv &= ~bits[k];
					if (ida(d+1, m, nsv, nmv))
						return true;
				}
			}
		}
		return false;
	}
}

int main()
{
	int T,t, k;
	initializeg();
	
	cin>>T;
	while(T--)
	{
		unsigned long long mtv = 0;	//火柴状态
		unsigned long long sqv = 0;	//正方形状态
		
		cin>>n>>k;
		mtv = ((unsigned long long)1 << 2*(n+1)*n)-1;
		for(int i = 0; i < k; i++)
		{
			cin>>t;
			mtv &= ~bits[t-1];
		}
		for(int i = 0; i < maxss[n-1]; i++)
			if ((square[n-1][i] & mtv) == square[n-1][i])
				sqv |= bits[i];
		for(dd = 0; dd <= maxss[n-1]; dd++)
		{
			if (!ida(0, -1, sqv, mtv))
				continue;
			cout<<dd<<endl;
			break;
		}
	}
}
