#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<string>
#include<iterator>
#include<cstdlib>
#include<vector>
#include<queue>
#include<map>
#include<set>
#define ll long long
#define mod 2011
using namespace std;

struct Mountain { int val,w; }mnt[1010]={0};
int n;
int dp[1010]={0},end[1010]={0};

inline void readx(int& x)
{
    x=0; int k=1; register char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

inline bool cmp(Mountain a,Mountain b)
{
    if (a.val==b.val) return a.w<b.w;
    return a.val>b.val;
}

inline void get_1()
{
    int ans=1,pre=0;
    for (int i=1;i<=n;i++)
    {
        if (mnt[i].val!=mnt[pre].val) pre=i;
        ans=(ans*(min(mnt[i].w,pre)+i-pre))%mod;
    }
    printf("%d ",ans);
}

inline void get_2()
{
    int pos,cac,ans=1;
    for (int i=1;i<=n;i++)
    {
        pos=i;
        while (mnt[pos+1].val==mnt[pos].val) pos++;
        memset(dp,0,sizeof dp); dp[0]=1;
        for (int j=i;j<=pos;j++)
            for (int k=1;k<min(mnt[j].w,i);k++)
                dp[k]=(dp[k]+dp[k-1])%mod;
        cac=0; for (int j=0;j<min(mnt[pos].w,i);j++) cac=(cac+dp[j])%mod;
        i=pos; ans=(ans*cac)%mod;
    }
    printf("%d\n",ans);
}

int main()
{
    readx(n);
    for (int i=1;i<=n;i++) { readx(mnt[i].val); readx(mnt[i].w); }
    sort(mnt+1,mnt+n+1,cmp);
    get_1(); get_2();
}