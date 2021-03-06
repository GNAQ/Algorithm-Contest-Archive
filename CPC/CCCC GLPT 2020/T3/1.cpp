#include<cstring>
#include<cstdio>
#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<queue>
#include<map>
typedef long long ll;
using namespace std;

struct ed
{
	int pre,to;
} edge[1000010];
int at=0,ptr[100010];

int n,m;
int dp[10010];
int A,B;

int ind[10010],vis[10010];
vector<int> endv;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int fx, int tx)
{
	at++;
	edge[at].pre=ptr[fx];
	edge[at].to=tx;
	ptr[fx]=at;
}

void DFS(int u)
{
	vis[u]=1;
	if (ptr[u]==0) endv.push_back(u);
	for (int v=ptr[u];v;v=edge[v].pre)
	{
		ind[edge[v].to]++;
		if (!vis[edge[v].to]) DFS(edge[v].to);
	}
}

int main()
{
	int u,v;
	readx(n); readx(m);
	for (int i=1;i<=m;i++) 
	{
		readx(u); readx(v);
		Is(u,v);
	}
	readx(A); readx(B);
	
	DFS(A);
	
	queue<int> que;
	que.push(A); dp[A]=1;
	
	while (!que.empty())
	{
		u=que.front(); que.pop();
		for (v=ptr[u];v;v=edge[v].pre)
		{
			dp[edge[v].to]+=dp[u];
			ind[edge[v].to]--;
			if (!ind[edge[v].to])
			{
				que.push(edge[v].to);
			}
		}
	}
	printf("%d ", dp[B]);
	if (endv.size()==1 && endv[0]==B) printf("Yes\n");
	else printf("No\n");
	
}
