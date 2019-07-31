#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
	int n,maxw, col,row;
	vector<string> sa;
	string s;
	while(cin>>n)
	{
		sa.resize(n);
		maxw = 0;
		for(int i=0; i < n; i++) 
		{
			cin>>sa[i];
			if(sa[i].length() > maxw)
				maxw = sa[i].length();
		}
		col = 62/(maxw+2);
		row = n/col;
		if (n%col)
			row++;
		
		sort(sa.begin(), sa.end());
		for(int i=0; i<60; i++)	cout<<'-';
		cout<<endl;
		for(int i=0; i < row; i++)
		{
			for(int j = 0; j < col; j++)
			{
				if(!(j*row+i < n))
					continue;
				cout<<sa[j*row+i];
				
				if(j == (col-1))
					continue;
				for(int k = 0; k < maxw+2-sa[j*row+i].length(); k++) cout<<' ';
			}
			cout<<endl;
		}
	}
}
