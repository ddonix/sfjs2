#include <iostream>
#include <string>
#include <map>
#include <queue>

using namespace std;

const int maxn = 10000;

int Left[maxn];
int Right[maxn];
map<int, queue<int> > heap;

int minh;
int maxh;

bool gettree(int & rt, int h)
{
	bool bl, br;
	cin>>rt;
	if (-1 == rt)
		return false;
	int l, r;
	if(heap.count(h) < 1)
		heap[h] = queue<int>();
	heap[h].push(rt);
	maxh = (h > maxh) ? h : maxh;
	minh = (h < minh) ? h : minh;
	bl = gettree(l, h-1);
	br = gettree(r, h+1);
	if (bl)
		Left[rt] = l;
	if (br)
		Right[rt] = r;
	return true;
}

int main()
{
	int ka = 1;
	while(1)
	{
		bool over;
		int root;
		minh = 0;
		maxh = 0;
		heap.clear();
		
		over = gettree(root, 0);
		if (!over)
			break;
		cout<<"Case "<<ka++<<":"<<endl;
		for(int i = minh; i <= maxh; i++)
		{
			int sum = 0;
			while(!heap[i].empty())
			{
				sum += heap[i].front();
				heap[i].pop();
			}
			cout<<sum;
			if (i < maxh)
				cout<<' ';
		}
		cout<<endl<<endl;
	}
}
