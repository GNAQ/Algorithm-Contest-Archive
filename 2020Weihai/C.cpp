#include<iostream>
#define LL long long
#include<cstdio>
using namespace std;
const int MAXN=2e5+100;
struct node{
	int to;
	LL val;
	int next;
}e[MAXN<<1];
int id[MAXN][3],tot,head[MAXN],vis[MAXN];
LL sum[MAXN][5],cnt[MAXN][5],tmp_cnt[5][5],tmp_sum[5][5],m[5];
void add_edge(int u,int v,int val)
{
	e[++tot].next=head[u];
	e[tot].to=v;
	e[tot].val=val;
	head[u]=tot;
}
void dfs1(int x,int f)
{
	if(vis[x]&(1<<1)) cnt[x][1]++;
	if(vis[x]&(1<<2)) cnt[x][2]++;
	if(vis[x]&(1<<3)) cnt[x][3]++;
	for(int i=head[x];i;i=e[i].next)
	{
		int to=e[i].to;
		if(to==f) continue;
		dfs1(to,x);
		cnt[x][1]+=cnt[to][1];
		cnt[x][2]+=cnt[to][2];
		cnt[x][3]+=cnt[to][3];
		sum[x][1]+=sum[to][1]+cnt[to][1]*e[i].val;
		sum[x][2]+=sum[to][2]+cnt[to][2]*e[i].val;
		sum[x][3]+=sum[to][3]+cnt[to][3]*e[i].val;
	}
}
double ans=0;
void dfs2(int x,int f,LL fsum1,LL fsum2,LL fsum3,LL fcnt1,LL fcnt2,LL fcnt3)
{
	double tmp_ans=0;
//	printf("%lld %lld %lld %lld %lld %lld\n",fsum1,fsum2,fsum3,fcnt1,fcnt2,fcnt3);
	tmp_cnt[1][1]=fcnt1;tmp_sum[1][1]=fsum1;
	tmp_cnt[2][2]=fcnt2;tmp_sum[2][2]=fsum2;
	tmp_cnt[3][3]=fcnt3;tmp_sum[3][3]=fsum3;
	tmp_cnt[1][2]=tmp_cnt[1][3]=tmp_cnt[2][3]=0;
	tmp_sum[1][2]=tmp_sum[1][3]=tmp_sum[2][3]=0;
	for(int i=head[x];i;i=e[i].next)
	{
		int to=e[i].to;
		if(to==f) continue;
		tmp_ans+=1.0*tmp_sum[1][2]*cnt[to][3]+1.0*tmp_cnt[1][2]*(sum[to][3]+cnt[to][3]*e[i].val);
		tmp_ans+=1.0*tmp_sum[1][3]*cnt[to][2]+1.0*tmp_cnt[1][3]*(sum[to][2]+cnt[to][2]*e[i].val);
		tmp_ans+=1.0*tmp_sum[2][3]*cnt[to][1]+1.0*tmp_cnt[2][3]*(sum[to][1]+cnt[to][1]*e[i].val);
		
		tmp_sum[1][2]+=tmp_sum[1][1]*cnt[to][2]+tmp_cnt[1][1]*(sum[to][2]+cnt[to][2]*e[i].val);
		tmp_sum[1][2]+=tmp_sum[2][2]*cnt[to][1]+tmp_cnt[2][2]*(sum[to][1]+cnt[to][1]*e[i].val);
		tmp_sum[1][3]+=tmp_sum[1][1]*cnt[to][3]+tmp_cnt[1][1]*(sum[to][3]+cnt[to][3]*e[i].val);
		tmp_sum[1][3]+=tmp_sum[3][3]*cnt[to][1]+tmp_cnt[3][3]*(sum[to][1]+cnt[to][1]*e[i].val);
		tmp_sum[2][3]+=tmp_sum[2][2]*cnt[to][3]+tmp_cnt[2][2]*(sum[to][3]+cnt[to][3]*e[i].val);
		tmp_sum[2][3]+=tmp_sum[3][3]*cnt[to][2]+tmp_cnt[3][3]*(sum[to][2]+cnt[to][2]*e[i].val);
		
		tmp_cnt[1][2]+=tmp_cnt[1][1]*cnt[to][2]+tmp_cnt[2][2]*cnt[to][1];
		tmp_cnt[1][3]+=tmp_cnt[1][1]*cnt[to][3]+tmp_cnt[3][3]*cnt[to][1];
		tmp_cnt[2][3]+=tmp_cnt[2][2]*cnt[to][3]+tmp_cnt[3][3]*cnt[to][2];
		
		tmp_sum[1][1]+=sum[to][1]+cnt[to][1]*e[i].val;
		tmp_sum[2][2]+=sum[to][2]+cnt[to][2]*e[i].val;
		tmp_sum[3][3]+=sum[to][3]+cnt[to][3]*e[i].val;
		
		tmp_cnt[1][1]+=cnt[to][1];
		tmp_cnt[2][2]+=cnt[to][2];
		tmp_cnt[3][3]+=cnt[to][3];
	}
//	cout<<"!!!"<<x<<" "<<tmp_ans<<endl;
//	for(int i=1;i<=3;i++,printf("\n"))
//		for(int j=1;j<=3;j++)
//			printf("%d ",tmp_sum[i][j]);
//	cout<<"-----------------"<<endl;
	if(vis[x]&(1<<1)) tmp_ans+=tmp_sum[2][3];
	if(vis[x]&(1<<2)) tmp_ans+=tmp_sum[1][3];
	if(vis[x]&(1<<3)) tmp_ans+=tmp_sum[1][2];
	if((vis[x]&(1<<1))&&((vis[x]&(1<<2)))) tmp_ans+=tmp_sum[3][3];
	if((vis[x]&(1<<1))&&((vis[x]&(1<<3)))) tmp_ans+=tmp_sum[2][2];
	if((vis[x]&(1<<2))&&((vis[x]&(1<<3)))) tmp_ans+=tmp_sum[1][1];
//	cout<<"???"<<x<<" "<<tmp_ans<<endl;
	ans+=1.0*tmp_ans/(m[1]*m[2]*m[3]);
	if(vis[x]&(1<<1)) tmp_cnt[1][1]++;
	if(vis[x]&(1<<2)) tmp_cnt[2][2]++;
	if(vis[x]&(1<<3)) tmp_cnt[3][3]++;
	fsum1=tmp_sum[1][1];fsum2=tmp_sum[2][2];fsum3=tmp_sum[3][3];
	fcnt1=tmp_cnt[1][1];fcnt2=tmp_cnt[2][2];fcnt3=tmp_cnt[3][3];
	for(int i=head[x];i;i=e[i].next)
	{
		int to=e[i].to;
		if(to!=f)
		{
			LL tmp_fcnt1=fcnt1-cnt[to][1],tmp_fcnt2=fcnt2-cnt[to][2],tmp_fcnt3=fcnt3-cnt[to][3];
			dfs2(to,x,fsum1-(sum[to][1]+cnt[to][1]*e[i].val)+tmp_fcnt1*e[i].val
			,fsum2-(sum[to][2]+cnt[to][2]*e[i].val)+tmp_fcnt2*e[i].val
			,fsum3-(sum[to][3]+cnt[to][3]*e[i].val)+tmp_fcnt3*e[i].val
			,tmp_fcnt1,tmp_fcnt2,tmp_fcnt3);
		}
	}
}
int main()
{
	int n;scanf("%d",&n);
	for(int i=1;i<=n-1;i++)
	{
		int u,v,val;
		scanf("%d%d%d",&u,&v,&val);
		add_edge(u,v,val);
		add_edge(v,u,val);
	}
	for(int i=1;i<=3;i++)
	{
		scanf("%lld",&m[i]);
		for(int j=1;j<=m[i];j++)
		{
			scanf("%d",&id[j][i]);
			vis[id[j][i]]|=(1<<i);
		}
	}
	dfs1(1,-1);
//	for(int i=1;i<=n;i++,printf("\n"))
//		for(int j=1;j<=3;j++)
//			printf("%lld %lld ",sum[i][j],cnt[i][j]);
	dfs2(1,-1,0,0,0,0,0,0);
	printf("%.10lf\n",ans);
}