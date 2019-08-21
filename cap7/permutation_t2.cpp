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
	for(int i = 0; i < n;)
	{
		int j;
		for(j = 0; j < cur && A[j] != P[i]; j++);
		if (j < cur)
			i++;
		else
		{
			int k = 0;
			do
			{
				A[cur+k] = P[i++];
				k++;
			}while(i < n && cur+k < n && A[cur+k-1] == P[i]);
			print_permutation(n, A, cur+k);
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

