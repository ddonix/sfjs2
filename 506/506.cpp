#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <vector>

using namespace std;

struct Node
{
	string name;
	int father;
	vector<int> child;
	int state;		//0:not installed  1:installed(ob) 2:install(ed)
	Node():father(-1), state(0){}
};

const int maxn = 10000;
Node noodpool[maxn];		//item pool
int n = 0;			//item number

vector<int> installed;		//installed item

int getNode(string &s)
{
	for(int i = 0; i < n; i++)
		if(noodpool[i].name == s)
			return i;
	noodpool[n].name = s;
	n++;
	return n-1;
}

void depend(queue<string> & q)
{
	int fa, ch;
	string b, u;
	b = q.front();
	q.pop();
	fa = getNode(b);
	while(!q.empty())
	{
		u = q.front();
		q.pop();
		
		ch = getNode(u);
		noodpool[ch].father = fa;
		noodpool[fa].child.push_back(ch);
	}
}

void list()
{
	for(int i = 0; i < installed.size(); i++)
		cout<<"  "<<noodpool[installed[i]].name<<endl;
}

void _install(int id, bool ac)
{
	if (noodpool[id].state)
		return;
	for(int i = 0; i < noodpool[id].child.size(); i++)
	{
		int ch = noodpool[id].child[i];
		_install(ch, false);
	}
	installed.push_back(id);
	cout<<"  Installing "<<noodpool[id].name<<endl;
	noodpool[id].state = ac ? 1:2;
}

void install(string item)
{
	int id = getNode(item);
	if(noodpool[id].state)
		cout<<"  "<<noodpool[id].name<<" is already installed."<<endl;
	else	
		_install(id, true);
}

bool isDep(int id)
{

}

void _remove(int id, bool ac)
{
	if (!noodpool[id].state)
		return;
	if (isDep(id))
	{
		cout<<"  "<<noodpool[id].name<<" is still needed."<<endl;
	}
}

void remove(string item)
{
	int id = getNode(item);
	if(!noodpool[id].state)
		cout<<"  "<<noodpool[id].name<<" is not installed."<<endl;
	else	
		_install(id, true);
}

void _remove(int id)
{

}
void remove(string item)
{

}

int main()
{
	string s;
	while(getline(cin, s) && s != "END")
	{
		n = 0;
		while(1)
		{
			stringstream ss(s);
			string s1;
			cout<<s<<endl;
			ss>>s1;
			if ('D' == s[0])
			{
				queue<string> q;
				string s1;
				while(ss>>s1)
				{
					q.push(s1);
				}
				depend(q);
			}
			else if('L' == s[0])
			{
				list();
			}
			else if('I' == s[0])
			{
				ss>>s1;
				install(s1);
			}
			else if('R' == s[0])
			{
				ss>>s1;
				remove(s1);
			}
			else
			{
				break;	
			}
			getline(cin, s);
		}
	}

}

int main()
{
	string s;
	while(getline(cin, s) && s != "END")
	{
		n = 0;
		while(1)
		{
			stringstream ss(s);
			string s1;
			cout<<s<<endl;
			ss>>s1;
			if ('D' == s[0])
			{
				queue<string> q;
				string s1;
				while(ss>>s1)
				{
					q.push(s1);
				}
				depend(q);
			}
			else if('L' == s[0])
			{
				list();
			}
			else if('I' == s[0])
			{
				ss>>s1;
				install(s1);
			}
			else if('R' == s[0])
			{
				ss>>s1;
				remove(s1);
			}
			else
			{
				break;	
			}
			getline(cin, s);
		}
	}
}
