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
	for(int i = 0; i < len-1; i++)
		for(int j = i+1; j < len; j++)
			if (j-i <= (len-j))
				if(!strncmp(&seq[i], &seq[j], (j-i)))
					return false;
	return true;
}

int main()
{	
	int t;
//	strcpy(seq, "ABACABCACBABCABACABCACBACABA");
	strcpy(seq, "ABACABADABACABCACBABCABACABCA");
	cout<<ishard(strlen(seq))<<endl;
}

