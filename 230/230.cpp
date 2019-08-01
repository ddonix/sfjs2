#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <set>

using namespace std;

struct Book
{
	string title;
	string author;

	Book(string s)
	{
		string::size_type p = s.find("\"", 1);
		title = s.substr(1, p-1);
		author = s.substr(p+5);
	}

	//其实是<=
	bool operator == (const Book & right) const
	{
		if (author < right.author)
			return true;
		else if(author > right.author)
			return false;
		else if(title <= right.title)
			return true;
		return false;
	}
};

int cmp(const Book & a, const Book & b)
{
	if (a.author < b.author)
		return 1;
	else if(a.author > b.author)
		return 0;
	return a.title < b.title;
}

int main()
{
	vector<Book> v;
	string s;
	while(getline(cin,s) && s != "END" && s != "END\r")
	{
		v.push_back(Book(s));
	}
	sort(v.begin(), v.end(), cmp);

	find(v.begin(), v.end(), Book("asd"));

	stack<string> rt;
	while(getline(cin,s) && s != "END" && s != "END\r")
	{
		string s1;
		cout<<s<<endl;
		if (s[0] == 'B')
		{
			s1 = s.substr(8, s.length()-2);
		}
		else if (s[0] == 'R')
		{
			s1 = s.substr(8, s.length()-2);
		}
		else
		{
		
		}
	}
	cout<<"END"<<endl;
}
