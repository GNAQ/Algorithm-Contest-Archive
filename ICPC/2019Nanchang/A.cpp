#include<cstdio>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<string>
#include<algorithm>
typedef long long ll;
using namespace std;

struct _Node
{
	int fa,siz,me;
} dsu[2000010];
int id[1000010],idcnt,dead[1000010];

struct _Tree
{
	int op,a,b,ans;
} t[1000010];
struct ed
{
	int pre,to;
} edge[1000010];
int at,ptr[1000010];

int n,m;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

inline void Is(int u,int v)
{
	edge[++at].pre=ptr[u];
	edge[at].to=v;
	ptr[u]=at;
}

inline int NewDsu(int u)
{
	idcnt++;
	dsu[idcnt].fa=dsu[idcnt].me=u;
	dsu[idcnt].siz=1;
	return idcnt;
}

inline int Find(int u)
{
	while (dsu[u].fa!=dsu[u].me)
		u=dsu[u].fa;
	return u;
}

inline void Merge(int u,int v) // u <- v
{
	int fau=Find(u), fav=Find(v);
	if (dsu[fau].siz<dsu[fav].siz) swap(fau,fav);
	dsu[fau].siz+=dsu[fav].siz;
	dsu[fav].fa=fau;
}

void DFS(int u)
{
	int oldid=-1,oldfa=-1,oldfb=-1;
	int a=t[u].a,b=t[u].b;
	if (t[u].op==1)
	{
		if (a!=b && dead[a]==0 && dead[b]==0 && Find(id[a])!=Find(id[b]))
		{
			oldfa=Find(id[a]); oldfb=Find(id[b]);
			Merge(id[a],id[b]);
		}
	}
	else if (t[u].op==2)
	{
		if (dead[a]==0) dsu[Find(id[a])].siz--;
		dead[a]++;
	}
	else if (t[u].op==3)
	{
		if (a!=b && dead[a]==0 && dead[b]==0 && Find(id[a])!=Find(id[b]))
		{
			dsu[Find(id[a])].siz--;
			oldid=id[a];
			id[a]=NewDsu(a);
			Merge(id[b],id[a]);
		}
	}
	else if (t[u].op==4)
	{
		if (dead[a] || dead[b]) t[u].ans=-1;
		else t[u].ans= (Find(id[a])==Find(id[b]) ? 1 : -1);
	}
	else
	{
		if (dead[a]) t[u].ans=0;
		else t[u].ans=dsu[Find(id[a])].siz;
	}
	
	for (int v=ptr[u];v;v=edge[v].pre)
		DFS(edge[v].to);
	
	// revoke!!
	if (t[u].op==1 && oldfa!=-1)
	{
		if (dsu[oldfa].fa!=oldfa)
		{
			dsu[oldfb].siz-=dsu[oldfa].siz;
			dsu[oldfa].fa=oldfa;
		}
		else
		{
			dsu[oldfa].siz-=dsu[oldfb].siz;
			dsu[oldfb].fa=oldfb;
		}
	}
	else if (t[u].op==2)
	{
		dead[a]--;
		if (dead[a]==0) dsu[Find(id[a])].siz++;
	}
	else if (t[u].op==3 && oldid!=-1)
	{
		dsu[Find(id[b])].siz--;
		id[a]=oldid;
		dsu[Find(id[a])].siz++;
	}
}

main()
{
	readx(n); readx(m);
	
	idcnt=n;
	for (int i=1;i<=n;i++) 
	{
		id[i]=i;
		dsu[i].fa=dsu[i].me=i; dsu[i].siz=1;
	}
	
	int opi,ki,ai,bi;
	for (int i=1;i<=m;i++)
	{
		bi=0;
		readx(opi); readx(ki); readx(ai);
		if (opi==1 || opi==3 || opi==4)
			readx(bi);
		Is(ki,i);
		t[i].op=opi; t[i].a=ai; t[i].b=bi;
	}
	
	for (int v=ptr[0];v;v=edge[v].pre)
		DFS(edge[v].to);
	
	for (int i=1;i<=m;i++) 
	{
		if (t[i].op==4) printf("%s\n", t[i].ans==1 ? "Yes" : "No");
		if (t[i].op==5) printf("%d\n",t[i].ans);
	}
}