/* uva 12107: 题意：改动数字谜语中的某几位，使得谜语有唯一解。要求改动的位数最小。如果有多个改动
 * 		    输出结果谜语字典序最小的那个。
 * 	      分析：本题分为两个问题，第一是判断谜语是否有唯一解。第二是在原谜语基础上进行最少改
 * 	            动成为有唯一解的新谜语。判断是否有唯一解，思路是枚举谜语左边所有*取值，看看
 * 	            与谜语右边匹配的可能有多少。最大计算量为pow(10,4)*4=40000。
 * 	            第二个问题可以枚举所有改动。可选改动的数量：谜语最多8位,可以改动0-8位，每位
 * 	            有10个可改选项，所有改动有：
 * 	      	    C(8,0)*pow(10,0)+C(8,1)*pow(10,1)+C(8,2)*pow(10,2)...+C(8,8)*pow(10,8) 
 * 	      	    =很大的数。每个改动判断是否唯一解，还要进行40000次运算，总的计算量是天文数字
 * 	      思路：1.ida。这是最直接的思路，直觉判断会超时。
 * 	      	    2.先根据当前谜语，得到所有解，然后根据解的形式，反向推导新的唯一解谜语。推导
 * 	      	    方法是固定固定某几位*,看看结果是否为唯一。这道题就变成了集合查找问题。这种思
 * 	      	    路有个问题待解决：如果改动不是固定*,而是把一个数字变成另一个数字，或者变成一
 * 	      	    个*。可能会导致错误答案，因为相当于对转移做了限制。很快就发现反例了！
 * 	      	    8 ** 8*。改为6 ** 8*是答案。失败！
 * 	      	    3.枚举所有的谜语，打表有唯一解谜语，然后看看当前谜语距离有唯一解谜语
 * 	      	    最近的是哪个。 表大小：pow(11,3)+3*pow(11,4)+...+pow(11,8)个谜语。也是一个
 * 	      	    巨大的数.哎！！！
 * 	      	    老老实实ida吧，想想有什么剪枝策略是正路。
 * 	      	    转移顺序：1.从左到右，数字改为*,而后从小到大改为别的数字(不能超过自己).
 * 	      	    	      2.从右到左，数字从小到大改为别的数字(大于自己).*从小到大改为数字.
 */
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

char t[10][10][10][10][4];//乘法表
const unsigned char bits[8] = {	0x1,	0x2,	0x4,	0x8,
				0x10,	0x20,	0x40,	0x80};

struct Puzzle
{
	char pu[8];
	int s;
	int lmin, lmax;
	int rmin, rmax;

	Puzzle newp(int pos, char c) const
	{
		Puzzle np;
		for(int i = 0; i < 8; i++)
			np.pu[i] = pu[i];
		np.pu[pos] = c;
		np.getsolve();
		return np;
	}

	char minb(int i) const
	{
		if (0 == i || 2 == i)
			return '1';
		else if (1 == i || 3 == i)
			return ('0' == pu[i-1]) ? '1' : '0';
		else 
		{
			for(int j = 4; j < 8; j++)
				if (j != i && pu[j] != '0')
					return '1';
			return '0';
		}
	}

	void getsolve()
	{
		int e0[8], e1[8];
		for(int i = 0; i < 8; i++)
		{
			e0[i] = ('*' == pu[i]) ? 0 : pu[i]-'0';
			e1[i] = ('*' == pu[i]) ? 9 : pu[i]-'0';
		}
		lmax = (e1[0]*10+e1[1])*(e1[2]*10+e1[3]);
		rmax = (e1[4]*1000+e1[5]*100+e1[6]*10+e1[7]);
		
		lmin = ((e0[0]||e0[1]) ? (e0[0]*10+e0[1]) : 1) *((e0[2]||e0[3]) ? (e0[2]*10+e0[3]) : 1);
		rmin = (e0[4]*1000+e0[5]*100+e0[6]*10+e0[7]);
		rmin = (rmin ? rmin : 1);
		
		s = 0;
		if (lmin > rmax || lmax < rmin)
			return;
		
		int ab[4][2];
		for(int i = 0; i < 4; i++)
		{
			ab[i][0] = (pu[i] == '*') ? ((i == 0 || i == 2) ? 1: 0) : pu[i]-'0';
			ab[i][1] = (pu[i] == '*') ? 9 : pu[i]-'0';
		}
		for(int a = ab[0][0]; a <= ab[0][1]; a++)
			for(int b = ab[1][0]; b <= ab[1][1]; b++)
				for(int c = ab[2][0]; c <= ab[2][1]; c++)
					for(int d = ab[3][0]; d <= ab[3][1]; d++)
					{
						if((a == 0 && b == 0) || (c == 0 && d == 0))
							continue;
						int j = 0;
						for(;'0' == t[a][b][c][d][j] && '0' == pu[4+j]; j++);
						if('0'==t[a][b][c][d][j] || '0'==pu[4+j])
							break;
						for(; j < 4; j++)
						{
							if (!(t[a][b][c][d][j] == pu[4+j]
									|| '*' == pu[4+j]))
								break;
						}
						if (4 == j)
						{
							s++;
							if (s > 1)
								return;
						}
					}
	}
};

Puzzle be;
void initialize()
{
	char m[5];
	for(int a = 0; a <= 9; a++)
		for(int b = 0; b <= 9; b++)
			for(int c = 0; c <= 9; c++)
				for(int d = 0; d <= 9; d++)
				{
					sprintf(m,"%04d",(a*10+b)*(c*10+d));
					memcpy(t[a][b][c][d], m, sizeof(char)*4);
				}
}

int dd;
unsigned char ans[8];

bool ida(int d, unsigned char vis, const Puzzle & p)
{
	if (d == dd)
	{
		if (p.s == 1)
			memcpy(ans, p.pu, sizeof(char)*8);
		return p.s == 1;
	}
	else
	{
		for(int i = 0; i < 8; i++)	//数字变*，变小
		{
			if (vis & bits[i] || '0' == p.pu[i] || '*' == p.pu[i])
				continue;
			
			if (0 == p.s)
			{
				if (ida(d+1, vis | bits[i], p.newp(i, '*')))
					return true;
			}
			if ((i < 4 && p.lmax < p.rmin) || (i >= 4 && p.rmax < p.lmin))
				continue;
			for(char j = p.minb(i); j < p.pu[i]; j++)
			{
				if (ida(d+1, vis | bits[i], p.newp(i, j)))
					return true;
			}
		}
		for(int i = 7; i >= 0; i--)//数字变大，*变数字
		{
			if (vis & bits[i] || '0' == p.pu[i])
				continue;
			
			if('*' == p.pu[i])
			{
				if(0 == p.s)
					continue;
				if ((p.lmax < p.rmin) || (p.rmax < p.lmin))
					continue;
			}
			else
			{
				if ((i < 4 && p.lmin > p.rmax) || (i >= 4 && p.rmin > p.lmax))
					continue;
			}

			for(char j = p.minb(i); j <= '9'; j++)
			{
				bool r;
				r = ida(d+1, vis | bits[i],  p.newp(i, j));
				if (i == 7)
				{
				
				}
				if (r)
					return true;
			}
		}
	}
	return false;
}

int main()
{
	int ka = 0;
	string s;
	initialize();
	while(getline(cin, s) && s[0] != '0')
	{
		string::size_type pos0 = s.find(' ');
		string::size_type pos1 = s.find(' ', pos0+1);
		if (pos0 < 2)
		{
			be.pu[0] = '0';
			be.pu[1] = s[0];
		}
		else
		{
			be.pu[0] = s[0];
			be.pu[1] = s[1];
		}
		if (pos1-pos0 < 2)
		{
			be.pu[2] = '0';
			be.pu[3] = s[pos0+1];
		}
		else
		{
			be.pu[2] = s[pos0+1];
			be.pu[3] = s[pos0+2];
		}
		for(int i = 0; i < 4; i++)
			be.pu[7-i] = (s.length()-1-i > pos1) ? s[s.length()-1-i] : '0';
		be.getsolve();
		
		memset(ans, 0, sizeof(ans));
		for(dd = 0; dd <= 6; dd++)
		{
			if (ida(0, 0, be))
				break;
		}
		cout<<"Case "<<++ka<<": ";
		if ('0' != ans[0])
			cout<<ans[0];
		cout<<ans[1]<<' ';
		if ('0' != ans[0])
			cout<<ans[2];
		cout<<ans[2]<<' ';
		int j;
		for(j = 4; '0' == ans[j]; j++);
		for(; j < 8; j++)
			cout<<ans[j];
		cout<<endl;
	}
}
