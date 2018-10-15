#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<iterator>
#include<cmath>
#include<cstdlib>
#include<vector>
#include<queue>
#include<set>
#include<map>
#define ll long long
#define fst first
#define snd second
using namespace std;

vector<pair<int,ll>> edge[100010];
int n,m,seq[100010];

int l[100010][22];
ll wl[100010][22];

bool used[100010],vis[100010];
int rest_cod[100010]; ll rest_min[100010];
struct _Node
{
	ll remain; int cod;
}nodes[100010],subs[100010];
int ctr1,ctr2;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int fx,int tx,ll wx)
{
	edge[fx].push_back({tx,wx});
	edge[tx].push_back({fx,wx});
}

bool cmp(const _Node& a1,const _Node& a2) { return a1.remain>a2.remain; }

void DFS(int now,int fa,ll tw)
{
	l[now][0]=fa; wl[now][0]=tw;
	for (int i=1;i<=20;i++) 
	{
		l[now][i]=l[l[now][i-1]][i-1];
		wl[now][i]=wl[now][i-1]+wl[l[now][i-1]][i-1];
	}
	for (auto v:edge[now]) if (v.fst!=fa) DFS(v.fst,now,v.snd);
}

int Find(int now,int fa)
{
	bool flag=1,sub_f=0;
	if (vis[now]) return 1;
	for (auto v:edge[now]) if (v.fst!=fa)
	{
		sub_f=1;
		if (!Find(v.fst,now))
		{
			flag=0;
			if (now==1) { subs[++ctr2].cod=v.fst; subs[ctr2].remain=v.snd; }
			else return 0;
		}
	}
	if (!sub_f) return 0;
	return flag;
}

bool Judge(int lim)
{
	ll tmp_n,way; ctr1=ctr2=0;
	memset(vis,0,sizeof vis); memset(used,0,sizeof used);
	for (int i=1;i<=m;i++)
	{
		// Upwent
		tmp_n=seq[i]; way=0;
		for (int j=20;j>=0;j--) if (l[tmp_n][j]>1 && way+wl[tmp_n][j]<=lim)
			{ way+=wl[tmp_n][j]; tmp_n=l[tmp_n][j]; }
		// remains
		if (l[tmp_n][0]==1 && way+wl[tmp_n][0]<=lim)
		{
			ctr1++; nodes[ctr1].cod=i; nodes[ctr1].remain=lim-way-wl[tmp_n][0];
			if (!rest_cod[tmp_n] || rest_min[tmp_n]>nodes[ctr1].remain)
				{ rest_cod[tmp_n]=i; rest_min[tmp_n]=nodes[ctr1].remain; }
		}
		else vis[tmp_n]=1;
	}
	// for (int i=1;i<=ctr1;i++) printf("%d %d\n",nodes[i].cod,nodes[i].remain);
	// system("pause");
	
	if (Find(1,0)) return true;
	sort(nodes+1,nodes+ctr1+1,cmp); sort(subs+1,subs+ctr2+1,cmp);
	
	// for (int i=1;i<=ctr2;i++) printf("%d %d\n",subs[i].cod,subs[i].remain);
	// system("pause");
	
	used[0]=1; int tptr=1;
	for (int i=1;i<=ctr2;i++)
	{
		if (!used[rest_cod[subs[i].cod]])
		{
			used[rest_cod[subs[i].cod]]=1;
			continue;
		}
		while (tptr<=ctr1 && (used[nodes[tptr].cod] || nodes[tptr].remain<subs[i].remain)) tptr++;
		if (tptr>ctr1) return false;
		used[nodes[tptr].cod]=1;
	}
	return true;
}

int main()
{
	// freopen("t.out","w",stdout);
	
	readx(n); int fx,tx,wx;
	for (int i=1;i<n;i++)
	{
		readx(fx); readx(tx); readx(wx);
		Is(fx,tx,wx);
	}
	readx(m);
	for (int i=1;i<=m;i++) readx(seq[i]);
	if (m<edge[1].size()) { printf("-1\n"); return 0; }
	DFS(1,0,0);
	
	int lx=0,rx=500000,mid,ans=-1;
	while (lx<=rx)
	{
		mid=(lx+rx)>>1;
		if (Judge(mid))
		{
			ans=mid;
			rx=mid-1;
		}
		else lx=mid+1;
	}
	
	printf("%d\n",ans);
	system("pause");
	return 0;
}