#include <iostream>
#include <cstring>
#include <vector>
#include <list>
#include <map>

using namespace std;

struct Node
{
	int i;
	string name;
	int father;
	vector<int> child;
};

const int maxn = 10000;
Node noodpool[maxn];

vector<int> installed_ob;
vector<int> installed_im;

int main()
{
	
}
