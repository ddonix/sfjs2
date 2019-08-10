#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Node
{
	int value;
	
	int c[4];
	Node(int v) : value(v) {}
	Node() {}
};

const int maxn = 20000;
Node nodepool[maxn];

int nn = 0;
int newNode()
{
	nn++;
	nodepool[nn].value=0;
	for(int i = 0; i < 4; i++) nodepool[nn].c[i] = 0;
	return nn;
}

int getquadtree(int r, stringstream & ss)
{
	int ch;
	char color;
	ss>>color;
	if ('p' == color)
	{
		nodepool[r].value = 0;
		for(int i = 0; i < 4; i++)
		{
			ch = newNode();
			getquadtree(ch, ss);
			nodepool[r].c[0] = ch;
		}
	}
	else if('e' == color)
		nodepool[r].value = 1;
	else
		nodepool[r].value = 2;
	return 0;
}

int black(int r)
{
	if (nodepool[r].value)
		return nodepool[r].value-1;
	else
	{
		int b = 0;
		for(int i = 0; i < 4; i++) b += black(nodepool[r].c[i]);
		return b;
	}
}

int mergeblack(int qrt1, int qrt2)
{
	if (0 == nodepool[qrt1].value)
		return black(qrt2);
	else if (1 == nodepool[qrt1].value)
		return 1;
	else
	{
		if (0 == nodepool[qrt1].value)
			return black(qrt2);
		else if (1 == nodepool[qrt1].value)
			return 1;
	}
	return 0;
}

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int bpix;
		char s[1000];
		int qroot1, qroot2;
		
		nn = 0;
		
		cin>>s;
		stringstream ss1(s);
		qroot1 = newNode();
		getquadtree(qroot1, ss1);
		
		cin>>s;
		stringstream ss2(s);
		qroot2 = newNode();
		getquadtree(qroot2, ss2);
		
		bpix = mergeblack(qroot1, qroot2);
		cout<<"There are "<<bpix<<" black pixels."<<endl;
	}
}
