#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<iterator>
#include<cstdlib>
#include<queue>
using namespace std;

struct ed
{
	int pre,to,capx;
}edge[400010]={0}
int nodenum,edgenum,cx,fx,tx,at=1,pointer[100010]={0},sx,ex;

queue<int> que;
int ag[100010]={0},ans=0,former[100010]={0},prex,cache1;

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
	edge[at].pre=pointer[fx];
	edge[at].to=tx;
	edge[at].capx=cx;
	pointer[fx]=at;
	at++;
	edge[at].pre=pointer[tx];
	edge[at].to=fx;
	edge[at].capx=0;
	pointer[tx]=at;
}

inline void Max_Flow()
{
	while (1)
	{
		memset(ag,0,sizeof(ag));
		que.push(sx); ag[sx]=2*1e9;
		while (!que.empty())
		{
			cache1=que.front(); que.pop();
			prex=pointer[cache1];
			
			while (prex)
			{
				if ((!ag[edge[prex].to]) && edge[prex].capx)
				{
					former[edge[prex].to]=prex;
					ag[edge[prex].to]=min(ag[cache1],edge[prex].capx);
					que.push(edge[prex].to);
				}
				prex=edge[prex].pre;
			}
			if (ag[ex])
			{
				while (!que.empty()) que.pop();
				break;
			}
		}
		if (!ag[ex]) break;
		ans+=ag[ex];
		cache1=ex;
		while (former[cache1])
		{
			edge[former[cache1]].capx-=ag[ex];
			edge[(former[cache1]^1)].capx+=ag[ex];
			cache1=edge[(former[cache1]^1)].to;
		}
	}
}

int main()
{
	readx(nodenum); readx(edgenum); readx(sx); readx(ex);
	for (int i=1;i<=edgenum;i++)
	{
		readx(fx); readx(tx); readx(cx);
		Insert();
	}
	Max_Flow();
	printf("%d\n",ans);
	return 0;
}
