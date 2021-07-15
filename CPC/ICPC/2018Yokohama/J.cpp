#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
typedef long long ll;
using namespace std;

struct _Node
{
	int id, dfn, c;
	bool operator < (const _Node &b) const
		{ return this->dfn < b.dfn; }
} node[100010];

int n, m;
int anc[100010][18], dep[100010], dfn[100010], tst;

struct ed
{
	int pre, to;
}edge[200010];
int at, ptr[100010];

set<_Node> col[100010];
int ans[100010];

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

void DFS(int u, int fa)
{
	dfn[u]=node[u].dfn = ++tst;
	dep[u]=dep[fa]+1;
	
	anc[u][0]=fa;
	for (int i=1;i<=17;i++) anc[u][i]=anc[anc[u][i-1]][i-1];
	
	for (int v=ptr[u];v;v=edge[v].pre)
		if (edge[v].to!=fa)
			DFS(edge[v].to, u);
}

int LCA(int u, int v)
{
	if (dep[u]<dep[v]) swap(u, v);
	for (int i=17;i>=0;i--) if (dep[anc[u][i]]>=dep[v]) u=anc[u][i];
	if (u==v) return v;
	for (int i=17;i>=0;i--) if (anc[u][i]!=anc[v][i])
	{
		u=anc[u][i];
		v=anc[v][i];
	}
	return anc[v][0];
}

int Dis(int u, int v)
{
	return dep[u]+dep[v]-2*dep[LCA(u, v)];
}

void Ins(int u)
{
	set<_Node> &st = col[node[u].c];
	auto ret = st.insert(node[u]);
	auto iter = ret.first;
	
	int l=0, r=0;
	iter++;
	if (iter != st.end())
	{
		r = (*iter).id;
	}
	iter--;
	if (iter != st.begin())
	{
		iter--;
		l = (*iter).id;
	}
	
	// printf("Ins %d with l = %d, r = %d\n", u, l, r);
	
	if (l && r) ans[node[u].c]-=Dis(l, r);
	if (l) ans[node[u].c]+=Dis(l, u);
	if (r) ans[node[u].c]+=Dis(u, r);
}

void Del(int u)
{
	set<_Node> &st = col[node[u].c];
	auto iter = st.find(node[u]);
	
	int l=0, r=0;
	iter++;
	if (iter != st.end())
	{
		r = (*iter).id;
	}
	iter--;
	if (iter != st.begin())
	{
		iter--;
		l = (*iter).id;
	}
	
	if (l && r) ans[node[u].c]+=Dis(l, r);
	if (l) ans[node[u].c]-=Dis(l, u);
	if (r) ans[node[u].c]-=Dis(u, r);
	
	// printf("Del %d with l = %d, r = %d\n", u, l, r);
	
	st.erase(node[u]);
}

int main()
{
	readx(n); int u, v;
	for (int i=1;i<n;i++)
	{
		readx(u); readx(v);
		Is(u, v); Is(v, u);
	}
	for (int i=1;i<=n;i++)
	{
		readx(node[i].c);
		node[i].id = i;
	}
	DFS(1, 0);
	
	for (int i=1;i<=n;i++) Ins(i);
	
	readx(m);
	for (int i=1;i<=m;i++)
	{
		char op;
		scanf("\n%c%d", &op, &u);
		
		if (op=='U')
		{
			scanf("%d", &v);
			Del(u);
			node[u].c = v;
			Ins(u);
		}
		else
		{
			if (col[u].empty())
				puts("-1");
			else
			{
				int fst, lst;
				fst = col[u].begin()->id;
				lst = col[u].rbegin()->id;
				printf("%d\n", (ans[u]+Dis(lst, fst))/2);
			}
		}
	}
	
	return 0;
}

/*
题解

考虑按 DFS 序排序后维护点的序列

记相邻的两个点为 L, R 则每个点的贡献是

Dis(L, X) + DIS(X, R) - DIS(L, R)

容易发现这样每个 X 对答案的贡献是双倍的，但是左右两侧插入的点只有一次

所以最后要再加上 DIS(L_MOST, R_MOST)

删除时反转过程即可。
*/