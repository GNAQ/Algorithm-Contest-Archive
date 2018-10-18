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
#include<map>
#include<set>
#define ll long long
using namespace std;

int dp[100010][2];
int n;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

bool Judge(int val)
{
	bool can[20];
	for (int i=1;i<=n;i++) can[i]=(val&(1<<(i-1)));
	for (int i=1;i<=n;i++) if (can[i]) if (!can[i-1] && !can[i+1]) return false;
	for (int i=1;i<=n;i++) printf("%d%c",can[i]," \n"[i==n]);
	return true;
}

int main()
{
	readx(n);
	for (int i=0;i<=n;i++) dp[i][0]=1;
	dp[2][1]=1;
	dp[3][0]=2; dp[3][1]=2;
	
	for (int i=4;i<=n;i++)
	{
		for (int j=i-2;j;j--)
		{
			dp[i][0]+=dp[i-j][1];
		}
		
		for (int j=2;j<=i;j++)
		{
			dp[i][1]+=dp[i-j][0];
		}
	}
	for (int i=2;i<=n;i++) printf("%d ",dp[i][0]+dp[i][1]-1);
	printf("\n");
}