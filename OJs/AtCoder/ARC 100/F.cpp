#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
typedef long long ll;
using namespace std;

const int mod = 1000000007;
int N,K,M,ai[100010],F,B;
int dp[25010][410],sfix[410],dp2[25010][410];
int fac[1010],ans;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int fastpow(int an,int p)
{
	int ret=1;
	for (;p;p>>=1,an=1LL*an*an%mod) if (p&1) ret=1LL*ret*an%mod;
	return ret;
}

bool IsAColorful()
{
	if (M<K) return 0;
	
	int vis[410],totv=0;
	memset(vis,0,sizeof vis);
	
	for (int i=1;i<=K;i++) 
	{
		if (!vis[ai[i]]) totv++;
		vis[ai[i]]++;
	}
	
	for (int i=K+1;i<=M;i++)
	{
		if (totv==K) return 1;
		vis[ai[i-K]]--;
		if (!vis[ai[i-K]]) totv--;
		if (!vis[ai[i]]) totv++;
		vis[ai[i]]++;
	}
	if (totv==K) return 1;
	return 0;
}

bool ADistinct()
{
	bool vis[410];
	memset(vis,0,sizeof vis);
	for (int i=1;i<=M;i++)
	{
		if (vis[ai[i]]) return 0;
		vis[ai[i]]=1;
	}
	return 1;
}

void GetFB()
{
	F=1; B=1;
	bool vis[410];
	
	memset(vis,0,sizeof vis);
	vis[ai[F]]=1;
	while (!vis[ai[F+1]]) 
		{ F++; vis[ai[F]]=1; }
	
	memset(vis,0,sizeof vis);
	vis[ai[M+1-B]]=1;
	while (!vis[ai[M-B]])
		{ B++; vis[ai[M+1-B]]=1; }
	return;
}

int main()
{
	// Initialization
	fac[0]=1;
	for (int i=1;i<=1000;i++) fac[i]=1LL*fac[i-1]*i%mod;
	
	readx(N); readx(K); readx(M);
	for (int i=1;i<=M;i++) readx(ai[i]);
	
	ans=1LL*(N-M+1)*fastpow(K,N-M)%mod;
	
	// Case 1
	if (IsAColorful())
	{
		printf("%d\n",ans);
		return 0;
	}
	
	dp[0][0]=1;
	for (int i=1;i<=N;i++)
	{
		for (int j=1;j<K;j++)
			dp[i][j] = (1LL * dp[i - 1][j - 1] * (K-j+1) % mod + sfix[j]) % mod;
		// construct Suffix sum
		for (int j=K-1;j;j--)
			sfix[j]=(sfix[j+1]+dp[i][j])%mod;
	}
	// Case 2 
	if (ADistinct())
	{
		memset(sfix,0,sizeof sfix);
		for (int i=1;i<=N;i++)
		{
			for (int j=1;j<K;j++)
			{
				dp2[i][j] = (1LL * dp2[i - 1][j - 1] * (K - j + 1) % mod + sfix[j]) % mod;
				if (j>=M) dp2[i][j]=(dp2[i][j]+dp[i][j])%mod;
			}
			for (int j=K-1;j;j--)
				sfix[j]=(sfix[j+1]+dp2[i][j])%mod;
		}
		
		int ans1=sfix[1];
		ans1=(1LL*ans1*fastpow(fac[K],mod-2)%mod*fac[K-M]%mod); // dp_ans div (K!/(K-M)!) 
		
		printf("%d\n",(ans-ans1+mod)%mod);
		return 0;
	}
	
	// Case 3
	GetFB(); 
	int ans2=0, div2=1LL*fastpow(fac[K],mod-2)*fac[K-F]%mod*fastpow(fac[K],mod-2)%mod*fac[K-B]%mod;
	for (int i=1;i<=N-M+1;i++) // Ai start pos
	{
		int L=i, R=i+M-1; // Ai interval
		pair<int,int> lr[2]; // (diff and also gen_able) range
		int anslr[2];
		
		lr[0]=make_pair(L,L + F-1);
		lr[1]=make_pair(N-R+1,N-R+1 + B-1);
		for (int id=0;id<=1;id++)
		{
			int lx=lr[id].first, rx=lr[id].second, sum=0;
			for (int i=lx;i>=1;i--)
			{
				if (rx-i+1>=K) break;
				sum=(sum+dp[rx][rx-i+1])%mod;
			}
			anslr[id]=sum;
		}
		ans2=(ans2+ 1LL*anslr[0]*anslr[1]%mod)%mod;
	}
	
	ans2=(1LL*ans2*div2)%mod;
	printf("%d\n",(ans-ans2+mod)%mod);
	return 0;
}
