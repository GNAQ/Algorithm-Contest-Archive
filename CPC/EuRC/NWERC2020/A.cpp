#include<iostream>
#include<cstdio>
#define LL long long
using namespace std;
const LL MAXN=1e7+100;
LL n,q,mx_pos=-1;
LL dat[MAXN],dp[MAXN];
int main()
{
	cin>>n>>q;
	for(int i=1;i<=1e6;i++)
		dp[i]=1e18;
	for(int i=1;i<=n;i++)
		scanf("%lld",&dp[i]);
	for(LL i=1;i<=n;i++)
	{
		int flag=-1;
		for(LL j=1;j<=n;j++)
			if(dp[i]*j>dp[j]*i)
			{
				flag=1;
				break;
			}
		if(flag==-1)
			mx_pos=i;
	} 
	for(LL i=n;i>=1;i--)
	    for(LL j=n+1;j<=1e6;j++)
			dp[j]=min(dp[j],dp[j-i]+dp[i]);
	for(LL i=1;i<=q;i++)
	{
		LL k;scanf("%lld",&k);
		if(k<=1e6) printf("%lld\n",dp[k]);
		else {
			LL delt=(k-1e6-1)/mx_pos+1;
			printf("%lld\n",delt*dp[mx_pos]+dp[k-delt*mx_pos]);
		}
	}
}
