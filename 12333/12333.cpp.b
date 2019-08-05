#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const int JZ = 1000000000;
const int MAXB = 999999999;
const int ZS = 9;

struct LLL
{
	int w;
	vector<unsigned long> data;

	LLL()
	{
		w = 1;
		data.push_back(0);
	}

	LLL(unsigned long d)
	{
		if (d < JZ)
		{
			w = 1;
			data.push_back(d);
		}
		else
		{
			w = 2;
			data.push_back(d%JZ);
			data.push_back(d/JZ);
		}
	}
	
	LLL(string d)
	{
		string str;
		w = (d.length()-1)/9+1;
		data.resize(w);
		
		int f = d.length()-(w-1)*9;
		str = d.substr(0,f); 
		for(int i = 0; i < w-1; i++)
		{
			str += ' ';
			str += d.substr(f+i*9, 9);
		}
		stringstream ss(str);
		for(int i = w-1; i >= 0; i--)
		{	
			unsigned long t;
			ss>>t;
			data[i] = t;
		}
	}

	LLL operator +(const LLL & right)
	{
		LLL temp;
		unsigned long c = 0, t;
		int w1 = (w < right.w) ? w : right.w;
		int w2 = (w > right.w) ? w : right.w;
		temp.w = w2;
		temp.data.resize(w2);
		
		for(int i = 0; i < w1; i++)
		{
			t = data[i]+right.data[i]+c;
			if (t > JZ)
			{
				c = 1;
				temp.data[i] = t-JZ;
			}
			else
			{
				c = 0;
				temp.data[i] = t;
			}
		}
		const vector<unsigned long> *x=0;
		if (w < right.w)
			x = &right.data;
		else if(w > right.w)
			x = &data;
		if(x)
		{
			for(int i = w1; i < w2; i++)
			{
				t = (*x)[i]+c;
				if (t > JZ)
				{
					c = 1;
					temp.data[i] = t-JZ;
				}
				else
				{
					c = 0;
					temp.data[i] = t;
				}
			}
		}
		if(c)
		{
			temp.w++;
			temp.data.push_back(c);
		}
		return temp;
	}

	void print(void)
	{
		string r;
		for(int i = w-1; i >= 0; i--)
		{
			stringstream ss;
			ss<<data[i];
			string s = ss.str()+" ";
			r += s;
		}
		cout<<r<<endl;	
	}

	void getstr(string &r)
	{
		for(int i = w-1; i >= 0; i--)
		{
			stringstream ss;
			ss<<data[i];
			string s = ss.str();
			r += s;
		}
	}
};

int main()
{

	int t;
	cin>>t;
	for(int i = 1; i <= t; i++)
	{
		LLL a(1), b(1);
		string s;
		cin>>s;
		if (s == "1")
		{
			cout<<"case #"<<i<<": "<<0<<endl;
			continue;
		}
		int j;
		for(j = 2; j <= 100000; j++)
		{
			LLL c = a+b;
			string ss;
			a = b;
			b = c;
			c.getstr(ss);
			if(j == 226){
				c.print();
cout<<"*******************"<<endl;
}
			
			if (ss.length() < s.length())
				continue;
			ss = ss.substr(0, s.length());
			if (s == ss)
			{
				cout<<"case #"<<i<<": "<<j<<endl;
				break;
			}
		}
		if(j > 100000)
			cout<<"case #"<<i<<": "<<-1<<endl;
	}
}
