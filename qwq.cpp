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
using namespace std;
typedef long long ll;
typedef ostream_iterator<int> os_iter_int;

int n,m;
int seq[100010],setx[100010],ssiz;

struct Node { int l,r,id; } node[100010];

struct ed { int pre,to; } edge[200010]; 
int at=1,ptr[100010];

int dep[100010],nsiz[100010],hson[100010];
vector<int> nvs[100010];

template<typename int_t>
void readx(int_t& x)
{
    x=0; int_t k=1; char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

void Is(int fx,int tx)
{
	at++;
	edge[at].pre=ptr[fx];
	edge[at].to=tx;
	ptr[fx]=at;
}

void Unique()
{
	memcpy(setx,seq,sizeof(int)*(n+6));
	sort(setx+1,setx+n+1); ssiz=unique(setx+1,setx+n+1)-(setx+1);
	for (int i=1;i<=n;i++) seq[i]=lower_bound(setx+1,setx+ssiz+1,seq[i])-setx;
}

bool Cmp_ranges(const Node& a,const Node& b)
{
	if (a.l==b.l) return a.r>b.r;
	else return a.l<b.l;
}

int sta[100010]; int hd;
void Build()
{
	sort(node+1,node+m+1,Cmp_ranges);
	sta[++hd]=1;
	for (int i=2;i<=m;i++)
	{
		while (hd)
		{
			if (node[sta[hd]].r<node[i].l) hd--;
			else break;
		}
		Is(node[sta[hd]].id,node[i].id);
		sta[++hd]=i;
	}
}

void DFS1(int now,int fa)
{
	nsiz[now]=1; dep[now]=dep[fa]+1;
	for (int v=ptr[now];v;v=edge[v].pre) 
	{
		DFS1(edge[v].to,now);
		nsiz[now]+=nsiz[edge[v].to];
		if (nsiz[hson[now]]<nsiz[edge[v].to]) hson[now]=edge[v].to;
	}
	
	cout<<"elem in "<<now<<"["<<node[now].l<<" "<<node[now].r<<"]"<<endl;
	for (auto v:nvs[now]) printf("%d ",v);
	cout<<endl;
}

bool vis[100010];
int bac[100010],cnt[100010][2],cntmax,ans[100010];

void Upd(int now,int dr)
{
	// int& C=bac[seq[now]];
	
	// cnt[C][0]--; cnt[C][1]-=col[now];
    // C+=dr;
    // cnt[C][0]++; cnt[C][1]+=col[now];
	
	// if (dr==1) cntmax=max(cntmax,C);
	// else while (!cnt[cntmax]) cntmax--;
	
	/*for (int i=0;i<nvs[now].size();i++)
	{
		int col=nvs[now][i];
		int& C=bac[col];
		cnt[
	}*/
	
	
	for (int v=ptr[now];v;v=edge[v].pre)
		if (!vis[edge[v].to]) Upd(edge[v].to,dr);
}

void DFS2(int now,int keep)
{
	for (int v=ptr[now];v;v=edge[v].pre)
		if (edge[v].to!=hson[now]) DFS2(edge[v].to,0);
	
	if (hson[now])
	{
		DFS2(hson[now],1);
		vis[hson[now]]=1;
	}
	
	Upd(now,1);
	ans[now]=cntmax;
	vis[hson[now]]=0;
	if (!keep) Upd(now,-1);
}

set<int> mapx;
void Process(int now)
{
	for (int v=ptr[now];v;v=edge[v].pre) 
		Process(edge[v].to);
	
	set<int>::iterator iter;
	iter=mapx.lower_bound(node[now].l); 
//	if (iter!=mapx.end()) iter++;
	while (iter!=mapx.end() && (*iter)<=node[now].r)
	{
		nvs[now].push_back(*iter);
		set<int>::iterator tmp=iter++; 
		mapx.erase(tmp);
	}
}

int main()
{
	readx(n); readx(m);
	for (int i=1;i<=n;i++) readx(seq[i]);
	Unique();
	for (int i=1;i<=m;i++)
	{
		readx(node[i].l); readx(node[i].r);
		node[i].id=i;
	}
	m++; node[m].l=1; node[m].r=n; node[m].id=m;
	
	for (int i=1;i<=n;i++) mapx.insert(i);
	Build(); Process(m);
	DFS1(m,0);
	
	DFS2(1,1);
	for (int i=1;i<m;i++) printf("%d\n",ans[i]);
}
