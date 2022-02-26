#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=1e6+100;
int fa[maxn],num1[maxn],num2[maxn],vis[maxn];
int find(int x)
{
	if(x!=fa[x]) fa[x]=find(fa[x]);
	return fa[x];
}
int main()
{
	
	int T;cin>>T;
	for(int ii=1;ii<=T;ii++)
	{
		int n,m;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
		{
			fa[i]=i;
			vis[i]=0;
			num1[i]=0;
			num2[i]=1;
		}
		for(int i=1;i<=m;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			if(find(u)==find(v))
				num1[find(u)]++;
			else {
				int fu=find(u),fv=find(v);
				num1[fu]+=num1[fv];
				num2[fu]+=num2[fv];
				num1[fu]++;
				fa[fv]=fu;
			}
		}
		int ans=0;
		for(int i=1;i<=n;i++)
			if(!vis[find(i)])
			{
				vis[find(i)]=1;
				ans+=max(0,num1[find(i)]-num2[find(i)]);
			}
		printf("Case #%d: %d\n",ii,ans);
	}
}