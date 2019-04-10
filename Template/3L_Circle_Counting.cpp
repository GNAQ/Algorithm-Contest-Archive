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
using namespace std;
typedef long long ll;
typedef ostream_iterator<int> os_iter_int;

int n,m,drg[100010];
vector<pair<int,int>> edgen;
struct ed { int pre,to,id; } edge[400010];
int at=1,ptr[100010];

pair<int,int> tag[200010];
int ans[200010];

template<typename inp_t>
void readx(inp_t& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

inline void Is(int fx,int tx,int _id)
{
	at++;
	edge[at].pre=ptr[fx];
	edge[at].to=tx;
	edge[at].id=_id;
	ptr[fx]=at;
}

inline ll C(ll _n,ll _m=2)
{
	return _n*(_n-1)/2;
}

int main()
{
	while (scanf("%d%d",&n,&m)!=EOF)
	{
		int fx,tx; edgen.push_back({0,0});
		for (int i=1;i<=m;i++)
		{
			readx(fx); readx(tx);
			edgen.push_back({fx,tx});
			drg[fx]++; drg[tx]++;
		}
		for (int i=1;i<=m;i++)
		{
			int u,v; tie(u,v)=edgen[i]; 
			if (drg[u]==drg[v])
				Is(min(u,v),max(u,v),i);
			else if (drg[u]<drg[v])
				Is(u,v,i);
			else 
				Is(v,u,i);
		}
		
		for (int i=1;i<=m;i++)
		{
			int u,v; tie(u,v)=edgen[i]; 
			for (int tmp=ptr[u];tmp;tmp=edge[tmp].pre)
				tag[edge[tmp].to]={i,edge[tmp].id};
			for (int tmp=ptr[v];tmp;tmp=edge[tmp].pre)
				if (tag[edge[tmp].to].first==i)
				{
					ans[i]++;
					ans[edge[tmp].id]++;
					ans[tag[edge[tmp].to].second]++;
				}
		}
		
		ll tans=0;
		for (int i=1;i<=m;i++)
			if (ans[i]>1) tans+=C(ans[i]);
		printf("%lld\n",tans);
		
		memset(drg,0,sizeof(int)*(n+5));
		at=1; memset(ptr,0,sizeof ptr);
		memset(ans,0,sizeof ans);
		memset(tag,0,sizeof tag);
		vector<pair<int,int>> ().swap(edgen);
	}
}