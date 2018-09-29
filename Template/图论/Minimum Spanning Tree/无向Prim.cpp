#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
using namespace std;

struct edge
{
	int pre,to,w;
}edge[100010]={0};
int pointer[10010]={0},edgenum,nodenum,fx,tx,wx;
//Prim MST
int mindis[10010]={0},prex,mst=0,wpoint,cache1;//mindis:任意Wpoint与Bpoint[]相连的最短边 mst:最小生成树边权总和 wpoint记录每次搜到的蓝点 
bool vis[10010]={false};//Blue node or white node

void Insert(int at,int fromx,int tox,int weight)
{
	edge[at].pre=pointer[fromx];
	edge[at].to=tox;
	edge[at].w=weight;
	pointer[fromx]=at;
	return;
}

int main()
{
	memset(mindis,0x3f,sizeof(mindis)); mindis[1]=0;
	scanf("%d%d",&nodenum,&edgenum);
	for (int i=1;i<=edgenum*2;i+=2)
	{
		scanf("%d%d%d",&fx,&tx,&wx);
		Insert(i,fx,tx,wx);
		Insert(i+1,tx,fx,wx);
	}
	//Prim MST
	for (int i=1;i<=nodenum;i++)
	{
		cache1=0x3f; wpoint=0;
		for (int j=1;j<=nodenum;j++)//Find a blue point which has a minimize distance
		{
			if (mindis[i]<cache1 && vis[i]==false)
			{
				cache1=mindis[i];
				wpoint=i;
			}
		}
		vis[wpoint]=true;//into WPoint
		mst+=mindis[wpoint];//Record MST
		prex=pointer[wpoint];//update MinDis
		while (prex>0)
		{
			if (edge[prex].w<mindis[edge[prex].to])
			{
				mindis[edge[prex].to]=edge[prex].w;
			}
			prex=edge[prex].pre;
		}
	}
	printf("%d\n",mst);
	return 0;
}
