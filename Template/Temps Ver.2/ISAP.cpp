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
using namespace std;
typedef long long ll;
typedef ostream_iterator<int> os_iter_int;

struct ed
{
	int pre,to,cap;
}edge[400010];
int at=1,ptr[100010];
int ss,tt,n,m;
ll totflow;


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
    edge[++at].pre=ptr[fx];
    edge[at].to=tx;
    edge[at].cap=cx;
    ptr[fx]=at;
    edge[++at].pre=ptr[tx];
    edge[at].to=fx;
	edge[at].cap=0;
    ptr[tx]=at;
}

namespace ISAP
{
	int gap[100010],cur[100010],dis[100010],aug[100010];
	queue<int> que;
	void BFS(int lim)
	{
		for (int i=1;i<=n;i++) dis[i]=lim;
		dis[tt]=0; que.push(tt); int cac;
		memcpy(cur,ptr,sizeof cur);
		while (!que.empty())
		{
			cac=que.front(); que.pop();
			for (int v=ptr[cac];v;v=edge[v].pre)
				if (edge[v^1].cap && dis[edge[v].to]==lim)
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
			ret=min(ret,edge[aug[now]].cap);
			now=edge[aug[now]^1].to;
		}
		now=tt;
		while (now!=ss)
		{
			edge[aug[now]].cap-=ret;
			edge[aug[now]^1].cap+=ret;
			now=edge[aug[now]^1].to;
		}
		return ret;
	}
	
	void ISAP(int lim)
	{
		totflow=0; BFS(lim);
		for (int i=1;i<=n;i++) gap[dis[i]]++;
		
		int now=ss;
		while (dis[ss]!=lim)
		{
			if (now==tt) { totflow+=Aug(); now=ss; }
			
			bool can=false;
			for (int v=cur[now];v;v=edge[v].pre)
				if (edge[v].cap && dis[edge[v].to]+1==dis[now])
				{
					can=true; cur[now]=v;
					aug[edge[v].to]=v; now=edge[v].to;
					break;
				}
			
			if (!can)
			{
				if (!(--gap[dis[now]])) break;
				int min_d=lim-1;
				for (int v=ptr[now];v;v=edge[v].pre)
					if (edge[v].cap) min_d=min(min_d,dis[edge[v].to]);
				dis[now]=min_d+1;
				gap[dis[now]]++;
				cur[now]=ptr[now];
				if (now!=ss) now=edge[aug[now]^1].to;
			}
		}
	}
};

int main()
{
	readx(n); readx(m); readx(ss); readx(tt); int fx,tx,cx;
    for (int i=1;i<=m;i++)
    {
        readx(fx); readx(tx); readx(cx);
        Is(fx,tx,cx);
    }
    
    
    ISAP::ISAP(n);
    cout<<totflow<<endl;
	
	
}