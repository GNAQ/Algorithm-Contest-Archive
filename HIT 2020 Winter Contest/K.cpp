#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<queue>
typedef long long ll;
using namespace std;

struct ed
{
	int pre,to;
}edge[400010];
int at=1,ptr[200010];
int ans;
int n,m;

int vis[200010],l1[200010],l2[200010];
int dlen[200010];
int cnt;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Ins(int fx,int tx)
{
	at++;
	edge[at].pre=ptr[fx];
	edge[at].to=tx;
	ptr[fx]=at;
	at++;
	edge[at].pre=ptr[tx];
	edge[at].to=fx;
	ptr[tx]=at;
}

void FindFor(int u)
{
	vis[u]=1;
	for (int v=ptr[u];v;v=edge[v].pre)
		if (!vis[edge[v].to]) FindFor(edge[v].to);
}

void Clear()
{
	ans=0; 
	for (int i=1;i<=n;i++) 
	{
		vis[i]=0;
		ptr[i]=0;
		l1[i]=l2[i]=0;
	}
	for (int i=1;i<=cnt;i++) dlen[i]=0;
	// Graph
	at=1;
	cnt=0;
}

void FindD(int rt)
{
	queue<int> que;
	int bg=rt, bgmax=1, tmp;
	
	que.push(rt); l1[rt]=1;
	while (!que.empty())
	{
		tmp = que.front(); que.pop(); 
		for (int v=ptr[tmp];v;v=edge[v].pre)
			if (l1[edge[v].to]==0)
			{
				l1[edge[v].to]=l1[tmp]+1;
				
				if (l1[tmp]+1 > bgmax)
				{
					bgmax=l1[tmp]+1;
					bg=edge[v].to;
				}
				
				que.push(edge[v].to);
			}
	}
	
	que.push(bg); l2[bg]=1;
	while (!que.empty())
	{
		tmp=que.front(); que.pop();
		for (int v=ptr[tmp];v;v=edge[v].pre)
			if (!l2[edge[v].to])
			{
				l2[edge[v].to]=l2[tmp]+1;
				dlen[cnt]=max(dlen[cnt], l2[tmp]+1);
				que.push(edge[v].to);
			}
	}
	return;
}

bool cmp(int a,int b)
{
	return a>b;
}

void Solve()
{
	ans=0;
	for (int i=1;i<=n;i++) if (!vis[i])
	{
		FindFor(i);
		
		cnt++;
		FindD(i);
		
		ans=max(ans, dlen[cnt]-1);
	}
	
	sort(dlen+1, dlen+cnt+1, cmp);
	
	if (cnt==1)
	{
		;
	}
	else if (cnt==2)
	{
		ans=max(ans, 1 + dlen[1]/2 + dlen[2]/2);
	}
	else
	{
		ans=max(ans, 1 + dlen[1]/2 + dlen[2]/2);
		ans=max(ans, 2 + dlen[2]/2 + dlen[3]/2);
	}
	printf("%d\n", ans);
	return;
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		readx(n); readx(m); int u,v;
		for (int i=1;i<=m;i++)
		{
			readx(u); readx(v);
			Ins(u,v);
		}
		
		Solve();
		Clear();
	}
	
}

// sol

// 求出每棵树的直径
// 然后把各个直径的中间连起来
// 答案就是 max{所有直径, (第三长+1)/2 + (第二长+1)/2 +2, (第一长+1)/2 + (第二长+1)/2 +1} 
