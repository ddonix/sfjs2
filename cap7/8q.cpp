#include <iostream>
#include <cstring>

using namespace std;

const int maxn = 10;
int n;

bool vis[3][maxn * 2];

int C[maxn];
int tot = 0;
void search(int cur)
{
	if (cur == n) {
		   for(int i = 0; i < n; i++)
		   {
		   	for(int j = 0; j < C[i]; j++)
		   		cout<<'.';
		   	cout<<'*';
		   	for(int j = C[i]+1; j < n; j++)
		   		cout<<'.';
		   	cout<<endl;
		   }
		   cout<<endl<<endl; 
		tot++;
	} else {
		for (int i = 0; i < n; i++) {
			if (!vis[0][i] && !vis[1][cur+i] && !vis[2][cur-i+n]) {
				C[cur] = i;
				vis[0][i] = vis[1][cur+i] = vis[2][cur-i+n] = true;
				search(cur+1);
				vis[0][i] = vis[1][cur+i] = vis[2][cur-i+n] = false;
			}

		}
	}
}

int main()
{
	while (cin >> n && n) {
		memset(vis, 0, sizeof(vis));
		tot = 0;
		search(0);
		cout << n << " queun question: " << tot << " answer" <<
		    endl;
	}

}
