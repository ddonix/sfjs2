#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <map>

using namespace std;
struct Book
{
	string author;
	int state;		//the state of a book. 	
				//0:on shelve,  1:borrow,  2:on table
				//
	Book()
	{
	}
	
	Book(const string &a)
	{
		author = a;
		state = 0;
	}
};

map<string, Book> m;
bool cmp(const string &a, const string &b)
{
	if (m[a].author == m[b].author)
		return a < b;
	return m[a].author < m[b].author;
}

int main()
{
	vector<string> db;
	vector<string>::iterator it;
	string::size_type p;
	string s, title, author;

	while(getline(cin,s) && s[0] != 'E')
	{
       		p = s.find("\"", 1);
		title = s.substr(0, p+1);
		author = s.substr(p+5);
		
		m[title] = Book(author);
		db.push_back(title);
	}
	sort(db.begin(), db.end(), cmp);
	
	while(cin>>s && s[0] != 'E')
	{
		string s1;
		if (s[0] != 'S')
		{
			getchar();
			getline(cin,s1);
			s1 = s1.substr(0,s1.find('\"', 1)+1);
			it = find(db.begin(), db.end(), s1);
			if (s[0] == 'B')
				m[*it].state = 1;
			else
				m[*it].state = 2;
		}
		else 
		{
			for(int i = 0; i < db.size(); i++)
			{
				int j;
				if(m[db[i]].state != 2)
					continue;
				cout<<"Put "<<db[i];
				for(j = i; j > 0; j--)
				{
					if (m[db[j]].state == 0)
						break;
				}

				if (m[db[j]].state == 0)
				{
					cout<<" after "<<db[j]<<endl;
				}
				else
				{
					cout<<" first"<<endl;
				}
				m[db[i]].state = 0;
			}
			cout<<"END"<<endl;
		}
	}
}
