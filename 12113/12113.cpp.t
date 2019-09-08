/* uva 12113: 思路： 	bfs + 打表。状态共有1+A(9,1)+A(9,2)+A(9,3)+A(9,4)+A(9,5)+A(9,6) = 79210种.每个状态64位，
 * 			空间开销79210*8=633680 Byte.状态排序，二分查找。
 * 
 */
#include <iostream>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

int sid = 0;
unsigned long long state[792100];

unsigned long bits[32]; 

int inline axistoi(bool rf, int x, int y)
{
	return x*(2*4+1)+y+(rf ? 0 : 4);
}

struct  Array
{
	unsigned long vis;
	unsigned long a;
	unsigned long long s;

	Array() {}

	Array newArray(int pos, int p)
	{
		Array r;
		r.vis = vis | bits[p];
		r.a = a | (((p<<1)+1) << pos);

		int x = pos/3, y = pos%3;
		r.s = s;

		r.s |= bits[axistoi(true, x,y)];
		r.s |= bits[axistoi(true, x+1,y)];
		r.s |= bits[axistoi(true, x,y+2)];
		r.s |= bits[axistoi(true, x+1,y+2)];
		r.s |= bits[axistoi(false, x,y)];
		r.s |= bits[axistoi(false, x,y+1)];
		r.s |= bits[axistoi(false, x+2,y)];
		r.s |= bits[axistoi(false, x+2,y+1)];
		
		r.s &= bits[axistoi(true, x,y+1)];
		r.s &= bits[axistoi(true, x+1,y+1)];
		r.s &= bits[axistoi(false, x+1,y)];
		r.s &= bits[axistoi(false, x+1,y+1)];
		return r;
	}
};

Array be;
void initialize()
{
	unsigned long b = 0x1;
	for(int i = 0; i < 32; i++)
	{
		bits[i] = b;
		b = (b << 1);
	}
	be.vis = 0;
	be.a = 0;
	be.s = 0;
}

void tabulation()
{
	int i;
	queue<Array> q;
	q.push(be);

	while(!q.empty())
	{
		Array arr = q.front();
		q.pop();

		state[sid++] = arr.s;
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
	int ka = 0;
	initialize();
	tabulation();
	sort(state, state+792100);

	string str;
	getline(cin, str);
	while(str.size() > 1)
	{
		unsigned long long s = 0;
		bool rf;
		int x = 0, y;
		do
		{
			for(int i = 0; i < 9; i++)
			{
				if (str[i] != ' ')
				{
					rf = i%2;
					y = i/2;
					s |= bits[axistoi(rf, x,y)];
				}
			}
			getline(cin, str);
		}while(x++ < 5);
		
		auto it = find(state, state+792100, s);
		if (it == state+792100)
			cout<<"Case "<<++ka<<": No"<<endl;
		else
			cout<<"Case "<<++ka<<": Yes"<<endl;
	}
}