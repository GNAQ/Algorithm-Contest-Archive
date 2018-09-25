#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;

int graph[5000][5000],marker[5000]={0},enfp[5000]={0};
int edgenum,bp,ep,counter=0,maxe=-1,mine=9999;
bool flag=false;

void go(int point)
{
	for (int i=mine;i<=maxe;i++)
	{
		if (graph[point][i]>0)
		{
			graph[point][i]--; graph[i][point]--;
			go(i);
		}
	}
	marker[counter]=point;
	counter++;
	return;
}

int main()
{
	memset(graph,0,sizeof(graph));
	scanf("%d",&edgenum);
	for (int i=1;i<=edgenum;i++)
	{
		scanf("%d%d",&bp,&ep);
		graph[bp][ep]++;
		graph[ep][bp]++;
		enfp[ep]++; enfp[bp]++;
		if (bp>maxe) maxe=bp;
		if (ep>maxe) maxe=ep;
		if (bp<mine) mine=bp;
		if (ep<mine) mine=ep;
	}
	for (int i=mine;i<=maxe;i++)
	{
		if (enfp[i]%2==1)
		{
			go(i);
			flag=true;
			break;
		}
	}
	if (flag==false) go(1);
	for (int i=counter-1;i>=0;i--) printf("%d\n",marker[i]);
	return 0;
}
