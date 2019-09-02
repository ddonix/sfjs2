/* 当前指令能否执行，是看当前时间片是否大于0.而不是指令执行的时间是否大于时间片.
 * 可是看题目原意， instruction currently beingexecuted when the time quantum expires will be allowed to complete.
 */

#include <iostream>
#include <queue>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct Program
{
	queue<string> statement;
	int time;
	int state;	//0: running; 1:ready; 2:block; 3:over
};

int getstype(const string & s)
{
	if ('=' == s[2])
		return 0;
	else if('i' == s[2])
		return 1;
	else if('c' == s[2])
		return 2;
	else if('l' == s[2])
		return 3;
	return 4;
};

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int np;
		int itime[5];
		int quantum;

		cin>>np;
		for(int i = 0; i < 5; i++)
			cin>>itime[i];
		cin>>quantum;
		
		vector<Program> program;
		int cpid;
		deque<int> ready;
		queue<int> block;
		
		int variable[26];
		int lock;
		
		program.resize(np);
		
		cin.ignore(1024, '\n');
		for(int i = 0; i < np; i++)
		{
			int type;
			int v;
			int value;
			string s;
			
			do
			{
				getline(cin, s);
				//cout<<s<<endl;
				program[i].statement.push(s);
			}while(s[2] != 'd');
			program[i].state = 1;
			ready.push_back(i);
		}

		lock = -1;
		cpid = -1;
		for(int i = 0; i < 26; i++)
			variable[i] = 0;

		while(!ready.empty())
		{
			cpid = ready.front();
			ready.pop_front();
			Program & p = program[cpid];
			p.time = quantum;
			p.state = 0;
			while(1)
			{
				string s = p.statement.front();
				//cout<<T<<" "<<s<<endl;
				int stype = getstype(s);
				if (p.time > 0)
				{
					bool ssucc = true;
					if (0 == stype)
					{
						stringstream ss(s.substr(3));
						ss>>variable[s[0]-'a'];
					}
					else if(1 == stype)
					{
						cout<<cpid+1<<": "<<variable[s[6]-'a']<<endl;
					}
					else if(2 == stype)
					{
						if(lock < 0)
							lock = cpid;
						else
						{
							p.state = 2;
							ssucc = false;
							block.push(cpid);
						}
					}
					else if(3 == stype)
					{
						lock = -1;
						if(!block.empty())
						{
							ready.push_front(block.front());
							block.pop();
						}
					}
					else// 4 == stype
					{
						p.state = 3;
					}
					if(ssucc)
						p.statement.pop();
					
					if(0 == p.state)
					{
						p.time -= itime[stype];
						if(0 == p.time)
						{
							p.state = 1;
							ready.push_back(cpid);
							break;
						}
					}
					else
						break;
				}
				else
				{
					p.state = 1;
					ready.push_back(cpid);
					break;
				}
			}
		}
		if(T>=1)
			cout<<endl;
	}
}
