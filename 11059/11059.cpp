#include <iostream>
using namespace std;

int main()
{
	int N;
	int ka = 0;
	while(cin>>N)
	{
		long long seq[18];
		for(int i = 0; i < N; i++)
			cin>>seq[i];
		int b, e;
		long long res;
		res = 0;
		for(b = 0; b < N; b++)
			for(e = b+1; e <= N; e++)
			{
				long long r = 1;
				for(int i = b; i < e; i++)
					r *= seq[i];
				if (r < 0)
					continue;
				res = (res > r) ? res : r;
			}
		cout<<"Case #"<<++ka<<": The maximum product is "<<res<<"."<<endl<<endl;
	}
}
