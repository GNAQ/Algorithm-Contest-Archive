// luogu-judger-enable-o2
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#define ll long long
using namespace std;

int N,K;
int dp[2000];
int seq[20],ans,ansseq[20];

template<typename int_t>
void readx(int_t& x)
{
    x=0; int_t k=1; char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

int DP(int upat,int V)
{
    memset(dp,0x3f,sizeof dp);
    dp[0]=0;
    for (int i=1;i<=upat;i++)
        for (int j=seq[i];j<=V;j++)
            dp[j]=min(dp[j],dp[j-seq[i]]+1);
    for (int i=1;i<=V;i++) if ((!dp[i]) || dp[i]>N) return i-1; 
    return V;
}

void DFS(int step,int low,int high,int sum)
{
    if (step==K+1) 
    {
        if (ans<high) { ans=high; for (int i=1;i<=N;i++) ansseq[i]=seq[i]; }
        return;
    }
    for (int i=low+1;i<=high+1;i++)
    {
        seq[step]=i;
        DFS(step+1,i,DP(step,N*(sum+i)),sum+i);
    }
}

int main()
{
    readx(N); readx(K);
    DFS(1,0,0,0);
    for (int i=1;i<=K;i++) printf("%d%c",ansseq[i]," \n"[i==K]);
    printf("MAX=%d\n",ans);
    return 0;
}
