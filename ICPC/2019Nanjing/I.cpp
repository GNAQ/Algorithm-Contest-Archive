#include<iostream>
#include<cstdio>
#include<map> 
#define LL long long
#define ull unsigned long long
using namespace std;
const int MAXN=100;
const int MAXM=1e5+100;
const int mod=1e9+7;
const ull base=19260817;
map<ull,LL>dp;
LL num[MAXN],jc[MAXM],st,n,zero;
LL dfs(int power,int res)
{
	ull now=0;LL ans=0;
	if(res==0) return 1;
	if(power>=50) return jc[res];
	for(int i=1;i<=50;i++) now=now*base+num[i];
	if(dp[now]) return dp[now];
	for(int to=1;to<=min(50,power);to++)
	{
		if(!num[to]) continue;
		num[to]--;
		ans+=(num[to]+1)*dfs(power+to,res-1);
		ans%=mod;
		num[to]++;
	}
	dp[now]=ans;
	return ans;
}
int main()
{
	cin>>n>>st;
	jc[0]=jc[1]=1;
	for(int i=2;i<=n;i++)
		jc[i]=(jc[i-1]*i)%mod;
	for(int i=1;i<=n;i++)
	{
		LL tmp;
		scanf("%lld",&tmp);
		if(tmp==0) 
		{
			zero++;
			i--;
			n--;
		}
		else num[tmp]++;
	}
	LL ans=dfs(st,n);
	for(int i=n+1;i<=n+zero;i++)
	{
		ans*=i;
		ans%=mod;
	}
	cout<<ans;
}
