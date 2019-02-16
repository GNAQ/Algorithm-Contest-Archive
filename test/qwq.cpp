#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<map>
#include<set>
#include<vector>
#include<queue>
typedef long long ll;
using namespace std;

struct ed
{
	int pre,to;
}edge[200010];
int at=1,ptr[100010];
int nodev[100010],nnv[100010],chseq[100010];
ll dp[1010];

int n,q;
const ll mod=1e9+7;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int fx,int tx)
{
	at++;
	edge[at].pre=ptr[fx];
	edge[at].to=tx;
	ptr[fx]=at;
}

void DP(int now)
{
	cout<<now<<endl;
	for (int v=ptr[now];v;v=edge[v].pre) 
		DP(edge[v].to);
	dp[now]=nodev[now];
	for (int v=ptr[now];v;v=edge[v].pre)
		dp[now]=(dp[now]*(dp[edge[v].to]+1))%mod;
}

int main()
{
	readx(n); readx(q); int fx;
	for (int i=1;i<=n;i++) readx(nodev[i]);
	for (int i=1;i<n;i++) 
		{ readx(fx); Is(fx,i+1); }
	
	for (int i=1;i<=q;i++)
	{
		int chnum;
		readx(chnum);
		for (int j=1;j<=chnum;j++)
		{
			readx(chseq[j]); 
			readx(nnv[chseq[j]]);
		}
		for (int j=1;j<=chnum;j++) swap(nodev[chseq[j]],nnv[chseq[j]]);
		
		memset(dp,0,sizeof dp);
		DP(1);
		printf("%lld\n",dp[1]);
		
		for (int j=1;j<=chnum;j++) swap(nodev[chseq[j]],nnv[chseq[j]]);
	}
	
}