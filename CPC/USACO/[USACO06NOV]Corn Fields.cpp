#include<bits/stdc++.h>
#define ll long long
using namespace std;

int N,M;
ll dp[14][2200];
int mapx[14][14],maps[14];

void readx(int& x)
{
	x=0; ll k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

bool Okay(int val)
{
	for (int i=1;i<M;i++) if (((1<<(i-1))&val) && ((1<<i)&val)) return false;
	return true;
}

main()
{
	readx(N); readx(M);
	for (int i=1;i<=N;i++)
		for (int j=1;j<=M;j++) readx(mapx[i][j]);
	
	for (int i=1;i<=N;i++)
		for (int j=1;j<=M;j++) maps[i]=(maps[i]<<1)+(mapx[i][j]^1);
		
	for (int i=0;i<(1<<M);i++) if (Okay(i) && (!(maps[1]&i))) dp[1][i]=1;
	
	for (int i=2;i<=N;i++)
		for (int sta=0;sta<(1<<M);sta++) if (Okay(sta) && (!(sta&maps[i])))
			for (int pre=0;pre<(1<<M);pre++) if (Okay(pre) && (!(sta&pre))) dp[i][sta]+=dp[i-1][pre];
	
	ll ans=0;
	for (int i=0;i<(1<<M);i++) if (!(i&maps[N])) ans+=dp[N][i];
	printf("%lld\n",ans%100000000);
	return 0;
}
