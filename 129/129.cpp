#include <iostream>
#include <cstring>
using namespace std;

const int maxl = 26;
const int maxseq = 81;

int n;
char l;
int tot;

char seq[maxseq];

bool ishard(int len)
{
	int i;
	for (i = 1; i <= len/2; i++) {
		char *s1 = &seq[len-i];
		char *s2 = &seq[len-2*i];
		if (!strncmp(s1, s2, i))
			break;
	}
	return i > len/2;
}

void hardseq(int cur)
{
	tot++;
	if (tot == n) {
		int p = 1;
		for(int i = 0; i < cur; i++)
		{
			if (p != 1 && p%80 == 0)
			{
				cout<<endl;
				p++;
			}
			else if (p%5 == 0)
			{
				cout<<" ";
				p++;
			}
			cout<<seq[i];
			p++;
		}
		cout << endl<< cur<< endl;
	}
	if (tot >= n)
		return;
	for (char c = 'A'; c < l; c++) {
		seq[cur] = c;
		if (ishard(cur+1))
			hardseq(cur+1);
	}
}

int main()
{
	int t;
	//strcpy(seq, "ABACABCACBABCABACABCACBACABA");
	//for(int i = 0; i < strlen(seq)-1; i++)
	//	cout<<ishard(strlen(seq)-i)<<endl;
	
	while (cin >> n >> t && n) {
		tot = -1;
		l = 'A' + t;
		hardseq(0);
	}
}
