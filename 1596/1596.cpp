#include <iostream>
#include <sstream>
#include <map>
#include <string>

using namespace std;

struct Array
{
	int e;
	map<int, int> v;

	Array()
	{}
	
	Array(const int ee)
	{
		e = ee;
	}
};
map<char, Array> arr;

//-1:未初始化
//-2:未声明
//-3:越界
//0-2147483647:正常
int value(const string & s)
{
	int r;
	if (isdigit(s[0]))
	{
		stringstream ss(s);
		ss>>r;
		return r;
	}
	if (arr.count(s[0]) < 1)
		return -2;

	string s1;
	int t1;
	s1 = s.substr(2,s.length()-3);
	t1 = value(s1);
	if (t1 < 0)
		return t1;
	if (t1 >= arr[s[0]].e)
		return -3;
	if (arr[s[0]].v.count(t1) < 1)
		return -1;
	return arr[s[0]].v[t1]; 
}

bool gcc(const string &s)
{
	string::size_type p = s.find('=');

	if(p == string::npos)
	{
		int e;
		string s1 = s.substr(2,s.length()-3);
		stringstream ss(s1);
		ss>>e;
		arr[s[0]] = Array(e);
		return true;
	}
	else
	{
		if(arr.count(s[0]) < 1)
			return false;
		string s1;
		int v1;
		s1 = s.substr(2,p-1);
		v1 = value(s1);
		if (v1 < 0)
			return false;
		if (v1 >= arr[s[0]].e)
			return false;

		string s2;
		int v2;
		s2 = s.substr(p+1);
		v2 = value(s2);
		if (v2 < 0)
			return false;
		arr[s[0]].v[v1] = v2;
		return true;
	}
}


int main()
{
	string s;
	bool flag;
	int line;
	while(cin>>s && s[0] != '.')
	{
		arr.clear();
		line = 1;
		flag = true;
		while(s[0] != '.')
		{
			if(flag)
			{
				flag = gcc(s);
				if(!flag)
					cout<<line<<endl;
			}
			cin>>s;
			line++;
		}
		if(flag)
			cout<<0<<endl;
	}
	return 0;
}
