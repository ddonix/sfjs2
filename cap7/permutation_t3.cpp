#include <iostream>

using namespace std;

struct Node
{
	int d;
	bool operator==(const Node & right)
	{
		return d == right.d;
	}
	
	bool operator!=(const Node & right)
	{
		return d != right.d;
	}
	
	friend ostream & operator<<(ostream & os, Node & node)
	{
		os<<node.d;
		return os;
	}
	
	friend istream & operator>>(istream & is, Node & node)
	{
		is>>node.d;
		return is;
	}
};


Node P[10];
void print_permutation(int n, Node *A, int cur)
{
	if (cur == n)
	{
		for(int i = 0; i < n; i++)
			cout<<A[i]<<" ";
		cout<<endl;
		return;
	}
	for(int i = 0; i < n; i++)
	{
		if(!i || P[i] != P[i-1])
		{
			int c1 = 0, c2 = 0;
			for(int j = 0; j < cur; j++) if(A[j] == P[i]) c1++;
			for(int j = 0; j < n; j++) if(P[i] == P[j]) c2++;
			if(c1 < c2) {
				A[cur] = P[i];
				print_permutation(n, A, cur+1);
			}
		}
	}
}

int main()
{
	Node A[10];
	int n;
	while(cin>>n && n)
	{
		for(int i = 0; i < n; i++)
			cin>>P[i];
		print_permutation(n, A, 0);
	}
}

