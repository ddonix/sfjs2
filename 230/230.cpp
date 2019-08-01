#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <stack>

using namespace std;
	
map<string, string> m;

struct Author 
{
	string name;
	vector<string> book;

	Author(const string &s, const string &b)
	{
		name = s;
		book.push_back(b);
	}

	bool operator < (Author & right) const
	{
		return name < right.name;
	}
};

struct FindByAuthorTitle
{
	FindByAuthorTitle(const string &s, int t) : str(s), type(t)
	{}
	
	bool operator()(const Author & b)
	{
		if (type)
			return m[str] == b.name;
		return str == b.name;
	}
	string str;
	int type;
};

int main()
{
	vector<Author> db;
	vector<Author>::iterator it;
	vector<string>::iterator it2;
	string::size_type p;

	string s, title, author;
	
	while(getline(cin,s) && s != "END" && s != "END\r")
	{
       		p = s.find("\"", 1);
		title = s.substr(1, p-1);
		author = s.substr(p+5);

		m[title] = author;
		it = find_if(db.begin(), db.end(), FindByAuthorTitle(author, 0));
		if (it == db.end())
			db.push_back(Author(author, title));
		else
			(*it).book.push_back(title);
	}
	for(it = db.begin(); it != db.end(); it++)
		sort((*it).book.begin(), (*it).book.end());
	sort(db.begin(), db.end());
	
	stack<string> rt;
	while(getline(cin,s) && s != "END" && s != "END\r")
	{
		string s1;
		cout<<s<<endl;
		if (s[0] == 'B')
		{
			cout<<s1<<endl;
			s1 = s.substr(8, s.length()-10);
			it = find_if(db.begin(), db.end(), FindByAuthorTitle(s1, 1));
			it2 = find((*it).book.begin(), (*it).book.end(), s1);
			(*it).book.erase(it2);
		}
		else if (s[0] == 'R')
		{
			s1 = s.substr(8, s.length()-10);
			rt.push(s1);
			cout<<s1<<endl;
		}
		else
		{
		
		}
	}
	cout<<"END"<<endl;
}
