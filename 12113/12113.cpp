/* uva 12113: 思路： 	bfs + 打表。状态共有1+A(9,1)+A(9,2)+A(9,3)+A(9,4)+A(9,5)+A(9,6) = 79210种.每个状态64位，
 * 			空间开销79210*8=633680 Byte.状态排序，二分查找。
 * 
 */
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int sid = 0;
unsigned long long state[792100];

unsigned long bits[32]; 

struct  Array
{
	unsigned long vis;
	unsigned long a;

	Array() {}
	Array(unsigned long v_, unsigned long a_) : vis(v_) , a(a_) {}

	Array newArray(int pos, int p)
	{
		Array r;
		r.vis = vis | bits[p];
		r.a = a | (((p<<1)+1) << pos);
		return r;
	}

	void genstate(unsigned long long & s)
	{
		s = 1;
	}
};

void initialize()
{
	unsigned long b = 0x1;
	for(int i = 0; i < 32; i++)
	{
		bits[i] = b;
		b = (b << 1);
	}
}

void tabulation()
{
	int i;
	queue<Array> q;
	q.push(Array(0, 0));

	while(!q.empty())
	{
		Array arr = q.front();
		q.pop();

		arr.genstate(state[sid++]);
		for(i = 0; i <= 25 && (arr.a & bits[i]); i += 5);
		if (i > 25)
			continue;
		
		for(int p = 0; p < 9; p++)
		{
			if (arr.vis & bits[p])
				continue;
			q.push(arr.newArray(i, p));
		}
	}
}

int main()
{
	initialize();
	tabulation();
	sort(state, state+792100);
	cout<<sid<<endl;
}
