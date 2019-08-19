#include <iostream>
#include <stack>
#include <vector>

using namespace std;

vector<stack<string> > st;

bool match(int a, int b)
{
	string c0 = st[a].top();
	string c1 = st[b].top();
	if ((c0[0] == c1[0]) || (c0[1] == c1[1]))
		return true;
	return false;
}

bool move(int a, int b)
{
	st[a].push(st[b].top());
	st[b].pop();
	return st[b].empty();
}

void accordian()
{
	int l;
	bool running = true;
	bool refor = false;
	while(running)
	{
		running = false;
		for(int i = 1; i < st.size(); )
		{
			if (!((i-3 >= 0 && match(i-3, i)) || (i-1 >= 0 && match(i-1, i))))
			{
				i++;
				continue;
			}
			running = true;
			if(i-3 >= 0 && match(i-3, i))
			{
				if (move(i-3, i))
					st.erase(st.begin()+i);
				break;
			}
			if(i-1 >= 0 && match(i-1, i))
			{
				if (move(i-1, i))
					st.erase(st.begin()+i);
				break;
			}
		}
	}
       
	l = st.size();
	cout<<l<<(l > 1 ? " piles " : " pile ")<<"remaining:";
	for(int i = 0; i < l; i++)
	{
		cout<<" "<<st[i].size();
	}
	cout<<endl;
}

int main()
{
	string s;
	unsigned short us;
	cin>>s;
	while(s[0] != '#')
	{
		st.clear();
		st.resize(52);
		for(int i = 0; i < 52; i++)
		{
			st[i].push(s);
			cin>>s;
		}
		accordian();
	}
}