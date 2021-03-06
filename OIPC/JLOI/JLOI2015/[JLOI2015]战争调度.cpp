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
using namespace std;

int n,m,edgenum,at=0,ptr[100010]={0},upat;
int w[2100][30],f[2100][30];

int dp[2100][2100]={0};

inline void readx(int& x)
{
    x=0; int k=1; register char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

int sta[20]={0};
inline void DFS(int now,int dep)
{
    memset(dp[now],0,sizeof(dp[now]));
    if (dep==n) 
    {
        for (int i=1;i<dep;i++) 
        {
            if (sta[i]) dp[now][1]+=w[now-upat][i];
            else dp[now][0]+=f[now-upat][i];
        }
        return;
    }
    
    sta[dep]=0; DFS(now<<1,dep+1); DFS(now<<1|1,dep+1);
    for (int i=0;i<=(1<<(n-dep-1));i++)
        for (int j=0;j<=(1<<(n-dep-1));j++)
            dp[now][i+j]=max(dp[now][i+j],dp[now<<1][i]+dp[now<<1|1][j]);
        
    sta[dep]=1; DFS(now<<1,dep+1); DFS(now<<1|1,dep+1);
    for (int i=0;i<=(1<<(n-dep-1));i++)
        for (int j=0;j<=(1<<(n-dep-1));j++)
            dp[now][i+j]=max(dp[now][i+j],dp[now<<1][i]+dp[now<<1|1][j]);
}


int main()
{
    readx(n); readx(m); upat=(1<<(n-1));
    for (int i=0;i<upat;i++)
        for (int j=n-1;j;j--) readx(w[i][j]);
    for (int i=0;i<upat;i++)
        for (int j=n-1;j;j--) readx(f[i][j]);
    
    DFS(1,1);
    int ans=0;
    for (int i=0;i<=m;i++) ans=max(ans,dp[1][i]);
    printf("%d\n",ans);
    return 0;
}