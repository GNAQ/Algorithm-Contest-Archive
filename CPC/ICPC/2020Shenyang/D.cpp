#include<iostream>
#include<cstdio>
using namespace std;
const long long MAXN=1e5+100;
long long n,now_cnt=1;
long long dat[MAXN];
long long ans=0;
void dfs(long long pos,long long odd,long long even,long long len,long long now_ans)
{
	if(pos==n+1) 
	{
		now_ans+=len*odd;
		if(now_ans==ans)
		{
			for(long long i=1;i<=n;i++)
				if(dat[i]==1) printf("r");
				else printf("b");
			printf("\n");now_cnt++;
			if(now_cnt>=100) exit(0);
		}
		return ;
	}
	dat[pos]=0;dfs(pos+1,odd,even,len+1,now_ans);
	dat[pos]=1;dfs(pos+1,even+len,odd,1,now_ans+1ll*len*odd);
}
void solve()
{
	long long pos=n+2;
	if(n&1) pos=n+1;
	for(;now_cnt<100&&pos>(n/2)+1&&(n/2)>=1;now_cnt++)
	{
		for(long long j=1;j<=n;j++)
		{
			if(j+1==pos||j==pos) printf("r");
			else if(j==n/2) printf("r");
			else printf("b");
		}
		printf("\n");
		pos--;
	}
	if(now_cnt>=100) exit(0);
	for(long long i=n/2-1;i>=1;i--)
	{
		dat[i]=1;
		dfs(i+1,i,0,1,0);
		dat[i]=0;
	}
}
int main()
{
	cin>>n;
	if(n&1) ans=1ll*(n+1)*(n+1)/4;
	else ans=1ll*n*(n+2)/4;
	printf("%lld\n",ans);
	for(long long i=1;i<=n;i++)
		if(i==n/2+1) printf("r");
		else printf("b");
	printf("\n");
	solve();
}