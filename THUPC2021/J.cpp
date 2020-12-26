#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int mod= 998244353;
const int MAXN=1010;
int s[10],dp[MAXN][50],dat[50],ans,n,k;
void dfs(int pos)
{	
	for(int dig=0;dig<=1;dig++)
		for(int last=0;last<=s[k-1];last++)
		{	
			int now=(last<<1)|dig;
			if(dat[now])
			{
				int to=now&s[k-1];
				dp[pos][to]+=dp[pos-1][last];
				dp[pos][to]%=mod;
			}
		}
	if(pos==n)
	{
		for(int i=0;i<=s[k-1];i++)
		{
			ans+=dp[pos][i];	
			ans%=mod;
		}
		return ;
	}
	dfs(pos+1);	
}
int main()
{
	s[1]=1;s[2]=3;
	s[3]=7;s[4]=15;
	cin>>n>>k;
	if(n<=16)
	{
		for(int i=0;i<(1<<n);i++)
		{
			for(int j=n-1;j>=0;j--)
				dat[n-j-1]=(i>>j)&1;
			int flag=1;
			for(int j=0;j+k<=n;j++)
			{
				int tmp=((i>>j)&s[k]);
				if(!dat[tmp]) flag=0;
			}
			ans+=flag;
		}
		cout<<ans;
	}		
	else {
		for(int i=0;i<(1<<16);i++)
		{
			for(int j=n-1;j>=0;j--)
				dat[n-j-1]=(i>>j)&1;
			int flag=1;
			for(int j=0;j+k<=16;j++)
			{
				int tmp=(i&(s[k]<<j))>>j;
				if(!dat[tmp]) flag=0;
			}
			if(flag) 
			{
				memset(dp,0,sizeof dp);
				dp[16][i&s[k-1]]=1;
				dfs(17);
			}
		}
		cout<<ans;
	}
}
