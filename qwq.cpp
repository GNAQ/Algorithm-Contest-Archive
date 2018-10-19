#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#define ll long long
using namespace std;

int n,m,v,e;
int G[310][310];
int cl[2010][2];
double pr[2010];

double dp[2010][2010][2];
const double INF=2*1e9;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}
void Input()
{
	int fx,tx,wx; memset(G,0x3f,sizeof G);
	readx(n); readx(m); readx(v); readx(e);
	for (int i=1;i<=v;i++) G[i][i]=0;
	
	for (int i=1;i<=n;i++) readx(cl[i][0]);
	for (int i=1;i<=n;i++) readx(cl[i][1]);
	for (int i=1;i<=n;i++) scanf("%lf",&pr[i]);
	for (int i=1;i<=e;i++)
	{
		readx(fx); readx(tx); readx(wx);
		if (wx<G[fx][tx]) G[tx][fx]=G[fx][tx]=wx;
	}
}

void Floyd()
{
	for (int k=1;k<=v;k++)
		for (int i=1;i<=v;i++)
			for (int j=1;j<=v;j++) G[i][j]=min(G[i][j],G[i][k]+G[k][j]);
}

int main()
{
	Input(); Floyd();
	
	memset(dp,0x43,sizeof dp);
	dp[1][0][0]=dp[1][1][1]=0;
	
	for (int i=2;i<=n;i++)
	{
		double tv=(double)G[cl[i-1][0]][cl[i][0]],tv2=(double)G[cl[i-1][1]][cl[i][0]];
		double qv=(double)G[cl[i-1][0]][cl[i][1]],qv2=(double)G[cl[i-1][1]][cl[i][1]];
		
		for (int j=0;j<=min(m,i);j++)
		{
			dp[i][j][0]=min(
							dp[i-1][j][0]+tv,
							dp[i-1][j][1]+tv*(1-pr[i-1])+tv2*pr[i-1]
						   );
			if (j!=0)
			dp[i][j][1]=min(
							dp[i-1][j-1][0]+qv*pr[i]+tv*(1-pr[i]),
							dp[i-1][j-1][1]+tv*(1-pr[i-1])*(1-pr[i])
										   +tv2*pr[i-1]*(1-pr[i])
										   +qv*(1-pr[i-1])*pr[i]
										   +qv2*pr[i-1]*pr[i]
							);
		}
	}
	
	double ans=INF;
	for (int i=0;i<=m;i++) ans=min(ans,min(dp[n][i][0],dp[n][i][1]));
	printf("%.2lf\n",ans);
	return 0;
}