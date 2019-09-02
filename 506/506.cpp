#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

struct Node
{
	string name;
	set<int> father;
	vector<int> child;
	int state;		//0:not installed  1:installed(ac) 2:install(pa)
	Node():state(0){}
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
		noodpool[fa].child.push_back(ch);
		noodpool[ch].father.insert(fa);
	}
}

void list()
{
	for(int i = 0; i < installed.size(); i++)
		cout<<"   "<<noodpool[installed[i]].name<<endl;
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
	cout<<"   Installing "<<noodpool[id].name<<endl;
	noodpool[id].state = ac ? 1:2;
}

void install(string item)
{
	int id = getNode(item);
	if(noodpool[id].state)
		cout<<"   "<<noodpool[id].name<<" is already installed."<<endl;
	else	
		_install(id, true);
}

bool isDep(int id)
{
	for(auto it = noodpool[id].father.begin(); it != noodpool[id].father.end(); it++)
		if (noodpool[*it].state)
			return true;
	return false;
}

void _remove(int id, bool ac)
{
	if (!noodpool[id].state)
		return;
	if (1 == noodpool[id].state && !ac)		//主动安装的不能被被动删除
		return;
	if (isDep(id))
	{
		if (ac == true)
			cout<<"   "<<noodpool[id].name<<" is still needed."<<endl;
		return;
	}
	cout<<"   Removing "<<noodpool[id].name<<endl;
	noodpool[id].state = 0;
	for(auto it = installed.begin(); it != installed.end(); it++)
	{
		if (*it == id)
		{
			installed.erase(it);
			break;
		}
	}
	for(int i = 0; i < noodpool[id].child.size(); i++)
		_remove(noodpool[id].child[i], false);
}

void remove(string item)
{
	int id = getNode(item);
	if(!noodpool[id].state)
		cout<<"   "<<noodpool[id].name<<" is not installed."<<endl;
	else	
		_remove(id, true);
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
