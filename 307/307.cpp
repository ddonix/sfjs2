/* uva 307: Sticks
 * 	题意：一些长度相同的棍子，被随意砍成n份，每一份的长度都不超过50.
 * 	      要求根据砍断之后的n份小棍子，还原原先棍子可能长度的最小值。
 * 	分析：乍一看水题，仔细分析难题！一根棍子可以被砍成很多段，多跟棍子还原的次数就难以计算了。
 * 	      那么，换一个思路，如果把问题换成，一根棍子最多砍成多少
 * 	思路：ida
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> stick;
int n;
int main()
{
	while(cin>>n && n)
	{
		stick.resize(n);
		for(int i = 0; i < n; i++)
			cin>>stick[i];
	}
}


