#include<iostream>
#include<cstring>
#include<cstdio>
#define LL long long
using namespace std;
const LL MAXN=550;
const LL inf=1e18;
LL n,m,match[MAXN],mapp[MAXN][MAXN],vis[MAXN];
LL ex[MAXN],ey[MAXN],slack[MAXN],pre[MAXN],enemy[MAXN],num_a[MAXN],num_b[MAXN],val[MAXN];
void match_(LL u)
{
	LL x,y=0,yy=0,delta;
	memset(pre,0,sizeof pre);
	for(LL i=1;i<=n;i++) slack[i]=inf;
	match[y]=u;
	while(1)
	{
		x=match[y];delta=inf;vis[y]=1;
		for(LL i=1;i<=n;i++)
		{
			if(vis[i]) continue;
			if(slack[i]>ex[x]+ey[i]-mapp[x][i])
			{
				pre[i]=y;
				slack[i]=ex[x]+ey[i]-mapp[x][i];
			}
			if(slack[i]<delta){delta=slack[i];yy=i;}
		}
		for(LL i=0;i<=n;i++)
        {	
            if(vis[i]) ex[match[i]]-=delta,ey[i]+=delta;
            else slack[i]-=delta;
        }
        y=yy;
        if(match[y]==-1)break;
	}
	while(y){match[y]=match[pre[y]];y=pre[y];}
}
LL KM()
{
	memset(match,-1,sizeof match);
	for(LL i=1;i<=n;i++)
	{
		memset(vis,0,sizeof vis);
		match_(i);
	}
	LL res=0;
	for(LL i=1;i<=n;i++)
		if(match[i]!=-1) res+=mapp[match[i]][i];
	return res;
}
int main()
{
	cin>>n;
	for(LL i=1;i<=n;i++)
		scanf("%lld",&enemy[i]);
	for(int i=1;i<=n;i++)
		scanf("%lld",&val[i]);
	for(LL i=1;i<=n;i++)
		scanf("%lld",&num_a[i]);
	for(int i=1;i<=n;i++)
		scanf("%lld",&num_b[i]);
	for(LL i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
				if(num_a[i]+num_b[j]>enemy[k])
					mapp[i][j]+=val[k];
	printf("%lld\n",KM());
}
