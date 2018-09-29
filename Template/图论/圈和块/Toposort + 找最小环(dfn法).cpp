#include<iostream>
#include<cstring>
#include<cmath>
#include<string>
#include<cstdio>
#include<queue>
#include<algorithm>
#include<iterator>
using namespace std;

int nodenum,tstamp=0,ans=0;
int to[200010]={0},dfn[200010]={0},inw[200010]={0};
bool can[200010];

void go(int nownode)
{
	dfn[nownode]=++tstamp;
	can[nownode]=false;
	if (!dfn[to[nownode]]) go(to[nownode]);
	else ans=min(ans,dfn[nownode]-dfn[to[nownode]]+1);
	return;
}

void toposort()
{
	queue<int> que;
	int cache1,cache2,cache3;
	
	for (int i=1;i<=nodenum;i++)
	{
		if (inw[i]==0) 
		{
			que.push(i);
		}
	}
	while (!que.empty())
	{
		cache1=que.front(); que.pop();
		can[cache1]=false; inw[to[cache1]]--;
		if (can[to[cache1]] && !inw[to[cache1]])
		{
			que.push(to[cache1]);
		}
	}
//	for (int i=1;i<=nodenum;i++) printf("%d ",can[i]);
//	printf("\n");
}

int main()
{
	scanf("%d",&nodenum);
	ans=10923843;
	for (int i=1;i<=nodenum;i++)
	{
		scanf("%d",&to[i]);
		inw[to[i]]++;
	}
	
	fill(can,can+nodenum,1);
	toposort();

	for (int i=1;i<=nodenum;i++)
	{
		if (can[i]) 
		{
			tstamp=0;
			memset(dfn,0,sizeof(dfn));
			go(i);
		}
	}
	printf("%d\n",ans);
	
	return 0;
}
