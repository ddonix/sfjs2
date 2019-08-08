#include <iostream>

using namespace std;

int *Left;
int *Right;

void link(int l, int r)
{
	Right[l] = r;
	Left[r] = l;
}

int main()
{
    int v1[100002], v2[100002];
    int n,m;
    int ka = 1;
    
    Left = v1; 
    Right = v2;
    while(cin>>n)
    {
        cin>>m;
        
        for(int i = 1; i <= n+1; i++)
            Left[i] = i-1;
        
        for(int i = 0; i <= n; i++)
            Right[i] = i+1;
        
        int c, x, y;
        for(int i = 0; i < m; i++)
        {
            cin>>c;
            if (c < 4)
                cin>>x>>y;
            if(1 == c)
            {
                if(x == Left[y])
                    continue;

		link(Left[x], Right[x]);
		link(Left[y], x);
		link(x, y);
            }
            else if (2 == c)
            {
                if (x == Right[y])
                    continue;

                link(Left[x], Right[x]);
		link(x, Right[y]);
		link(y, x);
            }
            else if (3 == c)
            {
                if(x == Left[y])
                {
            	    link(Left[x], y);
		    link(  
            
                    Right[x] = Right[y];
                    Left[y] = Left[x];
            
                    Left[x] = y;
                    Right[y] = x;

                }
                else if(Left[x] == y)
                {
                    Right[Left[y]] = x;
                    Left[Right[x]] = y;

                    Right[y] = Right[x];
                    Left[x] = Left[y];

                    Right[x] = y;
                    Left[y] = x;
                }
                else
                {
                    Right[Left[x]] = y;
                    Left[Right[x]] = y;

                    Right[Left[y]] = x;
                    Left[Right[y]] = x;

                    int t1,t2;
                    t1 = Left[x];
                    t2 = Right[x];

                    Left[x] = Left[y];
                    Right[x] = Right[y];

                    Left[y] = t1;
                    Right[y] = t2;
                }
            }
            else
            {
                int * t = Right;
                Right = Left;
                Left = t;
            }
        }
        
        int t = Right[0];
	while(t <= n && t > 0)
        {
            cout<<t<<endl;
            t= Right[t];
        }
        cout<<"Case "<<ka++<<": "<<0<<endl;
    }
}

