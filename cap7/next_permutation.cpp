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


int main()
{
	Node P[10];
	int n;
	while(cin>>n && n)
	{
		for(int i = 0; i < n; i++)
			cin>>P[i];
		sort(P, P+n);
		do
		{
			for(int i = 0; i < n; i++)
				cout<<P[i]<<" ";
			cout<<endl;
		}while(next_permutation(P, P+n));
	}
}

