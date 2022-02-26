#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
using namespace std;
const int MAXN=3e4+100;
const double inf=1e18;
int maxx,tot,dat[MAXN],prime[MAXN];
double dp[MAXN];
double tmp[MAXN][20];
bool check(int x)
{
	for(int i=2;i*i<=x;i++)
		if(x%i==0) return 0;
	return 1;
}
void init()
{
	for(int i=2;i<=maxx;i++)
		if(check(i)) prime[++tot]=i;
}
int main()
{
	int T;cin>>T;
	for(int i=1;i<=T;i++)
	{
		scanf("%d",&dat[i]);
		maxx=max(maxx,dat[i]);
	}
	init();
	for(int i=1;i<=maxx;i++)
		dp[i]=-inf;
	for(int i=1;i<=tot;i++)
	{
		int base=1,tim=0;
		double lg=log(prime[i]);
		for(int j=0;;j++)
		{
			base*=prime[i];tim++;
			if(base>maxx) break;
			for(int k=0;k+base<=maxx;k++)
				tmp[k+base][j]=dp[k]+tim*lg;
		}
		base=1;tim=0;
		for(int j=0;;j++)
		{
			base*=prime[i];tim++;
			if(base>maxx) break;
			for(int k=0;k+base<=maxx;k++)
				dp[k+base]=max(tmp[k+base][j],dp[k+base]);
		}
	}
	for(int i=1;i<=maxx;i++)
		dp[i]=max(dp[i],dp[i-1]);
	for(int i=1;i<=T;i++)
		printf("%.10lf\n",dp[dat[i]]);
}