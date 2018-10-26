#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<iterator>
#include<cmath>
#include<cstdlib>
#include<queue>
#include<vector>
#include<map>
#include<set>
#define ll long long
using namespace std;

int n,k;
const ll mod=1e9+9;
ll dp[2010][2010],dp2[2010][2010];
int seq1[2010],seq2[2010],last[2010];

ll C[2010][2010],fac[2010];

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Init_C(int upat)
{
	C[0][0]=1;
	for (int i=1;i<=upat;i++)
	{
		C[i][0]=1;
		for (int j=1;j<=i;j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	fac[0]=1;
	for (int i=1;i<=upat;i++) fac[i]=(fac[i-1]*i)%mod;
}


int main()
{
	readx(n); readx(k);
	for (int i=1;i<=n;i++) readx(seq1[i]);
	for (int i=1;i<=n;i++) readx(seq2[i]);
	sort(seq1+1,seq1+n+1); sort(seq2+1,seq2+n+1);
	
	int ptr=0;
	for (int i=1;i<=n;i++)
	{
		while (ptr<n && seq2[ptr+1]) ptr++;
		last[i]=ptr;
	}
	Init_C(n);
	
	dp[0][0]=1;
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<=min(i,k);j++)
		{
			dp[i][j]=dp[i-1][j];
			if (j && (last[i]-j+1)>0) 
			{
				dp[i][j]=(dp[i][j]+(dp[i-1][j-1]*(last[i]-j+1))%mod)%mod;
			}
		}
	}
	
	for (int )
	
}