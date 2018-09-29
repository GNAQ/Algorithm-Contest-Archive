#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
using namespace std;

int main()
{
	int dis[710][710],edgenum,f,t,w;
	memset(dis,0x3f,sizeof(dis));
	scanf("%d",&edgenum);
	for (int i=1;i<=edgenum;i++)
	{
		scanf("%d%d%d",&f,&t,&w);
		dis[f][t]=dis[t][f]=w;
	}
	//Floyd
	for (int k=1;k<100;k++)
	{
		for (int i=1;i<100;i++)
		{
			for (int j=1;j<100;j++)
			{
				if (dis[i][j]>dis[i][k]+dis[k][j])
				{
					dis[i][j]=dis[i][k]+dis[k][j];
				}
			}
		}
	}
	printf("\nNow enter the number of edges you want to look up:\n");
	int m;
	scanf("%d",&m);
	for (int i=0;i<m;i++)
	{
		scanf("%d%d",&f,&t);
		printf("%d\n",dis[f][t]);
	}
	return 0;
}
