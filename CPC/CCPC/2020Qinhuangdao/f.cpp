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

struct ed
{
	int pre,to;
} edge[2000010];
int at,ptr[300010];
int n,m;
int id[300010];
int ind[300010],ecnt[300010],vcnt[300010],cnt;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Clear()
{
	for (int i=1;i<=cnt;i++)
		ecnt[i]=vcnt[i]=0;
	cnt=0;
	for (int i=1;i<=n;i++) 
		ptr[i]=id[i]=ind[i]=0;
	at=0;
}

void Is(int u,int v)
{
	at++;
	edge[at].pre=ptr[u];
	edge[at].to=v;
	ptr[u]=at;
}

void DFS(int u)
{
	for (int v=ptr[u];v;v=edge[v].pre)
		if (!id[edge[v].to])
		{
			id[edge[v].to]=cnt;
			DFS(edge[v].to);
		}
}

int main()
{
	int T; readx(T);
	for (int tt=1;tt<=T;tt++)
	{
		
		
		readx(n); readx(m); int ans;
		int u,v;
		for (int i=1;i<=m;i++)
		{
			readx(u); readx(v);
			Is(u,v); Is(v,u);
			ind[u]++; ind[v]++;
		}
		
		for (int i=1;i<=n;i++) if (!id[i])
		{
			id[i]=++cnt;
			DFS(i);
		}
		
		for (int i=1;i<=n;i++) 
		{
			vcnt[id[i]]++;
			ecnt[id[i]]+=ind[i];
		}
		for (int i=1;i<=cnt;i++) 
			ecnt[i]>>=1;
		
		// for (int i=1;i<=n;i++) 
			// printf("[%d] %d %d\n",i, id[i], ind[i]);
		
		ans=0;
		for (int i=1;i<=cnt;i++) 
			if (ecnt[i]>=vcnt[i]) ans+=ecnt[i]-vcnt[i];
		
		printf("Case #%d: %d\n", tt, ans);
		
		Clear();
	}
}