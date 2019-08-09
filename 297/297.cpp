#include <iostream>

using namespace std;

struct Node
{
	int value;
	
	int c1;
	int c2;
	int c3;
	int c4;
	Node(int v) : value(v), c1(0), c2(0), c3(0), c4(0) {}
	Node() : c1(0), c2(0), c3(0), c4(0) {}
};

const int maxn = 10000;
Node quadtree1[maxn];
Node quadtree2[maxn];
Node *quadtree;

int nqt1;
int nqt2;
int *nqt;

int newNode()
{
	*nqt++;
	return *nqt;
}

char * getquadtree(int r, char *s)
{
	int c1, c2, c3, c4;
	int c;
	char *s1;
	if ('p' == *s)
	{
		c1 = newNode();
		c2 = newNode();
		c3 = newNode();
		c4 = newNode();
		s1 = getquadtree(c1, s+1);
		s2 = getquadtree(c2, s1);
		s3 = getquadtree(c3, s2);
		s4 = getquadtree(c4, s3);
	}
	else if('e' == *s)
	{
		quadtree[r].value = 0;
		return s++;
	}
	else
	{
		quadtree[r].value = 1;
		return s++;
	}
}

int merge()
{

}

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int bpix;
		char s[1000];
		
		nqt1 = 0;
		nqt = &nqt1;
		quadtree = quadtree1;
		cin>>s;
		getquadtree(1, s);
		
		nqt2 = 0;
		nqt = &nqt2;
		quadtree = quadtree2;
		cin>>s;
		getquadtree(1, s);
		
		bpix = merge();
		cout<<"There are "<<bpix<<" black pixels."<<endl;
	}
}
