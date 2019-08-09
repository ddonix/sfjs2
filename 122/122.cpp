#include <iostream>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

struct Node
{
	Node() : value(0), l(0), r(0) {}
	Node(int v) : value(v), l(0), r(0) {}
	int value;
	Node *l;
	Node *r;
};

bool complete;
void insert(Node* r, int v, string s)
{
	Node * p = r;
	for(int i = 0; i < s.length(); i++)
	{
		if ('L' == s[i])
		{
			if (!(p->l))
				p->l = new Node();
			p = p->l;
		}
		else
		{
			if (!(p->r))
				p->r = new Node();
			p = p->r;
		}
	}
	if(p->value)
		complete = false;
	else
		p->value = v;
}

bool iscomplete(Node *r)
{
	if (!complete)
		return false;
	if (0 == r)
		return true;
	else if (0 == r->value)
		return false;
	bool res = iscomplete(r->l);
	if (res)
		return iscomplete(r->r);
	return false;

}

void tt(Node *r, queue<int> & res)
{
	queue<Node *> q;
	q.push(r);
	while(!q.empty())
	{
		Node * p = q.front();
		q.pop();
		res.push(p->value);
		if (p->l)
			q.push(p->l);
		if (p->r)
			q.push(p->r);
	}
}

int main()
{
	Node root;
	string s;
	while(cin>>s)
	{
		root.value = 0;
		root.l = root.r = 0;
		complete = true;
		while(1)
		{
			string::size_type p = s.find(",");
			stringstream ss(s.substr(1, p-1));
			int v;
			ss>>v;
			
			if(complete)
				insert(&root, v, s.substr(p+1, s.length()-p-2));
			cin>>s;
			if("()" == s)
				break;
		}
		if (!iscomplete(&root))
			cout<<"not complete"<<endl;
		else
		{
			queue<int> q;
			tt(&root, q);
			cout<<q.front();
			q.pop();
			while(!q.empty())
			{
				cout<<" "<<q.front();
				q.pop();
			}
			cout<<endl;
		}
	}	
}
