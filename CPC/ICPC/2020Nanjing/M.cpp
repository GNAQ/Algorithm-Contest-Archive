#include<bits/stdc++.h>

using namespace std;

const long long inf=20000000000001LL;


template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

struct Edge
{
	int to,nxt;
	
	Edge(){}
	Edge(int to,int nxt):to(to),nxt(nxt){}
}e[2010];
int head[2010],cnt;

void addedge(int u,int v)
{
	e[++cnt]=Edge(v,head[u]);
	head[u]=cnt;
}

long long dp[2010][2010][2];
long long val[2010];
int siz[2010];

int n;

void pre(int now)
{
	siz[now]=1;
	for(int i=head[now];i;i=e[i].nxt)
	{
		int vs=e[i].to;
		pre(vs);
		siz[now]+=siz[vs];
	}
}

void dfs(int now)
{
	memset(dp[now],0x3f,sizeof(dp[now]));
	dp[now][0][0]=0;
	dp[now][1][1]=val[now];
	dp[now][0][1]=inf;
	for(int i=head[now];i;i=e[i].nxt)
	{
		int vs=e[i].to;
		dfs(vs);
		for(int j=siz[now];j>=0;j--)
		{
			int lim = min(j, siz[vs]);
			for(int k=0;k<=lim;k++)
			{
				dp[now][j][0]=min(dp[now][j][0],dp[now][j-k][0]+min(dp[vs][k][0],dp[vs][k][1]));
				dp[now][j][1]=min(dp[now][j][1],dp[now][j-k][1]+min(dp[vs][k][0],dp[vs][k][1]+val[vs]));
			}
		}
	}
}

void init()
{
	cnt=0;
	for (int i=1;i<=n;i++) head[i]=0;
}


signed main()
{
	//ios::sync_with_stdio(0);
	//cin.tie(0),cout.tie(0);
	int T;
	//cin>>T;
	readx(T);
	while(T--)
	{
		//cin>>n; init();
		readx(n); 
		for(int i=1;i<n;i++)
		{
			int tmp;
			//cin>>tmp;
			readx(tmp);
			addedge(tmp,i+1);
		}
		for(int i=1;i<=n;i++) 
		{
			//cin>>val[i];
			readx(val[i]);
		}
		pre(1);
		dfs(1);
		for(int i=n;i>0;i--)
		{
			printf("%lld ", min(dp[1][i][0], dp[1][i][1]));
			// cout<<min(dp[1][i][0],dp[1][i][1])<<' ';
		}
        init();
		//cout<<"0\n";
		printf("0\n");
	}
}