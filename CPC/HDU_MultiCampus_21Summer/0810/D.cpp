#pragma GCC optimize(3)
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

struct ed
{
	int pre, to;
}edge[200010];
int ptr[100010], at;

int n, f[100010];

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
	edge[at].pre = ptr[u];
	edge[at].to = v;
	ptr[u]=at;
}

int dfn[100010], low[100010], tcnt, stk[100010], hd;
bool inst[100010];

int sccid, bel[100010], sccnum[100010];
ll sccsum[100010];

void Tarjan(int u)
{
	dfn[u]=low[u]=++tcnt;
	stk[++hd]=u; inst[u]=1;
	
	for (int v = ptr[u]; v; v=edge[v].pre)
	{
		if (!dfn[edge[v].to])
		{
			Tarjan(edge[v].to);
			low[u]=min(low[edge[v].to], low[u]);
		}
		else if (inst[edge[v].to]) low[u]=min(low[u], dfn[edge[v].to]);
	}
	
	if (dfn[u]==low[u])
	{
		sccid++;
		int cac;
		do
		{
			cac = stk[hd--];
			bel[cac]=sccid;
			sccnum[sccid]++;
			inst[cac]=0;
		} while (cac!=u);
	}
}

void Solve()
{
	readx(n);
	for (int i=1;i<=n;i++)
	{
		readx(f[i]);
		Is(i, f[i]);
	}
	
	for (int i=1;i<=n;i++) 
		if (!dfn[i]) Tarjan(i);
	
	for (int i=1;i<=n;i++)
	{
		// cout << "!!" << bel[i] << endl;
		if (bel[i]==bel[f[i]])
		{
			// cout << "#" << i << endl;
			sccsum[bel[i]]+=i;
		}
	}
	
	// for (int i=1;i<=n;i++) cout << sccnum[i] << " " << sccsum[i] << endl;
	
	int i = 1; ll stdsum, stdcnt;
	while (!sccsum[i]) i++;
	stdsum=sccsum[i]; stdcnt=sccnum[i];
	
	for (int j=i+1;j<=sccid;j++) if (sccsum[j])
	{
		if (1LL * sccsum[j] * stdcnt != 1LL * stdsum * sccnum[j])
		{
			cout << "NO" << endl;
			return;
		}
	}
	cout << "YES" << endl;
	return;
}

void Clear()
{
	for (int i=1;i<=n;i++)
	{
		dfn[i]=low[i]=stk[i]=0;
		sccnum[i]=sccsum[i]=0;
		bel[i]=inst[i]=0;
		ptr[i]=0;
	}
	at = 0;
	hd = sccid = tcnt = 0;
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		Solve();
		Clear();
	}
}