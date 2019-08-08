#include <iostream>
#include <queue>
#include <string>
#include <sstream>
#include <vector>

using namespace std;


struct Program
{
	queue<Statement> s;
	int time;
	int state;	//0: running; 1:ready; 2:block; 3:over
};

struct Statement
{
	int type;
	int v;
	int value;
	Statement(int type) : type(t){}
	Statement(int type, int v1, int value1) : type(t), v(v1), value(value1) {}
};

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int quantum;
		int itime[5];

		int variable[26];
		int lock;
		int cpid;
		int np;
		char ch;
		
		cin>>np;
		for(int i = 0; i < 5; i++)
			cin>>itime[i];
		cin>>quantum;
		
		vector<Program> program;
		deque<int> ready;
		queue<int> block;
		
		program.resize(np);
		for(int i = 0; i < 26; i++)
			variable[i] = 0;
		lock = -1;
		
		for(int i = 0; i < np; i++)
		{
			int type;
			int v;
			int value;
			string t;
			
			program[i].state = 1;
			do
			{
				cin>>s;
				switch(s[2])
				{
				case '=':
					type = 0;
					cin>>t;
					v = t[0]-'a';
					cin>>t>>value;
					break;

				case 'i':
					type = 1;
					cin>>t;
					v = t[0]-'a';
					break;
				
				case 'c':
					type = 2;
					break;
				
				case 'l':
					type = 3;
					break;
				
				default:
					type = 4;
					break;
				}
				program[i].s.push(Statement(type, v, value));


			}
			string s;
			do
			{
				getline(cin, s);
				program[i].statement.push(s);
			}while(s[2] != 'd');
			ready.push_back(i);
		}

		cpid = -1;
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
				int stype = getstype(s);
				bool ssucc = true;
				if (itime[stype] <= p.time)
				{
					if (0 == stype)
					{
						stringstream ss(s.substr(3));
						ss>>variable[s[0]-'a'];
					}
					else if(1 == stype)
					{
						cout<<cpid+1<<": "<<variable[s[6]-'a']<<endl;
					}
					else if(4 == stype)
					{
						p.state = 3;
					}
					else if(2 == stype)
					{
						if(lock < 0)
						{
							lock = cpid;
						}
						else
						{
							p.state = 2;
							ssucc = false;
							block.push(cpid);
						}
					}
					else
					{
						lock = -1;
						if(!block.empty())
						{
							ready.push_front(block.front());
							block.pop();
						}
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
		cout<<endl;
	}
}
