#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<string>
#include<iterator>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
#include<set>
typedef long long ll;
using namespace std;

struct ed
{
	int pre,to,capx;
}edge[200010];
int at=1,ptr[100010];



template<typename inp_t>
void readx(inp_t& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int fx,int tx,int cx)
{
	at++;
	edge[at].pre=ptr[fx];
	edge[at].to=tx;
	edge[at].capx=cx;
	ptr[fx]=at;
	at++;
	edge[at].pre=ptr[tx];
	edge[at].to=fx;
	edge[at].capx=0;
	ptr[tx]=at;
}

namespace SAP // ISAP
{
	int gap[100010],dis[100010];
	int cur[100010],aug[100010];
	ll totflow; int ss,tt;
	
	queue<int> que;
	void BFS()
	{
		for (int i=ss;i<=tt;i++) dis[i]=tt-ss;
		dis[tt]=0; for (int i=ss;i<=tt;i++) cur[i]=ptr[i];
		que.push(tt); int cac;
		while (!que.empty())
		{
			cac=que.front(); que.pop(); 
			for (int v=ptr[cac];v;v=edge[v].pre)
				if (edge[v^1].capx && dis[edge[v].to]==tt-ss)
				{
					dis[edge[v].to]=dis[cac]+1;
					que.push(edge[v].to);
				}
		}
	}
	
	int Aug()
	{
		int now=tt,ret=2*1e9;
		while (now!=ss)
		{
			ret=min(ret,edge[aug[now]].capx);
			now=edge[aug[now]^1].to;
		}
		now=tt;
		while (now!=ss)
		{
			edge[aug[now]].capx-=ret;
			edge[aug[now]^1].capx+=ret;
			now=edge[aug[now]^1].to;
		}
		return ret;
	}
	
	void ISAP()
	{
		totflow=0; BFS(); memset(gap,0,sizeof gap);
		for (int i=ss;i<=tt;i++) gap[dis[i]]++;
		
		int now=ss;
		while (dis[ss]<(tt-ss))
		{
			if (now==tt) { totflow+=Aug(); now=ss; }
			
			bool can=false;
			for (int v=cur[now];v;v=edge[v].pre)
				if (edge[v].capx && dis[edge[v].to]+1==dis[now])
				{
					can=true; cur[now]=v;
					aug[edge[v].to]=v; now=edge[v].to;
					break;
				}
			
			if (!can)
			{
				if (!(--gap[dis[now]])) break; 
				
				int min_d=(tt-ss)-1;
				for (int v=ptr[now];v;v=edge[v].pre)
					if (edge[v].capx) min_d=min(min_d,dis[edge[v].to]);
				
				dis[now]=min_d+1;
				++gap[dis[now]]; cur[now]=ptr[now];
				if (now!=ss) now=edge[aug[now]^1].to;
			}
		}
	}
};

int main()
{
	
	
	
}