#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<iterator>
#include<queue>
#include<vector>
#include<map>
#include<set>
using namespace std;
typedef long long ll;
typedef ostream_iterator<int> os_iter_int;

struct ed { int pre,to,w; } edge[200010];
int at=1,ptr[200010];

int n,m,dis[200010],ss;

template<typename inp_t>
void readx(inp_t& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int fx,int tx,int wx)
{
	at++;
	edge[at].pre=ptr[fx];
	edge[at].to=tx;
	edge[at].w=wx;
	ptr[fx]=at;
}

struct Node
{
	int dis,id;
	bool operator < (const Node& B) const { return B.dis<dis; }
};
priority_queue<Node> que;
bool vis[200010];

void Dijkstra()
{
	Node cac1,cac2;
	memset(dis,0x3f,sizeof dis);
	dis[ss]=0; cac1.id=ss; cac1.dis=0;
	que.push(cac1); // vis[cac1.id]=1;
	while (!que.empty())
	{
		cac1=que.top(); que.pop();
		if (vis[cac1.id]) continue;
		vis[cac1.id]=1;
		for (int v=ptr[cac1.id];v;v=edge[v].pre)
			if (dis[edge[v].to]>dis[cac1.id]+edge[v].w)
			{
				dis[edge[v].to]=dis[cac1.id]+edge[v].w;
				cac2.id=edge[v].to; cac2.dis=dis[cac2.id];
				que.push(cac2);
			}
	}
}

int main()
{
	readx(n); readx(m); readx(ss); int fx,tx,wx;
	for (int i=1;i<=m;i++)
	{
		readx(fx); readx(tx); readx(wx);
		Is(fx,tx,wx);
	}
	
	Dijkstra();
	for (int i=1;i<=n;i++) printf("%d%c",dis[i]," \n"[i==n]);
	
}