#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#define ll long long
using namespace std;

int n,seq1[100010],seq2[100010],dp[100010],len,pos[100010];

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int main()
{
	readx(n);
	for (int i=1;i<=n;i++) readx(seq1[i]);
	for (int i=1;i<=n;i++) readx(seq2[i]);
	for (int i=1;i<=n;i++) pos[seq1[i]]=i;
	for (int i=1;i<=n;i++) seq2[i]=pos[seq2[i]];
	
	dp[1]=seq2[1]; len=1;
	for (int i=2;i<=n;i++)
	{
		if (seq2[i]>dp[len]) dp[++len]=seq2[i];
		else dp[lower_bound(dp+1,dp+len+1,seq2[i])-dp]=seq2[i];
	}
	printf("%d\n",len);
}
