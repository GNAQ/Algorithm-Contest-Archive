#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
#define LL long long
const int MAXN=3e5+100;
const int mod=1e9+7;
struct Node{
	int to;
	int id;
	int next;
}e[MAXN<<1];
int head[MAXN],num_p[MAXN],num_e[MAXN],num_pe[MAXN],dep[MAXN],fa[MAXN][21],tot,n,m,k;
LL fac[MAXN],fav[MAXN];
void init()
{
	tot=0;
	for(int i=1;i<=n;i++)
	{
		head[i]=0;
		num_p[i]=0;
		num_e[i]=0;
		num_pe[i]=0;
	}
	memset(head,0,sizeof head);
}
LL qpow(LL base,int tim)
{
	LL ans=1;
	while(tim)
	{
		if(tim&1) ans=(ans*base)%mod;
		tim>>=1;base=(base*base)%mod;
	}
	return ans;
}
void pre()
{
	fac[0]=fav[0]=1;
	for(int i=1;i<=MAXN-100;i++)
		fac[i]=(fac[i-1]*i)%mod;
	fav[MAXN-100]=qpow(fac[MAXN-100],mod-2);
	for(int i=MAXN-101;i>=1;i--)
		fav[i]=(fav[i+1]*(i+1))%mod;
}
LL C(int N,int K)
{
	return (((fac[N]*fav[K])%mod)*fav[N-K])%mod;
}
void add_edge(int u,int v,int id)
{
	e[++tot].next=head[u];
	e[tot].to=v;
	e[tot].id=id;
	head[u]=tot;
}
void dfs(int x,int f,int deep)
{
	fa[x][0]=f;dep[x]=deep;
	for(int i=head[x];i;i=e[i].next)
	{
		int to=e[i].to;
		if(to==f) continue;
		dfs(to,x,deep+1);
	}
}
int get_lca(int u,int v)
{
	if(dep[u]<=dep[v])
		swap(u,v);
	int delt=dep[u]-dep[v];
	for(int i=20;i>=0;i--)
		if(delt&(1<<i))
			u=fa[u][i];
	if(u==v) return u;
	for(int i=20;i>=0;i--)
		if(fa[u][i]!=fa[v][i])
		{
			u=fa[u][i];
			v=fa[v][i];
		}
	return fa[u][0];
}
void dfs1(int x)
{
	for(int i=head[x];i;i=e[i].next)
	{
		int to=e[i].to;
		if(to==fa[x][0])
			continue;
		dfs1(to);
		num_p[x]+=num_p[to];
		num_pe[e[i].id]=num_e[to];
		num_e[x]+=num_e[to];
	}
}
int main()
{
	pre();
	int T;cin>>T;
	while(T--)
	{	
		cin>>n>>m>>k;init();
		for(int i=1;i<=n-1;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			add_edge(u,v,i);
			add_edge(v,u,i);
		}
		dfs(1,1,1);
		for(int j=1;j<=20;j++)
			for(int i=1;i<=n;i++)
				fa[i][j]=fa[fa[i][j-1]][j-1];
		for(int i=1;i<=m;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			int lca=get_lca(u,v);
			if(lca!=1) 
				num_p[fa[lca][0]]--;
			num_p[lca]--;
			num_p[u]++;num_p[v]++;
			num_e[u]++;num_e[v]++;
			num_e[lca]-=2;
			//cout<<"!!!"<<u<<" "<<v<<" "<<lca<<endl;
		}
		dfs1(1);
		LL ans=0;
		for(int i=1;i<=n;i++)
			if(num_p[i]>=k)
			{
				//cout<<i<<" "<<num_p[i]<<" "<<C(num_p[i],k)<<endl;
				ans=(ans+C(num_p[i],k))%mod;
			}
		for(int i=1;i<=n-1;i++)
			if(num_pe[i]>=k)
			{
				//cout<<i<<" "<<num_pe[i]<<" "<<C(num_pe[i],k)<<endl;
				ans=(ans-C(num_pe[i],k))%mod;
			}
		printf("%lld\n",(ans+mod)%mod);
	}
}