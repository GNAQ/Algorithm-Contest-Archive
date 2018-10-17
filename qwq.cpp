#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<queue>
#include<vector>
#include<set>
#include<map>
#define ll long long
using namespace std;

int n,m,k;
int up[10010],down[10010];
struct _Pipe
{
	int d,u;
}pp[10010];

int dp[10010][2010];
bool has_p[10010];

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int main()
{
	readx(n); readx(m); readx(k); int tmp_x;
	for (int i=1;i<=n;i++) { readx(up[i]); readx(down[i]); }
	for (int i=1;i<=k;i++)
	{
		readx(tmp_x);
		readx(pp[tmp_x].d); readx(pp[tmp_x].u);
		has_p[tmp_x]=1;
	}
	
	memset(dp,0x3f,sizeof dp);
	for (int i=1;i<=m;i++) dp[0][i]=0;
	
	for (int i=1;i<=n;i++)
	{
		for (int j=up[i];j<=m+up[i];j++) 
			dp[i][j]=min(dp[i-1][j-up[i]]+1,dp[i][j-up[i]]+1);
		for (int j=m+1;j<=m+up[i];j++) // satisfy limits
			dp[i][m]=min(dp[i][m],dp[i][j]);
		for (int j=m-down[i];j>=1;j--) dp[i][j]=min(dp[i][j],dp[i-1][j+down[i]]);//fall down
		if (pp[i].d) for (int j=0;j<=pp[i].d;j++) dp[i][j]=0x3f3f3f3f;
		if (pp[i].u) for (int j=pp[i].u+1;j<=m;j++) dp[i][j]=0x3f3f3f3f;
	}
	int ans=0x3f3f3f3f;
	for (int i=1;i<=m;i++) ans=min(ans,dp[n][i]);
	if (ans<0x3f3f3f3f) printf("1 %d\n",ans);
	else
	{
		printf("0 "); ans=0; int last=n;
		for (;last>=1;last--)
			for (int j=1;j<=m;j++) if (dp[last][j]<0x3f3f3f3f) 
				goto next_step;
		next_step:
		for (int i=1;i<=last;i++) if (has_p[i]) ans++;
		printf("%d\n",ans);
	}
	
	system("pause");
	return 0;
}