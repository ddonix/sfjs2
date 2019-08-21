#include <iostream>

using namespace std;

struct Node
{
	int d;
	bool operator==(const Node & right)
	{
		return d == right.d;
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
	for(int i = 1; i <= n; i++)
	{
		bool ok = true;
		for(int j = 0; j < cur; j++)
			if (A[j] == P[i])
				ok = false;
		if(ok)
		{
			A[cur] = P[i];
			print_permutation(n, A, cur+1);
		}
	}
}

int main()
{
	Node A[10];
	int n;
	while(cin>>n && n)
	{
		for(int i = 1; i <= n; i++)
			cin>>P[i];
		print_permutation(n, A, 0);
	}
}

