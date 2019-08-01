#include <iostream>
#include <sstream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int n,m;

char op(char ch)
{
	if (ch >= 'a' && ch <= 'z')
		return ch;
	if (ch >= 'A' && ch <= 'Z')
		return ch-'A'+'a';
	return ' ';
}

struct Line
{
	string str;
	set<string> w;

	Line(const string & s) : str(s) {}
};

struct Docu
{
	vector<Line> line;
	set<string> w;
	
	void addline(const string & s)
	{
		Line l(s);
		
		string s1;
		s1.resize(s.size());
		transform(s.begin(), s.end(), s1.begin(), op);

		stringstream ss(s1);
		string s2;

		while(ss>>s2)
		{
			l.w.insert(s2);
			w.insert(s2);
		}
		line.push_back(l);
	}
};

vector<Docu> d;

void findOne(const string & s)
{
	bool flagall;
	flagall = false;
	for(int i = 0; i < n; i++)
	{
		if(d[i].w.count(s) < 1)
			continue;
		if (i > 0 && flagall)
			cout<<"----------"<<endl;
		flagall = true;
		for(int j = 0; j < d[i].line.size(); j++)
			if (d[i].line[j].w.count(s))
				cout<<d[i].line[j].str<<endl;
	}
	if(!flagall)
		cout<<"Sorry, I found nothing."<<endl;
}

void findOr(const string & s1, const string & s2)
{
	bool flagall;
	flagall = false;
	for(int i = 0; i < n; i++)
	{
		if ((d[i].w.count(s1) < 1) && (d[i].w.count(s2) < 1))
			continue;
		if (i > 0 && flagall)
			cout<<"----------"<<endl;
		flagall = true;
		for(int j = 0; j < d[i].line.size(); j++)
			if (d[i].line[j].w.count(s1) || d[i].line[j].w.count(s2))
				cout<<d[i].line[j].str<<endl;
	}
	if(!flagall)
		cout<<"Sorry, I found nothing."<<endl;
}

void findAnd(const string & s1, const string & s2)
{
	bool flagall;
	flagall = false;
	for(int i = 0; i < n; i++)
	{
		if (!(d[i].w.count(s1) && d[i].w.count(s2)))
			continue;
		if (i > 0 && flagall)
			cout<<"----------"<<endl;
		flagall = true;
		for(int j = 0; j < d[i].line.size();j++)
			if (d[i].line[j].w.count(s1) || d[i].line[j].w.count(s2))
				cout<<d[i].line[j].str<<endl;
	}
	if(!flagall)
		cout<<"Sorry, I found nothing."<<endl;
}

void findNot(const string &s)
{
	bool flagall;
	flagall = false;
	for(int i = 0; i < n; i++)
	{
		int j;
		if(d[i].w.count(s) == 1)
			continue;
		if (i > 0 && flagall)
			cout<<"----------"<<endl;
		flagall = true;
		for(j = 0; j < d[i].line.size(); j++)
			cout<<d[i].line[j].str<<endl;
	}
	if(!flagall)
		cout<<"Sorry, I found nothing."<<endl;
}

int main()
{
	int i;
	string s;
	cin>>n;
	cin.ignore();
	d.resize(n);
	i = 0;
	for(i = 0; i < n; i++)
	{
		while(getline(cin, s) && s[0] != '*')
		{
			d[i].addline(s);
		}
	}
	cin>>m;
	cin.ignore();
	for(i = 0; i < m; i++)
	{
		string s1, s2;
		string::size_type p,p1;
		
		getline(cin, s);
		p = s.find(' ');
		if (p == string::npos)
			findOne(s);
		else
		{
			p1 = s.find(' ', p+1);
			if (p1 == string::npos)
				findNot(s.substr(4));
			else
			{
				string s3,s4;
				s3 = s.substr(0,p);
				s4 = s.substr(p1+1);
				if(s3 == s4)
					findOne(s3);
				else if((p1-p) == 3)
					findOr(s3, s4);
				else
					findAnd(s3, s4);
			}
		}
		cout<<"=========="<<endl;
	}
	return 0;
}
