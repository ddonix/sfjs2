/* uva 246:10-20-30
 * 思路：这题关键是理解题意，英语学好吧。消失的牌要放回牌底去再发。
 *       draw就是循环了。
 */
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

vector<deque<int> > pile;	//所有牌堆，最多7个
deque<int> deck;		//手里的牌堆
int cp;				//当前要发牌的堆

bool isten(int x)
{
	return (10 == x) || (20 == x) || (30 == x);
}

bool deal(int p)
{
	deque<int> & pp = pile[p];
	const int op[3][3] = {{0,1,-1}, {0,-2,-1}, {-3, -2, -1}};
	int c[3], l, i;
	while(1)
	{
		l = pp.size();
		if (l < 3) break;
		for(i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
				c[j] = (op[i][j]>=0) ? pp[op[i][j]] : pp[l+op[i][j]];
			
			if (isten(c[0]+c[1]+c[2]))
			{
				deck.push_back(c[0]);
				deck.push_back(c[1]);
				deck.push_back(c[2]);
				for(int j = 0; j < 3; j++)
					if(op[i][j] >= 0)
						pp.pop_front();
					else
						pp.pop_back();
				break;
			}
		}
		if (3 == i) break;
	}
	return pp.empty();
}

struct Status
{
	int card[62];
	Status(){}
	
	Status(bool snap)
	{
		int i = 0;
		card[i++] = deck.size();
		card[i++] = pile.size();
		for(int j = 0; j < pile.size(); j++)
			card[i++] = pile[j].size();
		card[i++] = cp;
		while(i < 10) card[i++] = 0;
		for(int j = 0; j < card[0]; j++)
			card[i++] = deck[j];
		for(int j = 0; j < card[1]; j++)
			for(int k = 0; k < pile[j].size(); k++)
				card[i++] = pile[j][k];
	}
	
	bool operator==(const Status & b)
	{
		for(int i = 0; i < 62; i++)
			if (card[i] != b.card[i])
				return false;
		return true;
	}
};

int main()
{
	int c,i,t;
	bool loop;
	cin>>c;
	while(c != 0)
	{
		vector<Status> status;
		pile.clear();
		pile.resize(7);
		while(!deck.empty()) deck.pop_front();
		for(i = 0; i < 7; i++)
		{
			pile[i].push_back(c);
			cin>>c;
		}
		for(; i < 52; i++)
		{
			deck.push_back(c);
			cin>>c;
		}
		t = 7;
		cp = 0;
		loop = false;
		status.push_back(Status(true));
		while(!deck.empty() && !loop)
		{
			t++;
			pile[cp].push_back(deck.front());
			deck.pop_front();
			if (deal(cp))
			{
				pile.erase(pile.begin()+cp);
				if (cp == pile.size()) //原先是最后一个
				{
					if (pile.size() > 0)	//原先不只有一个
						cp = 0;
					else
						break;
				}
			}
			else
			{
				cp = (cp+1)%pile.size();
			}
			Status s(true);
			if (find(status.begin(), status.end(), s) != status.end())
			{
				loop = true;
				break;
			}
			status.push_back(s);
		}
		if (loop)
			cout<<"Draw: "<<t<<endl;
		else if (pile.empty())
			cout<<"Win : "<<t<<endl;
		else
			cout<<"Loss: "<<t<<endl;
	}
}
