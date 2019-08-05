#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

struct Order
{
	//Order() {};
	Order(int i, int s, int p) : id(i), size(s), price(p) {}
	
	int id;
	int size;
	int price;
};

struct find_by_id
{
	find_by_id(int i) : id(i) {};
	bool operator()(const Order &a)
	{
		return id == a.id;
	}
	int id;
};

bool cmpb(const Order & a, const Order b)
{
	if (a.price != b.price)
		return a.price < b.price;
	return (a.id > b.id);
}

bool cmps(const Order & a, const Order b)
{
	if (a.price != b.price)
		return a.price > b.price;
	return (a.id > b.id);
}

vector<Order>  vb;
vector<Order>  vs;
set<int> sb;
set<int> ss;

int bids, bidp;
int asks, askp;

void updatebid(bool era)
{
	if (vb.empty())
	{
		bids = 0;
		bidp = 0;
	}
	else
	{
		make_heap(vb.begin(), vb.end(), cmpb);
		auto it = vb.begin();
		bidp = (*it).price;
		bids = (*it).size;
		if(era)
		{
			for(it = vb.begin()+1; it != vb.end(); it++)
				if ((*it).price == bidp)
					bids += (*it).size;
		}
	}
}

void updateask(int era)
{
	if (vs.empty())
	{
		asks = 0;
		askp = 99999;
	}
	else
	{
		make_heap(vs.begin(), vs.end(), cmps);
		auto it = vs.begin();
		askp = (*it).price;
		asks = (*it).size;
		if (era)
		{
			for(it = vs.begin()+1; it != vs.end(); it++)
				if ((*it).price == askp)
					asks += (*it).size;
		}
	}
}

int main()
{
	int n;
	bool first = true;
	while(cin>>n)
	{
		vs.clear();
		vb.clear();
		ss.clear();	
		sb.clear();
		bids = bidp = asks=0;
		askp=99999;
		for(int id = 1; id <= n; id++)
		{
			int s, p;
			string o;
			cin>>o;
			if(o == "CANCEL")
			{
				int t;
				cin>>t;
				if (sb.count(t))
				{
					auto it = find_if(vb.begin(), vb.end(), find_by_id(t));
					if (it != vb.end())
					{
						int s1 = (*it).size;
						int p1 = (*it).price;
						vb.erase(it);
						
						if (p1  == bidp)
						{
							if (s1 > bids)
								bids -= s1;
							else
								updatebid(true);
						}
					}
				}
				else
				{
					auto it = find_if(vs.begin(), vs.end(), find_by_id(t));
					if (it != vs.end())
					{
						int s1 = (*it).size;
						int p1 = (*it).price;
						vs.erase(it);
						
						if (p1  == askp)
						{
							if (s1 > asks)
								asks -= s1;
							else
								updateask(true);
						}
					}
				}
			}
			else
			{
				cin>>s>>p;
				if(o == "BUY")
				{
					vb.push_back(Order(id, s, p));
					sb.insert(id);
					if (p == bidp)
						bids += s;
					else if(p > bidp)
						updatebid(false);
				}
				else
				{
					vs.push_back(Order(id, s, p));
					ss.insert(id);
					if (p == askp)
						asks += s;
					else if(p < askp)
						updateask(false);
				}
				while (bidp >= askp && (asks != 0))
				{
					int size = (bids > asks) ? asks : bids;
					while(size)
					{
						int s2;
						auto itb = vb.begin();
						auto its = vs.begin();
						bool bidupdate = false, askupdate = false;
						s2 = ((*itb).size < (*its).size) ? (*itb).size : (*its).size;
						s2 = (s2 > size) ? size : s2;
						if ((*itb).size == s2)
						{
							vb.erase(itb);
						}
						else
							(*itb).size -= s2;

						if ((*its).size == s2)
						{
							vs.erase(its );
						}
						else
							(*its).size -= s2;
						size -= s2;
						cout<<"TRADE "<<s2<<" "<<(o == "BUY" ? askp : bidp)<<endl;
						updatebid(true);
						updateask(true);
					}
				}
			}
			//cout<<"ID:"<<id<<"QUOTE "<<bids<<" "<<bidp<<" - "<<asks<<" "<<askp<<endl;
			cout<<"QUOTE "<<bids<<" "<<bidp<<" - "<<asks<<" "<<askp<<endl;
		}
		cout<<endl;
	}
}
