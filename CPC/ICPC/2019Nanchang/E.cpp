#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<vector>
typedef long long ll;
using namespace std;

struct ed
{
	int fr,to;
	ll w;
} edge[1000010];
int at=0;
int n,m,k,ds[100010];
ll ans;
bool vis[1000010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int u,int v,ll w)
{
	at++;
	edge[at].fr=u;
	edge[at].to=v;
	edge[at].w=w;
}

int Find(int e_1)
{
	if (e_1!=ds[e_1]) ds[e_1]=Find(ds[e_1]);
	return ds[e_1];
}
void Merge(int e_1,int e_2)
{
	ds[Find(e_2)]=Find(e_1);
}

void Clear()
{
	for (int i=1;i<=at;i++) vis[i]=0;
	at=0; ans=0;
}

void InitDS(int lim)
{
	for (int i=1;i<=lim;i++) ds[i]=i;
}

bool cmp(ed a, ed b)
{
	return a.w>b.w;
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		readx(n); readx(m); readx(k);
		int u,v,c; ll w;
		int cnt=0,wcnt=0;
		InitDS(n);
		
		for (int i=1;i<=m;i++)
		{
			readx(u); readx(v); readx(w); readx(c);
			if (c)
			{
				Is(u,v,w);
			}
			else
			{
				ans+=w;
				if (Find(u)!=Find(v))
				{
					Merge(u,v);
					cnt++;
				}
			}
		}
		
		if (at)
		{
			sort(edge+1,edge+at+1,cmp);
			for (int i=1;i<=at;i++)
			{
				u=edge[i].fr; v=edge[i].to; w=edge[i].w;
				if (wcnt==k) break;
				if (Find(u)!=Find(v))
				{
					ans+=w;
					cnt++;
					wcnt++;
					Merge(u,v);
					vis[i]=1;
				}
			}
		}
		
		if (cnt!=n-1)
		{
			printf("-1\n");
			Clear();
			continue;
		}
		
		for (int i=1;i<=at;i++) if (wcnt<k && vis[i]==0) 
		{
			wcnt++; ans+=edge[i].w;
		}
		
		printf("%lld\n",ans);
		Clear();
	}
	return 0;
}