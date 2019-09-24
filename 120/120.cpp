#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <vector>
using namespace std;

vector<int> v;
int n;

void wash(int l)
{
	stack<int> st;
	for(int i = 0; i < l; i++)
		st.push(v[i]);
	for(int i = 0; i < l; i++)
	{
		int a = st.top();
		st.pop();
		v[i] = a;
	}
}

void sorts()
{
	n = v.size();
	bool first = true;
	for(int i = n-1; i > 0; i--)
	{
		int max = v[i], ind = i;
		for(int j = 0; j < i; j++)
		{
			if (v[j] > max)
			{
				max = v[j];
				ind = j;
			}
		}
		if (0 == ind)
		{
			cout<<(first ? "" : " ");
			first = false;
			cout<<n-i;
			wash(i+1);
		}
		else if (ind < i)
		{
			cout<<(first ? "" : " ");
			first = false;
			cout<<n-ind<<endl;
			wash(ind+1);
			cout<<n-i;
			wash(i+1);
		}
	}
	cout<<(first ? "" : " ");
	cout<<0<<endl;
}

int main()
{
	string s;
	while(getline(cin, s) && "" != s)
	{
		cout<<s<<endl;
		v.clear();
		stringstream ss(s);
		int d;
		while(ss>>d)
		{
			v.push_back(d);
		}
		sorts();
	}
	return 0;
}
