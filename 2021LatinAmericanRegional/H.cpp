#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n,m;
struct ed
{
	int pre,to;
	ll cap;
}edge[200010];
int at=1,ptr[100010];
int ss,tt;

const int inf = 1e8;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int fx,int tx,ll cx)
{
	edge[++at].pre=ptr[fx];
	edge[at].to=tx;
	edge[at].cap=cx;
	ptr[fx]=at;
	edge[++at].pre=ptr[tx];
	edge[at].to=fx;
	ptr[tx]=at;
}

int lvl[100010],cac1,cur[100010];
queue<int> que;
int BFS()
{
	memset(lvl,0,sizeof lvl); lvl[ss]=1; que.push(ss);
	while (!que.empty())
	{
		cac1=que.front(); que.pop();
		for (int e=ptr[cac1];e;e=edge[e].pre) if (!lvl[edge[e].to] && edge[e].cap)
		{
			lvl[edge[e].to]=lvl[cac1]+1;
			que.push(edge[e].to);
		}
	}
	if (!lvl[tt]) return false;
	memcpy(cur,ptr,sizeof cur);
	return true;
}

ll DFS(int now,ll minf)
{
	if (!minf || now==tt) return minf;
	ll needf,sumf=0;
	for (int e=cur[now];e;e=edge[e].pre) if (lvl[edge[e].to]==lvl[now]+1)
	{
		cur[now]=e;
		if ((needf=DFS(edge[e].to,min(minf,edge[e].cap))))
		{
			sumf+=needf; minf-=needf;
			edge[e].cap-=needf; edge[e^1].cap+=needf;
			if (!minf) break;
		}
	}
	return sumf;
}

int main()
{
	readx(n); int v;
	ss = n + 1; tt = n + 2;
	for (int i=1;i<=n;i++)
	{
		char ss[10];
		scanf("%s", ss);
		if (ss[0] == '*') 
		{
			readx(v);
			if (v == 1) v = tt;
			Is(i, v, inf);
		}
		else
		{
			int k = atoi(ss);
			for (int j=1;j<=k;j++)
			{
				readx(v);
				if (v == 1) v = tt;
				Is(i, v, 1);
			}
		}
	}
	Is(ss, 1, inf);
	
	ll ans=0;
	while (BFS()) ans+=DFS(ss,2*1e9);
	ans++;
	if (ans > inf)
		puts("*");
	else
		printf("%lld\n", ans);
	return 0;
}