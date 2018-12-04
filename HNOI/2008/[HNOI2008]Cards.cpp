#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<iterator>
#include<vector>
#include<queue>
#include<map>
#include<set>
#define ll long long
using namespace std;

ll mod,n,m,ans,dp[110][110][110],R,B,G;
ll cir[110][110],cirnum,siz[110];
bool vis[110];

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

ll fastpow(ll an,ll p)
{
	ll ret=1;
	for (;p;p>>=1,an=(an*an)%mod) if (p&1) ret=(ret*an)%mod;
	return ret%mod;
}

void Find_Orc(int now)
{
	cirnum=0; memset(vis,0,sizeof vis); memset(siz,0,sizeof siz);
	for (int i=1;i<=n;i++) if (!vis[i])
	{
		cirnum++; int nex=i;
		while (!vis[nex])
		{
			vis[nex]=1;
			siz[cirnum]++;
			nex=cir[now][nex];
		}
	}
}

ll DP()
{
	memset(dp,0,sizeof dp);
	dp[0][0][0]=1;
	for (int i=1;i<=cirnum;i++)
		for (int r=R;r>=0;r--)
			for (int g=G;g>=0;g--)
				for (int b=B;b>=0;b--)
				{
					if (r>=siz[i]) dp[r][g][b]+=dp[r-siz[i]][g][b];
					if (g>=siz[i]) dp[r][g][b]+=dp[r][g-siz[i]][b];
					if (b>=siz[i]) dp[r][g][b]+=dp[r][g][b-siz[i]];
					dp[r][g][b]%=mod;
				}
	return dp[R][G][B];
}

int main()
{
	readx(R); readx(B); readx(G); readx(m); readx(mod);
	n=R+G+B; m++;
	for (int i=1;i<m;i++)
		for (int j=1;j<=n;j++)
			readx(cir[i][j]);
	for (int i=1;i<=n;i++) cir[m][i]=i;
	
	for (int i=1;i<=m;i++) 
	{
		Find_Orc(i);
		ans=(ans+DP())%mod;
	}
	ans=(ans*fastpow(m,mod-2))%mod;
	printf("%lld\n",ans);
	return 0;
}
