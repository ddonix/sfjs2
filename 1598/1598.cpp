#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

struct Order
{
	//Order() {};
	Order(int i, int s, int p,int t) : id(i), size(s), price(p) {}
	
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
	return a.price < b.price;
}

bool cmps(const Order & a, const Order b)
{
	return a.price > b.price;
}

int main()
{
	int n;
	while(cin>>n)
	{
		vector<Order>  vb;
		vector<Order>  vs;
		set<int> sb;
		set<int> ss;

		int bids=0, bidp=0, asks=0, askp=9999;
		string o;
		int s, p, t;
		
		for(int i = 1; i <= n; i++)
		{
			cin>>o;
			if(o == "CANCEL")
			{	
				cin>>t;
				if(sb.count(t))
				{
					auto it = find_if(vb.begin(), vb.end(), find_by_id(t));
					if((it != vb.end()) && ((*it).price == bidp))
					{
						if ((*it).size > bids)
							bids -= (*it).size;
						else
						{
						
						}
					}

					/*
					if (o.price == bp)
					{
						if (vo[t].size > bs)
						{
							bs -= vo[t].size;
						}
						else
						{
							auto it = max_element(vo.begin(), vo.end(), cmpb);
							bs = (*it).size;
							bp = (*it).price;
						}
					}*/
				}
				else
				{
					/*if(vo[t].price == ap)
					{
						if (vo[t].size > as)
							as -= vo[t].size;
						else
						{
							auto it = max_element(vo.begin(), vo.end(), cmps);
							as = (*it).size;
							ap = (*it).price;
						}
					}*/
				}
				cout<<"QUOTO "<<bids<<" "<<bidp<<" - "<<asks<<" "<<askp<<endl;
			}
			else
			{
				cin>>s>>p;/*
				bool trade = false;
				if(o == "BUY")
				{
					vo[i] = Order(s, p, 0);
					if (p == bp)
						bs += s;
					else if(p > bp)
					{
						bp = p;
						bs = s;

						if (bp >= ap)
						{
							int ts;
							trade = true;
							if (bs == as)
							{
								ts = as;
								v
							}
							cout<<"TRADE"<<ts<<" "<<ap<<endl;

						}
					}
					cout<<"QUOTO "<<bs<<" "<<bp<<" - "<<as<<" "<<ap<<endl;
				}
				else
				{
					vo[i] = Order(s, p, 1);
					if (p < ap)
					{
						as = s;
						ap = p;
					}
					cout<<"QUOTO "<<bs<<" "<<bp<<" - "<<as<<" "<<ap<<endl;
				}
				if (flag)
					cout<<"QUOTO "<<bs<<" "<<bp<<" - "<<as<<" "<<ap<<endl;
			*/
			}
		}
	}
}
