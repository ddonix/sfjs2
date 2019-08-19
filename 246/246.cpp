/* uva 246:10-20-30
 * 思路：这题关键是理解题意，英语学好吧。消失的牌要放回牌底去再发。
 *       draw就是循环了。
 */
#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

vector<vector<int> > pile;
queue<int> deck;
set<int> se;

bool deal(int p)
{
	vector<int> & pp = pile[p];
	int l;
	while(1)
	{
		l = pp.size();
		if (l < 3) break;
		if (se.count(pp[0]+pp[1]+pp[l-1]))
		{
			deak.push(pp[0]);
			deak.push(pp[1]);
			deak.push(pp[-1]);
			pp.erase();
			continue;
		}
		if (se.count(pp[0]+pp[l-2]+pp[l-1]))
		{
			continue;
		}
		if (se.count(pp[l-3]+pp[l-2]+pp[l-1]))
		{
			continue;
		}
		break;
	}
	if(pp.empty())
}

int main()
{
	int c,p,i,t;
	se.insert(10);
	se.insert(20);
	se.insert(30);
	cin>>c;
	while(c != 0)
	{
		pile.clear();
		pile.resize(7);
		for(i = 0; i < 7; i++)
		{
			pile[i].push_back(c);
			cin>>c;
		}
		while(!deck.empty()) deck.pop();
		for(; i < 52; i++)
		{
			deck.push(c);
			cin>>c;
		}
		p = 0;
		t = 7;
		while(!deck.empty())
		{
			t++;
			if (pile.empty())
			{
				cout<<"Win: "<<t<<endl;
				break;
			}
			else
			{
				pile[p].push_back(c);
				cin>>c;
				if (deal(p))
				{
					pile.erase(pile.begin()+p);
					if (p == pile.size()) p = 0;
				}
				else
				{
					p = (p+1)%pile.size();
				}
			}
		}
		cout<<"Los: "<<t<<endl;
	}
}
