#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

char op(char ch)
{
	if (ch == '{' || ch == '}' || ch == ',' || ch == ':')
		return ' ';
	return ch;
}

void analy(const string & s, map<string,string> & m, vector<string> & v)
{
	string s1;
	string key,value;
	s1.resize(s.size());

	transform(s.begin(), s.end(), s1.begin(), op);

	stringstream ss(s1);
	
	while(ss>>key && key != "")
	{
		v.push_back(key);
		ss>>value;
		m[key] = value;
	}
	sort(v.begin(), v.end());
}

int main()
{	
	int T;
	cin>>T;

	while(T--)
	{
		vector<string> va,vb;
		map<string, string> ma,mb;
		string s;

		cin>>s;
		analy(s, ma, va);
		cin>>s;
		analy(s, mb, vb);
		bool aflag, sflag, cflag;

		aflag = false;
		for(int i = 0; i < vb.size(); i++)
		{
			if(ma.count(vb[i]) < 1)
			{
				if(!aflag)
				{
					cout<<"+"<<vb[i];
					aflag = true;
				}
				else
					cout<<","<<vb[i];
			}
		}
		if(aflag)
			cout<<endl;
		
		sflag = false;
		for(int i = 0; i < va.size(); i++)
		{
			if(mb.count(va[i]) < 1)
			{
				if(!sflag)
				{
					cout<<"-"<<va[i];
					sflag = true;
				}
				else
					cout<<","<<va[i];
			}
		}
		if(sflag)
			cout<<endl;
		
		cflag = false;
		for(int i = 0; i < va.size(); i++)
		{
			if(mb.count(va[i]) == 1 && (mb[va[i]] != ma[va[i]]))
			{
				if(!cflag)
				{
					cout<<"*"<<va[i];
					cflag = true;
				}
				else
					cout<<","<<va[i];
			}
		}
		if(cflag)
			cout<<endl;

		if(!(aflag || sflag || cflag))
			cout<<"No changes"<<endl;
		cout<<endl;
	}
	return 0;
}

