#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct MAP {
	MAP(const char*);
	MAP(const MAP&);

	//string name;
	int a;
//	double w, e;
	/*double n, s;
	double area;
	double ratio;*/
};
 
MAP::MAP(const char* s)
{
}

MAP::MAP(const MAP& rhs)
{
}


int main()
{
	MAP s0("hello");
	vector<MAP> vec;
	vector<double> vvv;
	vec.push_back(s0);
	vvv.push_back(0.0);
	/*
	printInfo(vec);
	vec.push_back(s0);
	printInfo(vec);
	vec.push_back(s0);
	printInfo(vec);
	vec.push_back(s0);
	printInfo(vec);
*/
	return 0;
}
