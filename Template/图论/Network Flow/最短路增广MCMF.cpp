#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<string>
#include<cstdlib>
#include<queue>
#include<vector>
using namespace std;

struct ed { int pre,to,capx,cost; } edge[200010]={0};
int nodenum,edgenum,at=1,ptr[100010]={0},fx,tx,cx,wx,ss,tt;

queue<int> que;
int dc[100010]={0},former[100010]={0},ag[100010]={0};
bool vis[100010]={0};
int ansc=0,ansf=0;


inline void readx(int& x)
{
	x=0; int k=1; register char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

inline void Insert()
{
	at++;
	edge[at].pre=ptr[fx];
	edge[at].to=tx;
	edge[at].capx=cx;
	edge[at].cost=wx;
	ptr[fx]=at;
	at++;
	edge[at].pre=ptr[tx];
	edge[at].to=fx;
	edge[at].cost=-wx;
	ptr[tx]=at;
}

inline bool MinCostMaxFlow()
{
	register int prex,cache;
	memset(dc,0x3f,sizeof(dc));
	dc[ss]=0; que.push(ss); ag[ss]=2*1e9;
	
	while (!que.empty())
	{
		cache=que.front(); que.pop(); vis[cache]=false;
		for (prex=ptr[cache];prex;prex=edge[prex].pre)
			if (dc[edge[prex].to]>dc[cache]+edge[prex].cost && edge[prex].capx)
			{
				dc[edge[prex].to]=dc[cache]+edge[prex].cost;
				ag[edge[prex].to]=min(ag[cache],edge[prex].capx);
				former[edge[prex].to]=prex;
				if (!vis[edge[prex].to])
				{
					vis[edge[prex].to]=true;
					que.push(edge[prex].to);
				}
			}
	}
	if (dc[tt]==dc[nodenum+6]) return false;
	
	ansf+=ag[tt]; ansc+=ag[tt]*dc[tt]; cache=former[tt];
	while (cache)
	{
		edge[cache].capx-=ag[tt];
		edge[cache^1].capx+=ag[tt];
		cache=former[edge[cache^1].to];
	}
	return true;
}

int main()
{
	readx(nodenum); readx(edgenum); readx(ss); readx(tt);
	for (int i=1;i<=edgenum;i++)
	{
		readx(fx); readx(tx); readx(cx); readx(wx);
		Insert();
	}
	while (MinCostMaxFlow());
	printf("%d %d\n",ansf,ansc);
	return 0;
}
