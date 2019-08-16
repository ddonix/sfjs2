/*uva 536:Tree Recovery
 * 题意：由二叉树的先序和中序序列，求出后序序列。
 * 思路：先序最先出现根，中序根在中间，左边是左子树右边是右子树
 *       可用递归。这题不需要构造出二叉树，在递归的时候就求出后序序列。
 *       先跟，后右子树，再左子树。最后结果反着来就是。
 *
 */
#include <iostream>
#include <string>

using namespace std;

string sw(string p, string d)
{
	string res;
	int len = p.size();
	if(len <= 1)
		res = p;
	else
	{
		string pl, pr, dl, dr;
		string rl, rr;
		int i;
		char r = p[0];
		for(i = 0; d[i] != r; i++);
		if(i == 0)
		{
			dl = "";
			dr = d.substr(1);
			pl = "";
			pr = p.substr(1);
		}
		else if(i == len-1)
		{
			dl = d.substr(0);
			dr = "";
			pl = p.substr(1);
			pr = "";
		}
		else
		{
			dl = d.substr(0, i);
			dr = d.substr(i+1);
			int k;
			for(k = 1; string::npos == dr.find(p[k]); k++);
			pl = p.substr(1, k-1);
			pr = p.substr(k);
		}
		res += r;
		res += sw(pr, dr);
		res += sw(pl, dl);
	}
	return res;
}

int main()
{
	string p, d;
	string res;
	while(cin>>p)
	{
		cin>>d;
		res = sw(p, d);
		for(int i = res.size()-1; i>= 0; i--)
			cout<<res[i];
		cout<<endl;
	}
}
