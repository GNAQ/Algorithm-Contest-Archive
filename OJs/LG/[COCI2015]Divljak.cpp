#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
typedef long long ll;
using namespace std;

vector<int> edge[2001200];

// HLD
int tst=0, intim[2001200], outim[2001200];
int hson[2001200], topx[2001200];
int anc[2001200], siz[2001200], dep[2001200];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int lowbit(int x) { return x & (-x); }
void Is(int u, int v) { edge[u].push_back(v); }

struct _ACAM
{
	int fil, ch[27], val;
	bool is_end;
}ac[2001200];
int tsiz = 1;
int nodeid[2001200];

int n, q;
char s1[2001200], s2[2001200];

void Ins(char *wd, int id)
{
	int len = strlen(wd+1), u=1;
	
	for (int i=1;i<=len;i++) wd[i]=wd[i]-'a'+1;
	
	for (int i=1;i<=len;i++)
	{
		if (!ac[u].ch[wd[i]])
			ac[u].ch[wd[i]]=++tsiz;
		u = ac[u].ch[wd[i]];
	}
	ac[u].is_end = 1;
	nodeid[id]=u;
}

void GetFail()
{
	queue<int> que; int u = 1;
	
	for (int i=1;i<=26;i++)
	{
		if (ac[1].ch[i])
		{
			ac[ac[1].ch[i]].fil = 1;
			Is(1, ac[1].ch[i]);
			que.push(ac[1].ch[i]);
		}
		else
			ac[1].ch[i] = 1;
	}
	
	while (!que.empty())
	{
		u = que.front(); que.pop();
		
		for (int i=1;i<=26;i++)
		{
			int v = ac[u].ch[i];
			if (v)
			{
				ac[v].fil = ac[ac[u].fil].ch[i];
				Is(ac[v].fil, v);
				que.push(v);
			}
			else
				ac[u].ch[i] = ac[ac[u].fil].ch[i];
		}
	}
}

namespace BIT
{
	int v[4001010], lim;
	
	void Upd(int pos, int val)
	{
		while (pos <= lim)
		{
			v[pos]+=val;
			pos += lowbit(pos);
		}
	}
	
	int Qry(int pos)
	{
		int ret = 0;
		while (pos>0)
		{
			ret += v[pos];
			pos -= lowbit(pos);
		}
		return ret;
	}
};

// HLD
void DFS1(int u, int fa)
{
	siz[u] = 1; intim[u] = ++tst;
	anc[u] = fa; dep[u] = dep[fa] + 1;
	
	for (int i=0;i<edge[u].size();i++)
	{
		DFS1(edge[u][i], u);
		
		siz[u]+=siz[edge[u][i]];
		if (siz[edge[u][i]]>siz[hson[u]])
			hson[u]=edge[u][i];
	}
	
	outim[u] = ++tst;
}

void DFS2(int u, int src)
{
	topx[u] = src;
	if (hson[u]) 
		DFS2(hson[u], src);
	for (int i=0;i<edge[u].size();i++) 
		if (edge[u][i]!=hson[u])
			DFS2(edge[u][i], edge[u][i]);
}

int LCA(int u, int v)
{
	while (topx[u]!=topx[v])
	{
		if (dep[topx[u]]<dep[topx[v]]) swap(u, v);
		u = anc[topx[u]];
	}
	if (dep[u]<dep[v]) swap(u, v);
	return v;
}

bool cmp(const int &a, const int &b)
	{ return intim[a]<intim[b]; }

int tmp[2001200], vis[2001200];
void Qry(char *str, int timer)
{
	int len = strlen(str+1), u = 1, cnt = 0;
	for (int i=1;i<=len;i++) str[i]-='a'-1;
	
	for (int i=1;i<=len;i++) 
	{
		u = ac[u].ch[str[i]];
		if (vis[u]!=timer)
		{
			vis[u]=timer;
			tmp[++cnt] = u;
		}
	}
	
	sort(tmp+1, tmp+cnt+1, cmp);
	
	for (int i=1;i<=cnt;i++) 
		BIT::Upd(intim[ tmp[i] ], 1);
	for (int i=1;i<cnt;i++)
		BIT::Upd(intim[ LCA(tmp[i], tmp[i+1]) ], -1);
}

int main()
{
	readx(n);
	for (int i=1;i<=n;i++)
	{
		scanf("%s", s1+1);
		Ins(s1, i);
	}
	
	GetFail();
	DFS1(1, 0); DFS2(1, 1);
	BIT::lim = 2 * tsiz;
	
	readx(q); int op;
	while (q--)
	{
		readx(op);
		if (op == 1)
		{
			scanf("%s", s2+1);
			Qry(s2, q);
		}
		else
		{
			int x; readx(x); 
			int ans = BIT::Qry(outim[nodeid[x]]) - BIT::Qry(intim[nodeid[x]] - 1);
			printf("%d\n", ans);
		}
	}
	return 0;
}