#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+100;
const int mod=1e9+7;
int dp[MAXN],head[MAXN],tot;
int e[MAXN*30],nxt[MAXN*30];
void init()
{
	for(int i=1;i<=MAXN-100;i++)
		for(int j=i;j<=MAXN-100;j+=i)
		{
			e[++tot]=i;
			nxt[tot]=head[j];
			head[j]=tot;
		}
}
int main()
{
	init();
	int n;scanf("%d",&n);
	if(n==1) {printf("1");return 0;}
	if(n==2) {printf("2");return 0;}
	if(n==3) {printf("6");return 0;}
	dp[1]=1;dp[2]=1;
	for(int i=4;i<=n;i++)
	{
		dp[i-1]=(dp[i-1]+dp[1])%mod;
		dp[i-1]=(dp[i-1]+dp[2])%mod;
		for(int ii=head[i];ii;ii=nxt[ii])
		{
			int j=e[ii];
			if(j>=i-1||j<=2) continue;		
			dp[i-1]=(dp[i-1]+dp[j])%mod;
		}
		for(int ii=head[i-1];ii;ii=nxt[ii])
		{
			int j=e[ii];
			if(j>=i-1||j<=2) continue;		
			dp[i-1]=(dp[i-1]+dp[j])%mod;
		}
		for(int ii=head[i-2];ii;ii=nxt[ii])
		{
			int j=e[ii];
			if(j>=i-1||j<=2) continue;		
			dp[i-1]=(dp[i-1]+dp[j])%mod;
		}
//		for(int j=1;j<=n;j++)
//			cout<<dp[j]<<" ";
//		cout<<endl;
	}
	long long ans=0;
	for(int i=1;i<=n;i++)
		ans=(ans+dp[i])%mod;
	cout<<(ans*n)%mod;
}