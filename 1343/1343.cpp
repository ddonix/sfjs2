#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const unsigned char bit[] = {0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80};
const int pos[8][2] = {{0,2}, {0,3}, {0,4}, {1,2}, {1,3}, {1,4}, {2,4}, {3,4}};

int maxd = 15;
int dd;
unsigned char bg[4], ed[4];
int dn[4][2][3] = {{{2,2,2}, {3,4,2}}, {{2,2,4}, {3,4,4}}, {{0,2,2}, {1,4,2}}, {{0,2,4}, {1,4,4}}};

int h(unsigned char *s)
{
	int r = 0;
	for(int i = 0; i < 8; i++)
		if (!(s[pos[i][0]] & bit[pos[i][1]]))
			r++;
	return r;
}

void nexts(unsigned char *s, int d)
{
	if(d<4)
	{
		s[d] = s[d] << 1;
		if (s[d] & bit[7])
			s[d] |= bit[0];
		else
			s[d] &= ~bit[0];
	}
	else
	{
		d = d-4;
		if (s[d] & bit[0])
			s[d] |= bit[7];
		else
			s[d] &= ~bit[7];
		s[d] = s[d] >> 1;
	}
	for(int i = 0; i < 2; i++)
	{
		if (s[d] & bit[dn[d][i][1]])
			s[dn[d][i][0]] |= bit[dn[d][i][2]];
		else
			s[dn[d][i][0]] &= ~bit[dn[d][i][2]];
	}
}

void nexts(unsigned char *s, unsigned char *n, int d)
{
	memcpy(n, s, sizeof(unsigned char)*4);
	if(d<4)
	{
		n[d] = n[d] << 1;
		if (n[d] & bit[7])
			n[d] |= bit[0];
		else
			n[d] &= ~bit[0];
	}
	else
	{
		d = d-4;
		if (n[d] & bit[0])
			n[d] |= bit[7];
		else
			n[d] &= ~bit[7];
		n[d] = n[d] >> 1;
	}
	for(int i = 0; i < 2; i++)
	{
		if (n[d] & bit[dn[d][i][1]])
			n[dn[d][i][0]] |= bit[dn[d][i][2]];
		else
			n[dn[d][i][0]] &= ~bit[dn[d][i][2]];
	}
}

int ida(int d, int pre)
{
	if (d == dd)
		return !memcmp(bg, ed, 4);
	else
	{
		if (h(bg) > (dd-d))
			return false;
		for(int i = 0; i < 8; i++)
		{
			if (i == (pre+4) || i == (pre-4))
				continue;
			nexts(bg, i);
			if (ida(d+1, i))
				return true;
			nexts(bg, (i < 4) ? i+4 : i-4);
		}
		return false;
	}
}

int main()
{
	char ori[4][7];
	int ans, r;
	
	for(int i = 0; i < 4; i++)
		ed[i] = 0x1c;
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 7; j++)
			cin>>ori[i][j];
	ans = maxd;
	for(char b = '1'; b <= '3'; b++)
	{
		for(int i = 0; i < 4; i++)
		{
			bg[i] = 0;
			for(int j = 0; j < 7; j++)
				bg[i] |= ((ori[i][j] == b) ? bit[j] : 0);
		}
		for(dd = 0; dd < maxd; dd++)
			if (ida(0, -5))
				break;
		ans = (ans < dd) ? ans : dd;
	}
	cout<<ans<<endl;
	return 0;
}
