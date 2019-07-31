#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int main(int argc, char **argv)
{
        int n;
        char buff[81];
        int l,state;
        int r;

        scanf("%d", &n);
        for (int i = 0; i < n; i++)
        {
                scanf("%s", buff);
                l = strlen(buff);
                r = 0;
                state = 0;
                for(int j = 0; j < l; j++)
                {
                        if(buff[j] == 'O')
                        {
                                state += 1;
                                r += state;
                        }
                        else
                        {
                                state = 0;
                        }
                }
                printf("%d\n", r);
        }
}
