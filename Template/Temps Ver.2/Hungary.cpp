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

struct ed { int pre,to; } edge[2000010];
int at=1,ptr[100010];

int n,m,edgenum,ans;

template<typename inp_t>
void readx(inp_t& x)
{
	x=0; int k=1; char ch=0;
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

int vis[100010],match[100010];
bool Hungary(int now,int src)
{
	for (int v=ptr[now];v;v=edge[v].pre) if (vis[edge[v].to]!=src)
	{
		vis[edge[v].to]=src;
		if (!match[edge[v].to] || Hungary(match[edge[v].to],src)) { match[edge[v].to]=now; return true; }
	}
	return false;
}


int main()
{
	readx(n); readx(m); readx(edgenum); int fx,tx;
	for (int i=1;i<=edgenum;i++)
	{
		readx(fx); readx(tx);
		if (fx<1 || tx<1 || fx>n || tx>m) continue;
		tx+=n; Is(fx,tx);
	}
	
	for (int i=1;i<=n;i++) ans+=Hungary(i,i);
	printf("%d\n",ans);
}