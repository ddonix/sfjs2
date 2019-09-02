#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Node
{
	int t;		//type of node: 0:p(grey) ,1:empty(white), 2:full(black), -1:null
	int b;		//number of black bolock
	int d;		//root d: 256
	
	int c[4];
	Node() {}
};

const int maxn = 200000;
Node nodepool[maxn];

int nn = 0;
int newNode()
{
	nn++;
	nodepool[nn].t = -1;
	return nn;
}

int getquadtree(int r, stringstream & ss)
{
	int ch;
	char color;
	ss>>color;
	if ('p' == color)
	{
		nodepool[r].t = 0;
		nodepool[r].b = 0;
		for(int i = 0; i < 4; i++)
		{
			ch = newNode();
			nodepool[ch].d = nodepool[r].d >> 2;
			getquadtree(ch, ss);
			nodepool[r].b += nodepool[ch].b;
			nodepool[r].c[i] = ch;
		}
	}
	else if('e' == color)
	{
		nodepool[r].t = 1;
		nodepool[r].b = 0;
	}
	else
	{
		nodepool[r].t = 2;
		nodepool[r].b = nodepool[r].d;
	}
	return 0;
}

int mergeblack(int qrt1, int qrt2)
{
	if (1 == nodepool[qrt1].t)
		return nodepool[qrt2].b;
	else if (2 == nodepool[qrt1].t)
		return nodepool[qrt1].b;
	else
	{
		if (1 == nodepool[qrt2].t)
			return nodepool[qrt1].b;
		else if (2 == nodepool[qrt2].t)
			return nodepool[qrt2].b;
		else
		{
			int b = 0;
			for(int i = 0; i < 4; i++) b += mergeblack(nodepool[qrt1].c[i], nodepool[qrt2].c[i]);
			return b;
		}
	}
}

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int bpix;
		string s;
		int qroot1, qroot2;
		
		nn = 0;
		
		cin>>s;
		stringstream ss1(s);
		qroot1 = newNode();
		nodepool[qroot1].d = 1024;
		getquadtree(qroot1, ss1);
		
		cin>>s;
		stringstream ss2(s);
		qroot2 = newNode();
		nodepool[qroot2].d = 1024;
		getquadtree(qroot2, ss2);
		
		bpix = mergeblack(qroot1, qroot2);
		cout<<"There are "<<bpix<<" black pixels."<<endl;
	}
}
