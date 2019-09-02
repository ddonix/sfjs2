#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <vector>

using namespace std;

void analise_name(string s, string & user, string & mta)
{
	int i;
	i = s.find('@');
	user = s.substr(0, i);
	mta = s.substr(i+1);
}

int main()
{
	map<string, set<string>> mta;
	string s,s1;

	while(cin>>s && "*" != s)
	{
		int n;
		cin>>s>>n;
		mta[s] = set<string>();
		while(n--)
		{
			cin>>s1;
			mta[s].insert(s1);
		}
	}

	while(cin>>s && "*" != s)
	{
		string suser, smta;
		string ruser, rmta;
		map<string, vector<string>> recv;
		map<string, set<string>> recv1;
		queue<string> que;
		
		analise_name(s, suser, smta);
		while(cin>>s1 && "*" != s1)
		{
			analise_name(s1, ruser, rmta);
			if(recv.count(rmta) < 1)
			{
			       	recv[rmta] = vector<string>();
				recv[rmta].push_back(ruser);
				
				recv1[rmta] = set<string>();
				recv1[rmta].insert(ruser);

				que.push(rmta);
			}
			else
			{
				if(recv1[rmta].count(ruser) < 1)
				{
					recv[rmta].push_back(ruser);
					recv1[rmta].insert(ruser);
				}
			}
		}
		getline(cin, s1);
		string data = "";
		while(getline(cin, s1) && "*" != s1)
		{
			data += "     " + s1 + '\n';
		}
		while(!que.empty())
		{
			bool dflag = false;
			rmta = que.front();
			que.pop();
			cout<<"Connection between "<<smta<<" and "<<rmta<<endl;
			cout<<"     HELO "<<smta<<endl;
			cout<<"     250"<<endl;
			cout<<"     MAIL FROM:<"<<s<<">"<<endl;
			cout<<"     250"<<endl;
			for(int i = 0; i < recv[rmta].size(); i++)
			{
				ruser = recv[rmta][i];
				cout<<"     RCPT TO:<"<<ruser<<"@"<<rmta<<">"<<endl;
				if (mta[rmta].count(ruser) < 1)
				{
					cout<<"     550"<<endl;
				}
				else
				{
					cout<<"     250"<<endl;
					dflag = true;
				}
			}
			if (dflag)
			{
				cout<<"     DATA"<<endl;
				cout<<"     354"<<endl;
				cout<<data;
				cout<<"     ."<<endl;
				cout<<"     250"<<endl;
			}
			cout<<"     QUIT"<<endl;
			cout<<"     221"<<endl;
		}
	}
}
