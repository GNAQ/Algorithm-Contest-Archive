#include<algorithm>
#include<iostream>
#include<cstdio>
#include<bits/stdc++.h>

#define LL long long
using namespace std;
const int MAXN=2e6+100;

vector<int>to[200010];

struct node{
	int x;
	int y;
	bool friend operator < (node a,node b)
	{
		if(a.x==b.x) return a.y<b.y;
		else return a.x<b.x;
	}
}dat[MAXN];
struct POINT{
	int L;
	int R;
	LL val;
}point[MAXN];
int n,m,k,cnt,L[MAXN],R[MAXN];
long long ans=0;
bool vis[2000010];

void init()
{
	for(int i=1;i<=cnt;i++)
		to[i].clear();
	for(int i=1;i<=n;i++)
		L[i]=R[i]=0;
    for(int i=1;i<=cnt;i++)
        vis[i]=0;
	cnt=0;
    ans=0;
    
}

void add_edge(int u,int v)
{
	to[u].push_back(v);
}

void dfs(int now,int lmax)
{
    vis[now]=1;
    
    ans+=point[now].R-lmax+1;
    //cout<<"!"<<now<<" "<<ans<<'\n';
    for(int i=0;i<to[now].size();i++)
    {
        int vs=to[now][i];
        if(!vis[vs]&&(max(lmax,point[vs].L)<=point[vs].R)) dfs(vs,max(lmax,point[vs].L));
    }
}

int main()
{
	int T;cin>>T;
	while(T--)
	{
		init();
		cin>>n>>m>>k;
		for(int i=1;i<=k;i++)
			scanf("%d%d",&dat[i].x,&dat[i].y);
		for(int i=1;i<=n;i++)
		{
			dat[++k].x=i;
			dat[k].y=0;
			dat[++k].x=i;
			dat[k].y=m+1;
		}
		sort(dat+1,dat+1+k);
		int now_pos=1;L[1]=1;
		for(int i=1;i<=n;i++)
		{
			while(now_pos<k&&dat[now_pos+1].x==i)
			{
				if(dat[now_pos].y!=dat[now_pos+1].y-1)
				{
					point[++cnt].L=dat[now_pos].y+1;
					point[cnt].R=dat[now_pos+1].y-1;
					point[cnt].val=dat[now_pos+1].y-dat[now_pos].y-1;
					R[i]=cnt;L[i+1]=cnt+1;R[i+1]=cnt;
				}
				now_pos++;
			}	
			now_pos++;			
			int last_pos=L[i-1];
			if(last_pos==0||L[i-1]>R[i-1]) continue;
			for(int j=L[i];j<=R[i]&&j!=0;j++)
			{
				while(point[j].L>point[last_pos].R&&last_pos<=R[i-1])
					last_pos++;
				if(last_pos>R[i-1]) break;
				while(point[j].R>=point[last_pos].L&&last_pos<=R[i-1]) 
				{
					add_edge(last_pos,j);
					last_pos++;
				}
				if(last_pos>L[i-1]) last_pos--;
				if(last_pos>R[i-1]) break;
			}
		}
        dfs(1,1);
        cout<<ans<<"\n";
		init();
	}
}
