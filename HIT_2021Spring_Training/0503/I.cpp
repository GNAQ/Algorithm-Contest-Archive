#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<vector>
#include<string>
typedef long long ll;
using namespace std;

int n, k, ai[2010];
ll dp[2010][2010];
vector< pair<int, int> > vec[2010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int main()
{
	readx(n); readx(k); memset(dp,0xcf,sizeof(dp));
	for (int i=1;i<=n;i++) readx(ai[i]);
	
	int vand=-1, vor=0, vxor=0;
	for (int i=1;i<=n;i++)
	{
		vand = vand & ai[i];
		vor = vor | ai[i];
		dp[1][i]=vand^vor;
	}
	for (int i=2;i<=n;i++)
	{
		vand = -1; vor = 0; vxor = -1;
		for (int j=i;j>=1;j--)
		{
			vand = vand & ai[j];
			vor = vor | ai[j];
			
			if ((vand^vor)!=vxor)
			{
				vec[i].push_back(make_pair(j, vand^vor));
			}
			vxor = vand ^ vor;
		}
	}
	
	for (int i=2;i<=k;i++)
		for (int j=1;j<=n;j++)
		{
			for (int ii=0;ii<vec[j].size();ii++)
			{
				dp[i][j]=max(dp[i][j], dp[i-1][ vec[j][ii].first-1 ] + vec[j][ii].second);
			}
		}
	
	cout << dp[k][n] << endl;
	return 0;
}