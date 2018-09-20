// luogu-judger-enable-o2
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#define ll long long
using namespace std;

int n,m,w,q,c1,c2,mapx[100003][21]={0};
int dp[100003][21][6]={0};
bool vis[100003][21][6]={0};

inline void readx(int& x)
{
    x=0; int k=1; register char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}


inline int _DP(int nx,int ny,int use)
{
    if (ny>n) return 0;
    else if (mapx[ny][nx]==-1) return -1*1e9;
    else if (vis[ny][nx][use]) return dp[ny][nx][use];
    if (nx==1) use=0;
    
    int rec=-1e9;
    if (use<q)
    {
        char flag=1; int tmp=0;
        for (int i=1;i<w;i++)
        {
            if (mapx[ny+i][nx+i]==-1) { flag=0; break; }
            tmp+=mapx[ny+i][nx+i];
        }
        if (flag) rec=max(rec,_DP(nx+w,ny+w,use+1)+tmp);
    }
    if (nx==1) rec=max(rec,_DP(nx,ny+1,0));
    if (nx>1) rec=max(rec,_DP(nx-1,ny+1,use));
    vis[ny][nx][use]=1; dp[ny][nx][use]=rec+mapx[ny][nx];
    return dp[ny][nx][use];	
}


int main()
{
    readx(n); readx(m); readx(c1); readx(c2);
    for (int i=1;i<=m;i++)
        for (int j=1;j<=n;j++) readx(mapx[j][i]);
    
    int _ans=-1e9,ans1,ans2;
    for (q=1;q<=5;q++)
        for (w=1;w*q<m;w++)
        {
            memset(dp,0,sizeof dp);
            memset(vis,0,sizeof vis);
            int qwq=_DP(1,0,0)-c1*(w-1)-c2*(q-1);
            if (qwq>_ans) { _ans=qwq; ans1=q; ans2=w; }
        }
    
    if (_ans<0) printf("mission failed\n");
    else printf("%d %d %d\n",_ans,ans1,ans2);
    return 0;
}