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
#include<map>
#include<set>
#define ll long long
#define REG register
using namespace std;

struct ed { int pre,to,w; } edge[50010];
int at=1,ptr[1010];
int n,m;

int dis[1010][1010],path[1010][1010];
ll ans[1010];

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int& fx,int& tx,int& wx)
{
	at++;
	edge[at].pre=ptr[fx];
	edge[at].to=tx;
	edge[at].w=wx;
	ptr[fx]=at;
}

namespace DIS
{
	bool vis[1010];
	deque<int> que;
	void BFS(int ss)
	{
		que.push_back(ss); static int cac;
		memset(vis,0,sizeof vis);
		dis[ss][ss]=0; path[ss][ss]=1;
		
		while (!que.empty())
		{
			cac=que.front(); que.pop_front();
			if (vis[cac]) continue;
			vis[cac]=1;
			for (REG int v=ptr[cac];v;v=edge[v].pre)
			{
				if (dis[ss][edge[v].to]==dis[ss][cac]+edge[v].w)
					path[ss][edge[v].to]++;
				
				if (dis[ss][edge[v].to]>dis[ss][cac]+edge[v].w)
				{
					dis[ss][edge[v].to]=dis[ss][cac]+edge[v].w;
					path[ss][edge[v].to]=1;
					if (edge[v].w)
						que.push_back(edge[v].to);
					else
						que.push_front(edge[v].to);
				}
			}
		}
	}
};

int main()
{
	memset(dis,0x3f,sizeof dis);
	readx(n); readx(m); int fx,tx,wx;
	for (int i=1;i<=m;i++)
	{
		readx(fx); readx(tx); readx(wx);
		Is(fx,tx,wx);
	}
	
	for (REG int i=1;i<=n;i++) DIS::BFS(i);
	
	// for (int i=1;i<=n;i++)
	// 	for (int j=1;j<=n;j++)
	// 		printf("%d%c",dis[i][j]<dis[0][0]?dis[i][j]:-1," \n"[j==n]);
	// for (int i=1;i<=n;i++)
	// 	for (int j=1;j<=n;j++)
	// 		printf("%d%c",path[i][j]," \n"[j==n]);
	// cout<<endl<<endl;
	
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			for (int k=1;k<=n;k++) 
				if (dis[j][i]+dis[i][k]==dis[j][k])
					ans[i]+=1LL*path[j][i]*path[i][k];
	
	for (int i=1;i<=n;i++) printf("%lld\n",ans[i]);
}