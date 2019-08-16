#include <iostream>
#include <cstring>
#include <stack>

using namespace std;

string b;

bool isValid()
{
	int l = b.size();
	stack<char> s;
	for(int i = 0; i < l; i++)
	{
		if('(' == b[i] || '[' == b[i])
			s.push(b[i]);
		else if(')' == b[i])
		{
			if (s.empty() || s.top() != '(')
				return false;
			s.pop();
		}
		else if(']' == b[i])
		{
			if (s.empty() || s.top() != '[')
				return false;
			s.pop();
		}
		else
			return false;
	}
	return s.empty();
}

int main()
{
	int n;
	cin>>n;
	cin.ignore(1024, '\n');
	while(n--)
	{
		getline(cin, b);
		if(isValid())
			cout<<"Yes"<<endl;
		else
			cout<<"No"<<endl;
	}
}
