#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
using namespace std;

char rep[10011];

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
	int n,m; 
	readx(n); readx(m);
	
	for (int i=1;i<=m;i++)
	{
		int ans=0;
		scanf("%s", rep+1);
		
		for (int j=1;j<=n;j++)
		{
			if (rep[j]=='n')
				ans |= (1 << (n-j) );
		}
		ans++;
		printf("%d\n",ans);
	}
	return 0;
}
