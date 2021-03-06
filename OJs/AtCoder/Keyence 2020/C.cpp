#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;

ll n,k,s;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}



int main()
{
	readx(n); readx(k); readx(s);
	
	for (int i=1;i<=k;i++) 
		printf("%lld ",s);
	if (s==1000000000) 
	{
		for (int i=k+1;i<=n;i++)
			printf("1 ");
	}
	else
	{
		for (int i=k+1;i<=n;i++)
			printf("1000000000 ");
	}
	printf("\n");
	return 0;
}
