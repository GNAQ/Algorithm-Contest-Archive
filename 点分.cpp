#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<iterator>
#include<cmath>
#include<cstdlib>
#include<queue>
#include<vector>
#include<map>
#include<set>
#define ll long long
#define p_b push_back
#define m_p make_pair
#define fst first
#define snd second
using namespace std;

vector<pair<int,int>> edge[50010];

int dis[50010],dptr=0;
bool vis[50010]={0};

int tsiz[50010],subsiz,hsiz[50010],hpt;
int extra,ans=0,kx,n;

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

void _Init(int now,int fa,int nowdis)
{
	dis[++dptr]=nowdis;
	for (auto v:edge[now]) if ((!vis[v.fst]) && v.fst!=fa) _Init(v.fst,now,v.snd+nowdis);
}

int Solve(int now)
{
	dptr=0; _Init(now,0,extra);
	sort(dis+1,dis+dptr+1);
	
	int ret=0,lp=1,rp=dptr;
	while (lp<=rp)
	{
		if (dis[lp]+dis[rp]<=kx) { ret+=rp-lp; lp++; }
		else rp--;
	}
	return ret;
}

void GetHr(int now,int fa)
{
	tsiz[now]=1;
	for (auto v:edge[now]) if ((!vis[v.fst]) && v.fst!=fa)
	{
		GetHr(v.fst,now);
		tsiz[now]+=tsiz[v.fst];
		hsiz[now]=max(hsiz[now],tsiz[v.fst]);
	}
	hsiz[now]=max(hsiz[now],subsiz-tsiz[now]);
	if (hsiz[now]<hsiz[hpt]) hpt=now;
}

void Divs(int now)
{
	extra=0; ans+=Solve(now); vis[now]=1;
	for (auto v:edge[now]) if (!vis[v.fst])
	{
		extra=v.snd; ans-=Solve(v.fst); 
		
		subsiz=tsiz[v.fst]; hpt=0;
		GetHr(v.fst,0); Divs(hpt);
	}
}

int main()
{
	readx(n); int fx,tx,wx;
	for (int i=1;i<n;i++)
	{
		readx(fx); readx(tx); readx(wx);
		Is(fx,tx,wx);
	}
	readx(kx);
	hsiz[0]=2e9; hpt=0; subsiz=n;
	GetHr(1,0);
	Divs(hpt);
	printf("%d\n",ans);
	return 0;
}
