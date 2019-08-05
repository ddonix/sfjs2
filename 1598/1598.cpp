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

//make_heap has been called.
void updatebid()
{
	auto it = vb.begin();
	if (it == vb.end())
	{
		bids = 0;
		bidp = 0;
	}
	else
	{
		bidp = (*it).price;
		bids = (*it).size;
		for(auto it = vb.begin()+1; it != vb.end(); it++)
		{
			if ((*it).price == bidp)
				bids += (*it).size;
		}
	}
}

void updateask()
{
	auto it = vs.begin();
	if (it == vs.end())
	{
		asks = 0;
		askp = 99999;
	}
	else
	{
		askp = (*it).price;
		asks = (*it).size;
		for(auto it = vs.begin()+1; it != vs.end(); it++)
		{
			if ((*it).price == askp)
				asks += (*it).size;
		}
	}
}

void updateba()
{
	updatebid();
	updateask();
}

int main()
{
	int n;
	bool first = true;
	while(cin>>n)
	{
		vb.clear();
		vs.clear();
		sb.clear();
		ss.clear();	
		bids = bidp = asks=0;
		askp=99999;
		if (!first)
			cout<<endl;
		else
			first = false;
		for(int id = 1; id <= n; id++)
		{
			bool flag = false;
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
					if (it != vb.end() )
					{
						int s1 = (*it).size;
						int p1 = (*it).price;
						vb.erase(it);
						make_heap(vb.begin(), vb.end(), cmpb);
						
						if (p1  == bidp)
						{
							if (s1 > bids)
								bids -= s1;
							else
								updatebid();
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
						make_heap(vs.begin(), vs.end(), cmps);
						
						if (p1  == askp)
						{
							if (s1 > asks)
								asks -= s1;
							else
								updateask();
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
					make_heap(vb.begin(), vb.end(), cmpb);
					sb.insert(id);
					if (p == bidp)
						bids += s;
					else if(p > bidp)
					{
						bids = s;
						bidp = p;
					}
				}
				else
				{
					vs.push_back(Order(id, s, p));
					make_heap(vs.begin(), vs.end(), cmps);
					ss.insert(id);
					if (p == askp)
						asks += s;
					else if(p < askp)
					{
						asks = s;
						askp = p;
					}
				}
				while (bidp >= askp && (asks != 0))
				{
					flag = true;
					int size = (bids > asks) ? asks : bids;
					int sss = 0;
					while(sss < size)
					{
						int s2;
						auto itb = vb.begin();
						auto its = vs.begin();
						s2 = ((*itb).size < (*its).size) ? (*itb).size : (*its).size;
						s2 = (s2 + sss > size) ? (size - sss) : s2;
						sss += s2;
						if (id == 223)
						{
						}
						if ((*itb).size == s2)
						{
							vb.erase(itb);
							make_heap(vb.begin(), vb.end(), cmpb);
						}
						else
							(*itb).size -= s2;

						if ((*its).size == s2)
						{
							vs.erase(its);
							make_heap(vs.begin(), vs.end(), cmps);
						}
						else
							(*its).size -= s2;
						cout<<"TRADE "<<s2<<" "<<(o == "BUY" ? askp : bidp)<<endl;
					}
					updateba();
				}
			}
			//cout<<"ID:"<<id<<"QUOTE "<<bids<<" "<<bidp<<" - "<<asks<<" "<<askp<<endl;
			cout<<"QUOTE "<<bids<<" "<<bidp<<" - "<<asks<<" "<<askp<<endl;
		}
	}
}
