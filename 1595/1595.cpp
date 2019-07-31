#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,i;
		int min, max, middle;
		int x,y;
		vector<int> v;
		cin>>n;

		v.resize(n);
		
		min = 20002;
		max = 0;
		for(i = 0; i < n; i++)
		{
			cin>>x>>y;
			x += 10001;
			y += 10001;
			
			if (x > max)
				max = x;
			if (x < min)
				min = x;
			v[i] = ((unsigned int)x |((unsigned int)y << 16));
		}
		bool flag;

		middle = min+max;
		flag = true;
		
		for(i = 0; i < n; i++)
		{
			unsigned int t = v[i];
			if (0 == t)
				continue;
			
			unsigned int l = t & 0x0000ffff;
			if (l+l == middle)
				continue;
			
			unsigned int t1 = ((unsigned int)(middle-l) | (t & 0xffff0000)); 
			int j;
			for(j = i+1; j < n; j++)
			{
				if(v[j] == t1)
				{
					v[j] = 0;
					break;
				}
			}
			if (j == n)
			{
				flag = false;
				break;
			}
		}
		if (flag)
			cout<<"YES"<<endl;
		else
			cout<<"NO"<<endl;
	}
}
