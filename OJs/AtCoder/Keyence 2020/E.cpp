#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;

struct ed
{
	int pre,v,id,w;
} edge[400010];
int at=1,ptr[100010];

int eans[200010],vans[100010];

int n,m,d[100010],p[100010],id[100010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int u,int v,int id)
{
	edge[++at].v=v;
	edge[at].pre=ptr[u];
	edge[at].id=id;
	ptr[u]=at;
	edge[++at].v=u;
	edge[at].pre=ptr[v];
	edge[at].id=id;
	ptr[v]=at;
}

// 不出环：考虑环上最小点不可能存在。
void Color(int u,int fa)
{
	for (int v=ptr[u];v;v=edge[v].pre)
		if (edge[v].v!=fa)
		{
			vans[edge[v].v]=vans[u]^1;
			Color(edge[v].v,u);
		}
}

int main()
{
	readx(n); readx(m);
	for (int i=1;i<=n;i++) readx(d[i]);
	int u,v;
	for (int i=1;i<=m;i++) 
	{
		readx(u); readx(v);
		Is(u,v,i);
	}
	
	for (int i=1;i<=n;i++)
	{
		bool flag=0; int min_d = 2*1e9, targ, tmpid;
		
		for (int v=ptr[i];v;v=edge[v].pre)
		{
			if (d[edge[v].v]<=d[i])
			{
				flag=1;
				if ((d[edge[v].v]<min_d) || (d[edge[v].v]==min_d && edge[v].v>targ))
				{
					targ=edge[v].v;
					min_d=d[edge[v].v];
					tmpid=edge[v].id;
				}
			}
		}
		p[i]=targ;
		id[i]=tmpid;
		
		if (!flag)
		{
			printf("-1\n");
			return 0;
		}
	}
	
	at=1; memset(ptr,0,sizeof(ptr));
	for (int i=1;i<=n;i++)
		Is(i,p[i],id[i]);
	
	for (int i=1;i<=n;i++) if (!vans[i])
	{
		vans[i]=2;
		Color(i,0);
	}
	for (int i=1;i<=m;i++) eans[i]=1e9;
	
	for (int i=1;i<=n;i++)
		for (int v=ptr[i];v;v=edge[v].pre)
			if (edge[v].v==p[i])
			{
				// cout<<"!!"<<i<<" "<<edge[v].v<<" "<<edge[v].id<<endl;
				eans[edge[v].id]=d[i];
			}
	
	for (int i=1;i<=n;i++)
		printf("%c","  BW"[vans[i]]);
	printf("\n");
	for (int i=1;i<=m;i++) 
		printf("%d\n",eans[i]);
	return 0;
}