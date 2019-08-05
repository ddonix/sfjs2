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
	{}

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
			data.push_back(d/JZ);
			data.push_back(d%JZ);
		}
	}
	
	LLL(string d)
	{
		string str;
		w = (d.length()-1)/9+1;
		
		int f = d.length()-(w-1)*9;
		str = d.substr(0,f); 
		for(int i = 0; i < w-1; i++)
		{
			str += ' ';
			str += d.substr(f+i*9, 9);
		}
		stringstream ss(str);
		for(int i = 0; i < w; i++)
		{	
			unsigned long t;
			ss>>t;
			data.push_back(t);
		}
	}
	void print(void)
	{
		string r;
		for(int i = 0; i < w; i++)
		{
			stringstream ss;
			ss<<data[i];
			string s = ss.str();
			r += s;
		}
		cout<<r<<endl;	
	}
};

int main()
{
	LLL a("12345678912323453423423424124");
	a.print();
	LLL b(1234);
	b.print();
	LLL c("123456789");
	c.print();
	LLL d("123456789123456789");
	d.print();
	LLL e("123456789123456789333");
	e.print();
	LLL f(1234567899);
	f.print();
}
