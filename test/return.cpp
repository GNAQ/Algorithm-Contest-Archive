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
typedef long long ll;
using namespace std;

int n,m,ai[3000010],bi[3000010];

template<typename inp_typ>
void readx(inp_typ& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

namespace Sol1
{
	int pre[3010][6010];
	ll dp[3010][6010];
	
	void Output(int ni,int nj)
	{
		if (ni>1) Output(ni-1,pre[ni][nj]);
		printf("%d",nj-pre[ni][nj]);
	}
	
	void DP()
	{
		memset(dp,0x3f,sizeof dp); dp[0][0]=0;
		for (int i=1;i<=n;i++)
		{
			for (int j=0;j<=m;j++)
			{
				dp[i][j]=dp[i-1][j]; pre[i][j]=j;
				if (j>0 && dp[i-1][j-1]+ai[i]<dp[i][j]) 
				{
					dp[i][j]=dp[i-1][j-1]+ai[i];
					pre[i][j]=j-1;
				}
				if (j>1 && dp[i-1][j-2]+bi[i]<dp[i][j])
				{
					dp[i][j]=dp[i-1][j-2]+bi[i];
					pre[i][j]=j-2;
				}
			}
		}
	}
	
};

namespace Sol2 // ai equals
{
	ll ans; int plan[300010];
	struct elem { int a,b,id; };
	elem seq[300010];
	
	bool cmp1(elem a1,elem a2) { return a1.b<a2.b; }
	
	void Solve()
	{
		for (int i=1;i<=n;i++) { seq[i].a=ai[i]; seq[i].b=bi[i]; seq[i].id=i; }
		sort(seq+1,seq+n+1,cmp1);
		
		int pos=0;
		if (m<=n)
		{
			for (int i=1;i<=m;i++)
			{
				ans+=seq[i].a;
				plan[seq[i].id]=1;
			}
			return;
		}
		else
		{
			for (int i=1;i<=n;i++) 
			{
				plan[i]=1;
				ans+=seq[seq[i].id].a;
			}
			for (int i=1;i<=(m-n);i++) 
			{
				ans+=seq[i].b-seq[i].a;
				plan[seq[i].id]=2;
			}
			pos=(m-n)+1;
		}
		
		for (int i=pos;i<n;i+=2)
		{
			if (seq[i].a+seq[i+1].a>=seq[i].b)
			{
				ans-=(seq[i].a+seq[i+1].a-seq[i].b);
				plan[seq[i].id]=2; plan[seq[i+1].id]=0;
			}
			else break;
		}
	}
};

namespace Sol3 // bi equals
{
	ll ans; int plan[300010];
	struct elem { int a,b,id; };
	elem seq[300010];
	
	bool cmp1(elem a1,elem a2) { return a1.a<a2.a; }
	
	void Solve()
	{
		for (int i=1;i<=n;i++) { seq[i].a=ai[i]; seq[i].b=bi[i];seq[i].id=i; }
		sort(seq+1,seq+n+1,cmp1);
		
		int pos=0;
		if (m<=n)
		{
			for (int i=1;i<=m;i++)
			{
				ans+=seq[i].a;
				plan[seq[i].id]=1;
			}
			pos=m;
		}
		else
		{
			for (int i=1;i<=n;i++) 
			{
				plan[seq[i].id]=1;
				ans+=seq[i].a;
			}
			for (int i=n-(m-n)+1;i<=n;i++) 
			{
				ans+=seq[i].b-seq[i].a;
				plan[seq[i].id]=2;
			}
			pos=n-(m-n);
		}
		
		while (pos>1 && seq[pos].a+seq[pos-1].a>=seq[pos].b)
		{
			ans-=(seq[pos].a+seq[pos-1].a-seq[pos].b);
			plan[seq[pos].id]=2; plan[seq[pos-1].id]=0;
			pos-=2;
		}
	}
};

bool Judge()
{
	int tmp=ai[1];
	for (int i=1;i<=n;i++) if (ai[i]!=tmp) return false;
	return true;
}

int main()
{
	freopen("return.in","r",stdin);
	freopen("return.out","w",stdout);
	
	readx(n); readx(m);
	for (int i=1;i<=n;i++) { readx(ai[i]); readx(bi[i]); }
	
	if (n<=3000) 
	{
		Sol1::DP();
		printf("%lld\n",Sol1::dp[n][m]);
		Sol1::Output(n,m);
		putchar('\n');
	}
	else if (Judge())
	{
		Sol2::Solve();
		printf("%lld\n",Sol2::ans);
		for (int i=1;i<=n;i++) printf("%d",Sol2::plan[i]);
		putchar('\n');	
	}
	else
	{
		Sol3::Solve();
		printf("%lld\n",Sol3::ans);
		for (int i=1;i<=n;i++) printf("%d",Sol3::plan[i]);
		putchar('\n');		
	}
	
}