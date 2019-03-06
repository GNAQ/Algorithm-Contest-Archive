#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<bitset>
typedef long long ll;
using namespace std;

int n,m,pre,cnt;
int mseq[1000100];

// bitset<50001> dp[2];
bool dp[2][1010];

template<typename inp_t>
void readx(inp_t& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

bool Q(int j)
{
	if (j<1 || j>n) return 1;
	return dp[pre][j];
}

int main()
{
	readx(n); readx(m); // m<=n
	for (int i=1;i<=m;i++) readx(mseq[i]);
	
	pre=1,cnt=0;
	for (int i=n;i>=1;i--)
	{
		for (int j=1;j<=n;j++)
		{
			if (i&2) dp[cnt][j]=(Q(j-i)&Q(j+i))^1;
			else dp[cnt][j]=(Q(j-i)^1)|(Q(j+i)^1);
		}
		swap(pre,cnt);
	}
	
	for (int i=1;i<=m;i++) printf("%d",dp[pre][mseq[i]]);
	printf("\n");
}