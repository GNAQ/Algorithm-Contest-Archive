#include<cstdio>
#include<cmath>
#include<iostream>
#include<iterator>
#include<cstring>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<queue>
#include<vector>
using namespace std;

struct ed { int pre,to,capx; } edge[220010]={0};
int nodenum,edgenum,ss,tt,at=1,ptr[100010]={0},fx,tx,cx;

queue<int> que;
int level[100010]={0},cac,cur[100010]={0};

int ansf;

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
	ptr[fx]=at;
	at++;
	edge[at].pre=ptr[tx];
	edge[at].to=fx;
	ptr[tx]=at;
}

inline int BFS()
{
	memset(level,0,sizeof(level));
	level[ss]=1; que.push(ss);
	while (!que.empty())
	{
		cac=que.front(); que.pop();
		for (int prex=ptr[cac];prex;prex=edge[prex].pre)
			if ((!level[edge[prex].to]) && edge[prex].capx)
			{
				level[edge[prex].to]=level[cac]+1;
				que.push(edge[prex].to);
			}
	}
	return level[tt];
}
inline int DFS(int now,int minf)
{
	if ((!minf) || now==tt) return minf;
	int sumf=0,needf;
	for (int prex=cur[now];prex;prex=edge[prex].pre)
	{
		cur[now]=prex;
		if (level[edge[prex].to]==level[now]+1)
			if (needf=DFS(edge[prex].to,min(minf,edge[prex].capx)))
			{
				sumf+=needf; minf-=needf;
				edge[prex].capx-=needf; edge[prex^1].capx+=needf;
				if (!minf) break;
			}
	}
	return sumf;
}

int main()
{
	readx(nodenum); readx(edgenum); readx(ss); readx(tt);
	for (int i=1;i<=edgenum;i++)
	{
		readx(fx); readx(tx); readx(cx);
		Insert();
	}
	
	while (BFS())
	{
		for (int i=1;i<=nodenum;i++) cur[i]=ptr[i];
		ansf+=DFS(ss,2*1e9);
	}
	printf("%d\n",ansf);
	return 0;
}
