#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
const int MAXN=4e5+100;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}
struct E{
	int to;
	int next;
}e[MAXN<<1];
int tot,n,ans,mid,head[MAXN],tg[10],res[10],flag,ckd,dis[MAXN];
void init()
{
	tot=0;
	memset(head,0,sizeof head);
}
void add_edge(int u,int v)
{
	e[++tot].next=head[u];
	e[tot].to=v;
	head[u]=tot;
}
void check_ans()
{
	ckd=2;
	queue<int>line;
	line.push(tg[0]);
	line.push(tg[1]);
	//cout<<tg[0]<<" "<<tg[1]<<endl;
	for(int i=1;i<=n;i++)
		dis[i]=MAXN;
	dis[tg[0]]=dis[tg[1]]=0;
	while(!line.empty())
	{
		int x=line.front();
		line.pop();
		for(int i=head[x];i;i=e[i].next)
		{
			int to=e[i].to;
			if(dis[to]==MAXN)
			{
				dis[to]=dis[x]+1;
				line.push(to);
			}
		}
	}
	for(int i=1;i<=n;i++)
		if(dis[i]>mid) ckd=1;
}
int dfs(int x,int f)
{
	int maxlen=0;
	//cout<<x<<" "<<f<<endl;
	for(int i=head[x];i;i=e[i].next)
	{
		int to=e[i].to;
		if(to==f) continue;
		//cout<<"x="<<x<<" "<<to<<" "<<i<<endl;
		maxlen=max(maxlen,dfs(to,x)+1);
		if(ckd) return 0;
		if(maxlen>mid) 
		{
			tg[flag++]=to;
			if(flag==1) tg[flag]=x;
			//cout<<"to="<<to<<" "<<x<<endl;
			if(flag==2) 
				check_ans();
			else {
				dfs(x,to);
				if(!ckd) ckd=3;
			}
		}
		if(ckd) return 0;
	}
	//cout<<"--------"<<endl;
	return maxlen;
}
bool check()
{
	dfs(1,1);
	//cout<<ckd<<" "<<flag<<endl;
	if(!flag) {tg[0]=1;tg[1]=2;}
	if(ckd==2||flag<2) return 1;
	else return 0;
}
int main()
{
	int T;cin>>T;
	while (T--)
	{
		cin>>n;init();
		for(int i=1;i<=n-1;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			add_edge(u,v);
			add_edge(v,u);
		}
		int l=0,r=1e6;
		while(l<=r)
		{
			mid=(l+r)>>1;ckd=0;flag=0;
			if(check()) 
			{
				ans=mid;
				r=mid-1;
				res[0]=tg[0];
				res[1]=tg[1];
			}
			else l=mid+1;
		}
		//mid=1;check();
		cout<<ans<<" "<<res[0]<<" "<<res[1]<<endl;
	}
}