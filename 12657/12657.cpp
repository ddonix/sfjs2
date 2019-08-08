#include <iostream>

using namespace std;
int main()
{
    int v1[100002], v2[100002];
    int *left = v1, *right = v2;
    int n,m;
    int ka = 1;
    int ll, rr;
    
    while(cin>>n)
    {
        cin>>m;
        ll = 1;
        rr = n;
        
        for(int i = 1; i < n; i++)
            left[i] = i-1;
        
        for(int i = 0; i <= n; i++)
            right[i] = i+1;
        
        int c, x, y;
        for(int i = 0; i < m; i++)
        {
            cin>>c;
            if (c < 4)
                cin>>x>>y;
            if(1 == c)
            {
                if(x == left[y])
                    continue;

                if (left[y] == 0)
                    ll = x;
                
                right[left[x]] = right[x];
                left[right[x]] = left[x];
                
                right[x] = y;
                left[x] = left[y];
                
                right[left[y]] = x;
                left[y] = x;

            }
            else if (2 == c)
            {
                if (x == right[y])
                    continue;

                if (right[y] == n+1)
                    rr = x;
                
                right[left[x]] = right[x];
                left[right[x]] = left[x];
                
                left[x] = y;
                right[x] = right[y];

                left[right[y]] = x;
                right[y] = x;
            }
            else if (3 == c)
            {
                if (ll == x)
                    ll = y;
                else if (ll == y)
                    ll = x;
                if (rr == y)
                    rr = x;
                else if(rr == x)
                    rr = y;
                if(right[x] == y)
                {
                    
                    right[left[x]] = y;
                    left[right[y]] = x;
            
                    right[x] = right[y];
                    left[y] = left[x];
            
                    left[x] = y;
                    right[y] = x;

                }
                else if(left[x] == y)
                {
                    right[left[y]] = x;
                    left[right[x]] = y;

                    right[y] = right[x];
                    left[x] = left[y];

                    right[x] = y;
                    left[y] = x;
                }
                else
                {
                    right[left[x]] = y;
                    left[right[x]] = y;

                    right[left[y]] = x;
                    left[right[y]] = x;

                    int t1,t2;
                    t1 = left[x];
                    t2 = right[x];

                    left[x] = left[y];
                    right[x] = right[y];

                    left[y] = t1;
                    right[y] = t2;
                }
            }
            else
            {
                int tt = ll;
                ll = rr;
                rr = tt;
                int * t = right;
                right = left;
                left = t;
            }
        }
        
        int t = ll;
        while(t <= n)
        {
            cout<<t<<endl;
            t= right[t];
        }
        cout<<"Case "<<ka++<<": "<<0<<endl;
    }
}

