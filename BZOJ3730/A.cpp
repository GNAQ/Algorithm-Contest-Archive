#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
typedef long long ll;
using namespace std;

struct ed
{
	int pre, to;
}edge[200010];
int at, ptr[100010], n, m, nnv[100010]; // node value

// NodeDiv Tree
int dep[100010], tsiz[100010], msiz[100010], dsiz[100010];
int hr, subsiz; 
bool vis[100100];
// vector<int> e2[100010]; 这道题目只需要记录父亲
int tfa[100010];

// LCA Dis Calc
int l[100010][20];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int u, int v)
{
	at++; 
	edge[at].pre=ptr[u];
	edge[at].to=v;
	ptr[u]=at;
}

void Init_DFS(int u, int fa)
{
	
	dep[u]=dep[fa]+1;
	l[u][0]=fa;

	for (int i=1;i<=17;i++) 
		l[u][i]=l[l[u][i-1]][i-1];
	
	for (int v=ptr[u];v;v=edge[v].pre)
		if (edge[v].to!=fa) Init_DFS(edge[v].to, u);
}

int LCA(int u, int v)
{
	if (dep[u]<dep[v]) swap(u, v);
	for (int i=17;i>=0;i--) if (dep[l[u][i]]>=dep[v]) u=l[u][i];
	if (u==v) return v;
	for (int i=17;i>=0;i--) if (l[u][i]!=l[v][i])
	{
		u=l[u][i];
		v=l[v][i];
	}
	return l[v][0];
}

int GetDis(int u, int v)
{
	return dep[u]+dep[v]-2*dep[LCA(u, v)];
}

namespace BIT
{
	vector<int> S1[100010], S2[100010];
	
	void Init(vector<int> &S, int siz)
	{
		for (int i=0;i<=siz+2;i++) 
			S.push_back(0);
	}
	
	void Add(vector<int> &S, int pos, int val)
	{
		while (pos<S.size())
		{
			S[pos]+=val;
			pos+=(pos&(-pos));
		}
	}
	int Qry(vector<int> &S, int pos)
	{
		int ret = 0;
		if (pos>=S.size()) 
		{
			cout << "!!" << endl;
			pos=S.size()-1;
		}
		while (pos)
		{
			ret+=S[pos];
			pos-=(pos&(-pos));
		}
		return ret;
	}
}

namespace NDiv
{
	void GetRt(int u, int fa)
	{
		tsiz[u]=1; msiz[u]=0;
		for (int v=ptr[u];v;v=edge[v].pre) 
			if (edge[v].to!=fa && !vis[edge[v].to])
			{
				GetRt(edge[v].to, u);
				tsiz[u]+=tsiz[edge[v].to];
				msiz[u]=max(msiz[u], tsiz[edge[v].to]);
			}
		msiz[u]=max(msiz[u], subsiz-tsiz[u]);
		if (msiz[u]<msiz[hr]) hr=u;
	}
	
	void BuildTree(int u, int totn)
	{
		vis[u]=1; dsiz[u]=totn;
		BIT::Init(BIT::S1[u], totn); BIT::Init(BIT::S2[u], totn);
		// cerr << "Init " << u << " as " << totn << endl;
		for (int v=ptr[u];v;v=edge[v].pre) if (!vis[edge[v].to])
		{
			subsiz = tsiz[edge[v].to];
			if (subsiz>tsiz[u]) subsiz = totn - tsiz[u];
			msiz[hr=0]=1e9;
			GetRt(edge[v].to, 0);
			tfa[hr]=u; // Record
			BuildTree(hr, subsiz);
		}
	}
}

void Update(int x, int val)
{
	int u = x;
	while (u)
	{
		int fa = tfa[u]; 
		BIT::Add(BIT::S1[u], GetDis(u, x)+1, val); // 这里 +1 是为了防止 0 下标
		if (fa) BIT::Add(BIT::S2[fa], GetDis(fa, x)+1, val);
		u=fa;
	}
}

int Qry(int x, int k)
{
	int ret = 0;
	int u = x, lst = 0;
	while (u)
	{
		int dis = GetDis(u, x);
		cout << "!!" << dis << endl;
		if (dis<=k)
		{
			ret += BIT::Qry(BIT::S1[u], k-dis+1);
			cout << "#" << ret << " " << k-dis << endl;
			cout << dsiz[u] << endl;
			if (lst) ret -= BIT::Qry(BIT::S2[lst], k-dis+1);
		} 
		lst=u; u=tfa[u];
	}
	return ret;
}

int main()
{
	readx(n); readx(m); int u, v;
	for (int i=1;i<=n;i++) readx(nnv[i]);
	for (int i=1;i<n;i++)
	{
		readx(u); readx(v);
		Is(u, v); Is(v, u);
	}
	
	Init_DFS(1, 0);
	
	subsiz = n;
	msiz[hr=0]=1e9;
	NDiv::GetRt(1, 0);
	NDiv::BuildTree(hr, n);
	
	for (int i=1;i<=n;i++) Update(i, nnv[i]);
	
	int op = 0, ans = 0;
	for (int i=1;i<=m;i++)
	{
		readx(op); readx(u); readx(v);
		u^=ans; v^=ans;
		if (op==0)
		{
			// printf("%d\n", ans=Qry(u, v));
			printf("%d\n", Qry(u, v));
		}
		else
		{
			Update(u, v-nnv[u]);
			nnv[u]=v;
		}
		if (i==2) return 0;
	}
	return 0;
}