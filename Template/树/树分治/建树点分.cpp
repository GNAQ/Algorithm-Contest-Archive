#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<queue>
#include<vector>
#include<map>
#include<set>
#define ll long long
#define fst first
#define snd second
#define p_b push_back
#define m_p make_pair
using namespace std;

vector<pair<int,int>> edge[10010];
vector<int> tree[10010];

int n,ans,kx,m;
int dptr,extra,subsiz,hpt;
int dis[10010],hsiz[10010],tsiz[10010];
bool vis[10010];

void readx(int& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int fx,int tx,int wx)
{
	edge[fx].p_b({tx,wx});
	edge[tx].p_b({fx,wx});
}
void Is_Tree(int fx,int tx) { tree[fx].p_b(tx); }

void _Init(int now,int fa,int nowdis)
{
	dis[++dptr]=nowdis;
	for (auto v:edge[now]) if ((!vis[v.fst]) && v.fst!=fa) _Init(v.fst,now,nowdis+v.snd);
}

int Solve(int now)
{
	dptr=0; _Init(now,0,extra);
	sort(dis+1,dis+dptr+1);
	
	int ret=0,lp=1,rp=dptr;
	while (lp<=rp)
	{
		if (dis[lp]+dis[rp]>kx) rp--;
		else if (dis[lp]+dis[rp]<kx) lp++;
		else if (dis[lp]+dis[rp]==kx) { ret++; rp--; }
	}
	return ret;
}

void GetHr(int now,int fa)
{
	tsiz[now]=1; hson[now]=0;
	for (auto v:edge[now]) if ((!vis[v.fst]) && v.fst!=fa)
	{
		GetHr(v.fst,now);
		tsiz[now]+=tsiz[v.fst];
		hsiz[now]=max(hsiz[now],tsiz[v.fst]);
	}
	hsiz[now]=max(hsiz[now],subsiz-tsiz[now]);
	if (hsiz[hpt]>hsiz[now]) hpt=now;
}

void BuildTree(int now)
{
	vis[now]=1;
	for (auto v:edge[now]) if (!vis[v.fst])
	{
		subsiz=tsiz[v.fst]; hpt=0;
		GetHr(v.fst,0); Is_Tree(now,hpt);
		BuildTree(v.fst);
	}
}

void Divs(int now)
{
	extra=0; ans+=Solve(now); vis[now]=1;
	for (auto v:edge[now]) if (!vis[v.fst]) { extra=v.snd; ans-=Solve(v.fst); }
	for (auto v:tree[now]) Divs(v);
}

int main()
{
	readx(n); readx(m); int fx,tx,wx;
	for (int i=1;i<n;i++)
	{
		readx(fx); readx(tx); readx(wx);
		Is(fx,tx,wx);
	}
	
	int root;
	subsiz=n; hsiz[0]=2e9; hpt=0;
	GetHr(1,0); root=hpt;
	BuildTree(hpt);
	
	for (int i=1;i<=m;i++)
	{
		ans=0; readx(kx);
		memset(vis,0,sizeof vis);
		Divs(root);
		if (ans) printf("AYE\n");
		else printf("NAY\n");
	}
	return 0;
}
