// luogu-judger-enable-o2
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
#include<map>
#include<set>
#define ll long long
#define INF 0x3f3f3f3f
using namespace std;

struct ed
{
    int pre,to,w;
}edge[10010]={0};
int n,m,p,fx,tx,wx,at=0,ptr[1100]={0};

struct _nodes { int val,cod; }node[1100]={0};
int dp[1100][1100]={0},_dp[1100]={0};

//Status&Const Part

inline void readx(int& x)
{
    x=0; int k=1; register char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

inline void Insert()
{
    at++;
    edge[at].pre=ptr[fx];
    edge[at].to=tx;
    edge[at].w=wx;
    ptr[fx]=at;
    at++;
    edge[at].pre=ptr[tx];
    edge[at].to=fx;
    edge[at].w=wx;
    ptr[tx]=at;
}
inline bool cmp1(_nodes a,_nodes b) { return a.val<b.val; }

queue<int> que; bool vis[100010]={0};
inline void MST_SPFA(int St)
{
    register int cac;
    while (!que.empty())
    {
        cac=que.front(); que.pop(); vis[cac]=false;
        for (int prex=ptr[cac];prex;prex=edge[prex].pre)
            if (dp[edge[prex].to][St]>dp[cac][St]+edge[prex].w)
            {
                dp[edge[prex].to][St]=dp[cac][St]+edge[prex].w;
                if (!vis[edge[prex].to])
                {
                    vis[edge[prex].to]=1;
                    que.push(edge[prex].to);
                }
            }
    }
}

inline int Steiner_Tree(int END)
{
    for (int w=1;w<=END;w++)
    {
        for (int i=1;i<=n;i++)
        {
            for (int j=(w-1)&w;j;j=(j-1)&w) dp[i][w]=min(dp[i][w],dp[i][j]+dp[i][w-j]);
            if (dp[i][w]!=INF) { que.push(i); vis[i]=1; }
        }
        MST_SPFA(w);
    }
    int ret=2*1e9;
    for (int i=1;i<=n;i++) ret=min(ret,dp[i][END]);
    return ret;
}

int main()
{
    readx(n); readx(m); readx(p);
    for (int i=1;i<=m;i++)
    {
        readx(fx); readx(tx); readx(wx);
        Insert();
    }
    for (int i=1;i<=p;i++) { readx(node[i].val); readx(node[i].cod); }
    sort(node+1,node+p+1,cmp1);
    
    int ctr1=0;
    for (int i=1;i<=p;i++)
    {
        if (node[i].val!=node[i-1].val) ctr1++;
        node[i].val=ctr1;
    }
    ctr1=(1<<ctr1)-1; memset(_dp,0x3f,sizeof _dp);
    
    for (int i=1;i<=ctr1;i++)
    {
        memset(dp,0x3f,sizeof dp);
        int tmp=0;
        for (int j=1;j<=p;j++) if ((1<<(node[j].val-1))&i)
        {
            dp[node[j].cod][1<<tmp]=0;
            tmp++;
        }
        _dp[i]=Steiner_Tree((1<<tmp)-1);
    }
    
    for (int i=1;i<=ctr1;i++)
        for (int j=(i-1)&i;j;j=(j-1)&i)
            _dp[i]=min(_dp[i],_dp[j]+_dp[i-j]);
    printf("%d\n",_dp[ctr1]);
    return 0;
}