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
using namespace std;
typedef long long ll;
typedef ostream_iterator<int> os_iter_int;

bool G[710][710];
int n,m; ll ans;
int drg[710];
int d2[710][710],d3[710][710];

template<typename inp_t>
void readx(inp_t& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int main()
{
	readx(n); readx(m); int fx,tx;
	for (int i=1;i<=m;i++)
	{
		readx(fx); readx(tx); 
		drg[fx]++; drg[tx]++;
		G[fx][tx]=G[tx][fx]=1;
	}
	
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			for (int k=1;k<=n;k++)
				d2[i][j]+=G[i][k]*G[k][j];
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			for (int k=1;k<=n;k++)
				d3[i][j]+=(int)G[i][k]*d2[k][j];
	
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			ans+=1LL*d2[i][j]*d3[i][j];
	ans/=10;
	
	for (int i=1;i<=n;i++)
		for (int j=1;j<=i;j++) if (G[i][j])
			for (int k=1;k<=j;k++)
		{
			if (!(G[i][k] && G[j][k])) continue;
			ans-=drg[i]+drg[j]+drg[k]-3;
		}
	printf("%lld\n",ans);
}