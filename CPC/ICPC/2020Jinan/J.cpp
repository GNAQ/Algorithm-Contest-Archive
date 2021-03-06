#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
using namespace std;
typedef long long ll;

struct ed
{
	int pre,to;
} edge[20010];
int at=0,ptr[1010];
int n, col[1010];

int wcnt, bcnt;

ll ai[1010];


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

void DFS(int u, int dep, int fa)
{
	if (dep%2) wcnt++;
	else bcnt++;
	
	col[u]=dep%2;
	for (int v=ptr[u];v;v=edge[v].pre)
		if (edge[v].to!=fa)
		{
			DFS(edge[v].to, dep+1, u);
		}
	return;
}

int main()
{
	readx(n);
	int u,v; 
	wcnt=bcnt=0;
	for (int i=1;i<n;i++)
	{
		readx(u); readx(v);
		Is(u,v); Is(v,u);
	}
	DFS(1,1,-1);
	
	if (wcnt<bcnt)
	{
		swap(wcnt, bcnt);
		for (int i=1;i<=n;i++) col[i]^=1;
	}
	
	int lim = 2;
	for (int i=1;i<=n;i++) if (!col[i])
	{
		ai[i]=1152921504606846974LL;
		ai[i] ^= (1LL<<lim);
		
		for (int v=ptr[i];v;v=edge[v].pre)
			ai[edge[v].to] |= (1LL<<lim);
			
		lim++;
	}
	for (int i=1;i<=n;i++) if (col[i])
		ai[i] |= 1;
	

	for (int i=1;i<=n;i++) 
		printf("%lld%c", ai[i], " \n"[i==n]);
	return 0;
}