/*
 * UVa  10763 - Foreign Exchange
 * Time   :  0.132s(UVa)
 * Author :  D_Double
 *
 */
 
#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>
#define MAXN 500005
using namespace std;
int arr[MAXN];
 
void swap(int a,int b){
	int t=arr[a]; arr[a] = arr[b]; arr[b] = t;
}
 
void init(){
	for(int i=0; i<MAXN; ++i)
		arr[i] = i;
}
 
bool isOk(){
	for(int i=0; i<MAXN; ++i)
		if(arr[i]!=i) return false;
	return true;
}
 
int main(){
	int n, i, a, b;
	while(scanf("%d",&n), n){
		init();
		for(int i=0; i<n; ++i){
			scanf("%d %d", &a, &b);
			swap(a, b);
		}
		if(isOk()) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
