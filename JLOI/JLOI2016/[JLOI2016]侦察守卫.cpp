// luogu-judger-enable-o2
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#define ll long long
using namespace std;

struct ed
{
    int pre,to;
}edge[500010]={0},edge2[1000010]={0};
int n,m,at=0,ptr[500010]={0},nodev[500010]={0},d;
int at2=0,ptr2[500010]={0};

int dp[500010][22]={0},dp2[500010][22]={0};
bool mark[500010][22]={0};


inline void readx(int& x)
{
    x=0; int k=1; register char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

inline void Insert(int fx,int tx)
{
    at++;
    edge[at].pre=ptr[fx];
    edge[at].to=tx;
    ptr[fx]=at;
}
inline void Insert2(int fx,int tx)
{
    at2++;
    edge2[at2].pre=ptr2[fx];
    edge2[at2].to=tx;
    ptr2[fx]=at2;
    at2++;
    edge2[at2].pre=ptr2[tx];
    edge2[at2].to=fx;
    ptr2[tx]=at2;
}

inline void DFS(int now,int fa)
{
    for (int prex=ptr2[now];prex;prex=edge2[prex].pre) if (edge2[prex].to!=fa)
    {
        Insert(now,edge2[prex].to);
        DFS(edge2[prex].to,now);
    }
}

inline void _DP(int now,int fa)
{
    int flag=1;
    for (int prex=ptr[now];prex;prex=edge[prex].pre)
    {
        flag=0; _DP(edge[prex].to,now);
        for (register int i=1;i<=d;i++) mark[now][i]|=mark[edge[prex].to][i-1];//UPD marks
    }
    if (flag)
    {
        dp[now][0]=dp2[now][0]=mark[now][0]*nodev[now];
        for (register int i=1;i<=d;i++) { dp[now][i]=0; dp2[now][i]=nodev[now]; }
        return;
    }
    
    for (register int prex=ptr[now];prex;prex=edge[prex].pre)
        for (int i=1;i<=d;i++)
            dp[now][i]+=dp[edge[prex].to][i-1];
    for (register int prex=ptr[now];prex;prex=edge[prex].pre)
            dp2[now][d]+=dp[edge[prex].to][d];
    dp2[now][d]+=nodev[now];
    
    int tmp=0;
    for (int i=d-1;i>=0;i--)
    {
        tmp=0;
        for (int prex=ptr[now];prex;prex=edge[prex].pre)
            tmp+=dp[edge[prex].to][i];
        dp2[now][i]=dp2[now][i+1];
        for (int prex=ptr[now];prex;prex=edge[prex].pre)
            dp2[now][i]=min(dp2[now][i],dp2[edge[prex].to][i+1]+tmp-dp[edge[prex].to][i]);
    }
    
    //UPD1
    dp[now][0]=dp2[now][0];
    for (int i=1;i<=d;i++)
        dp[now][i]=min(dp[now][i],dp[now][i-1]);
    //UPD2 (Why?)
    for (int i=d-1;i>=0;i--) if (!mark[now][i]) 
        dp[now][i]=min(dp[now][i],dp[now][i+1]);
    dp2[now][0]=dp[now][0];
}

int main()
{
    readx(n); readx(d);
    for (int i=1;i<=n;i++) readx(nodev[i]);
    readx(m); register int cac,fx,tx;
    for (int i=1;i<=m;i++) { readx(cac); mark[cac][0]=1; }
    for (int i=1;i<n;i++) { readx(fx); readx(tx); Insert2(fx,tx); }
    
    DFS(1,0); _DP(1,0);
    printf("%d\n",dp[1][0]);
    return 0;
}