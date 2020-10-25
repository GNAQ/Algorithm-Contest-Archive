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

ll mod,n,k;
ll dp[110][600010];
ll sum[110];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

ll fpow(ll an,ll p)
{
	ll ret=1;
	for (;p;p>>=1,an=an*an%mod) if (p&1) ret=ret*an%mod;
	return ret;
}


int main()
{
	readx(n); readx(k); readx(mod);
	
	memset(dp,0,sizeof dp);
	dp[0][0]=1; 
	
	for (int i=1;i<=n;i++)
	{
		int lim = i*(i+1)/2*k;
		memset(sum,0,sizeof sum);
		for (int j=0;j<=lim;j++)
		{
			sum[j%i]=(sum[j%i]+dp[i-1][j])%mod;
			if (j-i*(k+1)>=0) sum[j%i]=(sum[j%i]-dp[i-1][j-i*(k+1)]+mod)%mod;
			dp[i][j]=sum[j%i];
		}
	}
	
	
	for (int i=0;i<=n;i++)
	{
		int lim = i*(i+1)/2*k;
		cout<<"[i:"<<i<<"]";
		for (int j=0;j<=lim;j++)
			printf("%lld%c",dp[i][j]," \n"[j==lim]);
	}
	cout<<"---------------------"<<endl;
	
	for (int i=1;i<=n;i++)
	{
		int lim=i*(i+1)/2*k;
		ll ans=0;
		for (int j=0;j<=lim;j++) // i as each n
			ans=(ans+dp[i-1][j]*dp[n-i][j]%mod)%mod;
		cout<<"$"<<ans<<endl;
		ans=(ans*(k+1)%mod-1+mod)%mod;
		printf("%lld\n",ans);
	}
	
	return 0;
}