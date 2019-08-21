#include <iostream>
#include <algorithm>

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
	
	bool operator<(const Node & right)
	{
		return d < right.d;
	}
	
	bool operator>(const Node & right)
	{
		return d > right.d;
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
void print_subset(int n, Node *A, int cur)
{
	//打印当前集合
	for (int i = 0; i < cur; i++)
		cout<<A[i]<<" ";
	cout<<endl;
	
	//递归构造子集
	for (int i = 0; i < n; i++) {
		if (!cur || P[i] > A[cur-1])
		{
			A[cur] = P[i];
			print_subset(n, A, cur + 1);
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
		print_subset(n, A, 0);
	}
}
