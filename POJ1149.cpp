#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<vector>
#include<algorithm>
typedef long long ll;
using namespace std;

struct ed
{
	int pre,to,cap;
}edge[200010];
int at=1,ptr[100010];
int S,T,n,m;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int u, int v, int c)
{
	at++;
	edge[at].pre=ptr[u];
	edge[at].to=v;
	edge[at].cap=c;
	ptr[u]=at;
	at++;
	edge[at].pre=ptr[v];
	edge[at].to=u;
	edge[at].cap=0;
	ptr[v]=at;
}

namespace Dinic
{
	int lvl[100010],cur[100010];
	
	
}

int main()
{
	
}