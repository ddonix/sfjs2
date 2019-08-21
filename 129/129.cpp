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
		cur = strlen(seq);
		for (int j = 0; j < 4 && j < cur; j++)
			cout << seq[j];
		int i;
		for (i = 1; i < (cur - 1) / 4; i++) {
			cout << " ";
			for (int j = 0; j < 4; j++)
				cout << seq[i * 4 + j];
		}
		if (i * 4 < cur) {
			cout << " ";
			for (int j = 0; i * 4 + j < cur; j++)
				cout << seq[i * 4 + j];
		}
		cout << endl<< cur<< endl;
		return;
	}
	if (tot >= n)
		return;
	for (char c = 'A'; c <= l; c++) {
		seq[cur] = c;
		if (ishard(cur+1))
			hardseq(cur+1);
	}
}

int main()
{
	int t;
	strcpy(seq, "ABACABCACBABCABACABCACBACABA");
	for(int i = 0; i < strlen(seq)-1; i++)
		cout<<ishard(strlen(seq)-i)<<endl;
	/*
	while (cin >> n >> t && n) {
		tot = -1;
		l = 'A' + t;
		hardseq(0);
	}*/
}
