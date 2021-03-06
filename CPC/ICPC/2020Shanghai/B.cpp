#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
typedef long long ll;
using namespace std;

int n,m;
char G1[1010][1010],G2[1010][1010];

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
	readx(n); readx(m);
	for (int i=1;i<=n;i++)
		scanf("%s", G1[i]+1);
	for (int i=1;i<=n;i++)
		scanf("%s", G2[i]+1);
	
	int cnt=0,lim=(n*m)/2;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			if (G1[i][j]=='.') G1[i][j]=0;
			else G1[i][j]=1;
			if (G2[i][j]=='.') G2[i][j]=0;
			else G2[i][j]=1;
			G2[i][j]^=G1[i][j];
			cnt+=G2[i][j];
		}
	
	if (cnt<=lim)
	{
		for (int i=1;i<=n;i++) 
		{
			for (int j=1;j<=m;j++)
				printf("%c", ".X"[(int)G1[i][j]]);
			puts("");
		}
	}
	else
	{
		for (int i=1;i<=n;i++) 
		{
			for (int j=1;j<=m;j++)
				printf("%c", ".X"[(int)(G1[i][j]^1)]);		
			puts("");
		}
	}
	
	return 0;
}
