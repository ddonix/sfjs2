#include <iostream>

using namespace std;

int v1[100002], v2[100002];
int *Left;
int *Right;
int n,m;

void link(int l, int r)
{
	Right[l] = r;
	Left[r] = l;
}

void link(int l, int m, int r)
{
	Left[m] = l;
	Right[m] = r;

	Right[l] = m;
	Left[r] = m;
}

unsigned long count()
{
	unsigned long res = 0;
	int t;
	if (Right == v2)
        	t = v2[0];
	else
        	t = v1[n+1];
	while(t <= n && t > 0)
        {
        	res += t;
            	t = Right[t];
		if (t <= n && t > 0)
			t = Right[t];
		else
			break;
	}
	return res;
}

void print()
{
	if (Right[0] > 0)
	{
        	int t = Right[0];
		while(t <= n)
        	{
            		cout<<t<<" ";
            		t = Right[t];
        	}
	}
	else 
	{
        	int t = Right[n+1];
		while(t > 0)
        	{
            		cout<<t<<" ";
            		t = Right[t];
        	}
	}
	cout<<endl;
}

int main()
{
    int ka = 1;
    
    while(cin>>n)
    {
        cin>>m;
        

    	Left = v1; 
    	Right = v2;
        for(int i = 1; i <= n+1; i++)
            v1[i] = i-1;
	v1[0] = -1;
        
        for(int i = 0; i <= n; i++)
            v2[i] = i+1;
	v2[n+1] = -1;
        
	int c, x, y;
        for(int i = 0; i < m; i++)
        {
            cin>>c;
            if (c < 4)
                cin>>x>>y;
            if(1 == c)
            {
                //cout<<"1: "<<x<<" "<<y<<endl;
		if(x == Left[y])
                    continue;

		link(Left[x], Right[x]);
		link(Left[y], x);
		link(x, y);
            }
            else if (2 == c)
            {
                //cout<<"2: "<<x<<" "<<y<<endl;
                if (x == Right[y])
                    continue;

                link(Left[x], Right[x]);
		link(x, Right[y]);
		link(y, x);
            }
            else if (3 == c)
            {
                //cout<<"3: "<<x<<" "<<y<<endl;
                if(x == Left[y])
                {
            	    link(Left[x], y);
		    link(x, Right[y]);
		    link(y,x);
                }
                else if(x == Right[y])
                {
                	link(Left[y], x);
			link(y, Right[x]);
			link(x, y);
		}
                else
                {
                	int yl = Left[y];
			int yr = Right[y];
			link(Left[x], y, Right[x]);
			link(yl, x, yr);
		}
            }
            else
            {
                //cout<<"h_t"<<endl;
                int * t = Right;
                Right = Left;
                Left = t;
            }
	    //print();
        }
        cout<<"Case "<<ka++<<": "<<count()<<endl;
    }
}

