#include <iostream>
#include <stack>
#include <queue>

using namespace std;

int main()
{
	int n;
	while(cin>>n && n)
	{
		int t;
		while(cin>>t && t)
		{
			queue<int> A;
			queue<int> B;
			stack<int> C;

			B.push(t);
			A.push(1);
			for(int i = 2; i <= n; i++)
			{
				cin>>t;
				B.push(t);
				A.push(i);
			}
			bool ok = true;
			while(!B.empty() && ok)
			{
				int a, b, c;
				b = B.front();
				B.pop();
				
				while(C.empty() || C.top() != b)
				{
					if(A.empty())
						break;
					C.push(A.front());
					A.pop();
				}
				if(C.top() != b)
					ok = false;
				else
					C.pop();
			}
			cout<<(ok ? "Yes" : "No")<<endl;
		}
		cout<<endl;
	}
}
