#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
 
using namespace std;
 
/* Trie define */  
#define nodesize 4000004      //节点个数   
#define dictsize 10           //字符集大小   
  
typedef struct node1  
{
	int    id;
    int    flag;            //值域   
    node1* next[dictsize];  
}tnode;  
tnode  dict[nodesize];  
int    ID[256];
  
class Trie  
{  
    private:
        int    size;  
        tnode* root;  
    public:  
        Trie() {makeID(); initial();}  
        void makeID() {  
            for ( int i = 0 ; i < 10 ; ++ i )  
                ID['0'+i] = i;
        }  
        void initial() {  
            memset( dict, 0, sizeof( dict ) );  
            root=NULL; size=0; root=newnode();  
        }  
        tnode* newnode() {return &dict[size ++];}  
        void insert( char* word, int L, int id ) {  
            tnode* now = root;  
            for ( int i = 0 ; i < L ; ++ i ) {
                if ( !now->next[ID[word[i]]] )  
                    now->next[ID[word[i]]] = newnode();  
                /* 标记路径 */
                if ( !now->id && !now->flag ) now->id = id;
                now = now->next[ID[word[i]]];  
            }
			if ( !now->flag ) {
				now->flag = 1;
				now->id = id;
			}
        }
        int query( char* word ) {
            tnode* now = root;  
            for ( int i = 0 ; word[i] ; ++ i ) {
                if ( !now->next[ID[word[i]]] ) return -1;  
                now = now->next[ID[word[i]]];  
            }
			return now->id;
        }
}trie;  
/* Trie  end */  
 
int  F[2][21000];
char FF[42],In[42];
 
int main()
{
	/* 大整数计算Fib前100000个数字 */
	memset( F, 0, sizeof(F) );
	F[0][0] = F[1][0] = 1;
	trie.insert( "1", 1, 0 );
	int s = 0,l = 1,r,count,p,q;
	for ( int i = 2 ; i < 100000 ; ++ i ) {
		p = i%2, q = (i+1)%2;
		for ( int j = s ; j < l ; ++ j )
			F[p][j] = F[p][j] + F[q][j];
		for ( int j = s ; j < l ; ++ j )
			if ( F[p][j] >= 10 ) {
				F[p][j+1] += 1;
				F[p][j]   -= 10;
			}
		if ( F[p][l] ) l ++;
		if ( l - s > 50 ) s ++;
		r = l-1;  count = 0;
		while ( r >= 0 && count < 40 ) 
			FF[count ++] = F[p][r --] + '0';
 
		if (i == 11987)
			cout<<FF<<endl;
		trie.insert( FF, count, i );
	}
	int T;
	while ( scanf("%d",&T) != EOF ) 
	for ( int t = 1 ; t <= T ; ++ t ) {
		scanf("%s",In);
		printf("Case #%d: %d\n",t,trie.query( In ));
	}
	return 0;
}
