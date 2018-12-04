#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#define ll long long
using namespace std;

struct ed { int fr,to,w; }edge[200000];
int n,m,at;
//Kruskal
int dsu[100010],mst_w;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int fx,int tx,int wx)
{
	edge[++at].fr=fx;
	edge[at].to=tx;
	edge[at].w=wx;
}

int Find(int e_1)
{
	if (dsu[e_1]!=e_1) dsu[e_1]=Find(dsu[e_1]);
	return dsu[e_1];
}
void Merge(int e_1,int e_2)
{
	dsu[Find(e_2)]=Find(e_1);
}

bool cmp1(ed a1,ed a2)
{
	return a1.w<a2.w;
}
bool Kruskal()
{
	sort(edge+1,edge+at+1,cmp1); int tmp=0;
	for (int i=1;i<=n;i++) dsu[i]=i;
	for (int i=1;i<=at;i++)
	{
		if (tmp==n-1) break;
		if (Find(edge[i].fr)!=Find(edge[i].to))
		{
			Merge(edge[i].fr,edge[i].to);
			mst_w+=edge[i].w;
			tmp++;
		}
	}
	if (tmp<n-1) return false;
	return true;
}

int main()
{
	readx(n); readx(m); int fx,tx,wx;
	for (int i=1;i<=m;i++)
	{
		readx(fx); readx(tx); readx(wx);
		Is(fx,tx,wx);
	}
	
	if (!Kruskal()) printf("orz\n");
	printf("%d\n",mst_w);
}
