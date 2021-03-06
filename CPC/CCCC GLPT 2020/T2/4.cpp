#include<cstring>
#include<cstdio>
#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<map>
#include<set>
typedef long long ll;
using namespace std;

ll G[210][210];
bool iG[210][210];
ll n,m,k,ans,id,aans;

vector<ll> ways[100010];
ll cnt,ki[100010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

bool vis[210];
bool CheckOnce(int inx)
{
	int timer=0,siz=ways[inx].size();;
	for (int i=1;i<=n;i++) vis[i]=0;
	for (int i=0;i<siz-1;i++)
	{
		timer+=1^vis[ways[inx][i]];
		vis[ways[inx][i]]=1;
	}
	return timer==n;
}

int main()
{
	ans=200000000000000000LL;
	ll u,v,w;
	readx(n); readx(m);
	for (int i=1;i<=m;i++) 
	{
		readx(u); readx(v); readx(w);
		if ((iG[u][v]==1 && G[u][v]>w) || iG[u][v]==0)
		{
			G[u][v]=G[v][u]=w;
			iG[u][v]=iG[v][u]=1;
		}
	}
	
	readx(k);
	for (int i=1;i<=k;i++)
	{
		readx(u); 
		if (u==n) 
		{
			cnt++;
			ki[cnt]=i;
		}
		for (int j=1;j<=u;j++) 
		{
			readx(v);
			if (u==n) ways[cnt].push_back(v);
		}
		if (u==n) ways[cnt].push_back(0);
	}
	
	for (int i=1;i<=cnt;i++)
	{
		ll cost=0; bool flag=!CheckOnce(i);
		u=0;
		int siz=ways[i].size();
		for (int j=0;j<siz;j++)
		{
			if (j<siz-1 && (ways[i][j]<1 || ways[i][j]>n))
			{
				flag=1;
				break;
			}
			if (!iG[u][ways[i][j]])
			{
				flag=1;
				break;
			}
			cost+=G[u][ways[i][j]];
			u=ways[i][j];
		}
		if (!flag && ans>cost)
		{
			ans=cost;
			id=ki[i];
		}
		if (!flag) aans++;
	}
	printf("%lld\n%lld %lld\n", aans, id, ans);
	
}
