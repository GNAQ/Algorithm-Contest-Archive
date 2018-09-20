#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<vector>
#include<cmath>
#include<string>
#include<cstdlib>
#include<map>
#include<set>
#define ll long long
#define PAUSE system("pause")
using namespace std;

int n=1,m=1,s,t,_Ctr=0;
bool vis[110][110]={0};
char chs[100]={0};

int dp[110][30]={0},pre[110][30]={0},otpt[110]={0};

inline void readx(int& x)
{
	x=0; int k=1; register char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

inline void clear_all()
{
	s=t=0;
	memset(vis,0,sizeof vis);
	memset(dp,0,sizeof dp);
	memset(pre,0,sizeof pre);
	memset(otpt,0,sizeof otpt);
	memset(chs,0,sizeof chs);
}

inline void output(int i,int j)
{
	if (i!=t) output(i+1,pre[i][j]);
	if (pre[i][j]!=j) otpt[i+1]=pre[i][j]+'A'-1;
}

int main()
{
	while (1)
	{
		_Ctr++; clear_all();
		readx(m); readx(n); 
		if (m==0 || n==0) return 0;
		if (_Ctr>1) putchar('\n');
		
		for (int i=1;i<=m;i++)
		{
			scanf("%s",chs+1);
			for (int j=1;j<=n;j++) vis[i][j]=(chs[j]=='X');
		}
		readx(s); readx(t); t--;
		
		memset(dp,0x3f,sizeof dp);
		for (int i=1;i<=n;i++) if (!vis[t][i]) dp[t][i]=0;
		for (int i=t-1;i>=s;i--)
			for (int j=1;j<=n;j++) if (!vis[i][j])
			{
				for (int k=1;k<=n;k++) if (!vis[i+1][k])
				{
					if (dp[i+1][k]+(j!=k)<dp[i][j])
					{
						dp[i][j]=dp[i+1][k]+(j!=k);
						pre[i][j]=k;
					}
				}
			}
		printf("Case %d:\n\n",_Ctr);
		
		int ans=2*1e9,ptr=0;
		for (int i=1;i<=n;i++) if (dp[s][i]<ans)
			{ ans=dp[s][i]; ptr=i; }
		if (ans>200)  { printf("Not available\n"); continue; }
		
		output(s,ptr); int qwq=s; otpt[qwq]=ptr+'A'-1;
		for (int i=s+1;i<=t;i++) if (otpt[i]!=0)
		{
			printf("%c: %d-%d\n",otpt[qwq],qwq,i);
			qwq=i;
		}
		printf("%c: %d-%d\n",otpt[qwq],qwq,t+1);
	}
	// system("pause");
	return 0;
}