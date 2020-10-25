#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
typedef long long ll;
using namespace std;

int n;
char ch[1010];

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
	int T; readx(T);
	while (T--)
	{
		readx(n);
		scanf(" %s", ch+1);
		
		for (int i=1;i<=n;i++)
			printf("%c", ch[i+i-1]);
		printf("\n");
	}
	return 0;
}