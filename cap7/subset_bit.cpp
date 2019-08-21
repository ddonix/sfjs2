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

void print_subset(int n, int b)
{
	//打印当前集合
	for (int i = 0; i < n; i++)
		if ((1<<i) & b)
			cout<<P[i]<<" ";
	cout<<endl;
}

int main()
{
	Node A[10];
	int n;
	while(cin>>n && n)
	{
		for(int i = 0; i < n; i++)
			cin>>P[i];
		for(int i = 1; i < (1<<n); i++)
			print_subset(n, i);
	}
}
