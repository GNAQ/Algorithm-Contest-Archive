// luogu-judger-enable-o2
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<queue>
#include<vector>
#include<map>
#include<set>
#define ll long long 
using namespace std;

struct edge
{
    int pre,to;
}edge[200010]={0};
int nodenum,edgenum,at=0,ptr[100010]={0},fx,tx;
int ans=0;

int nodev[100010]={0},s,dis[100010][22]={0},l[100010][22]={0};

inline void readx(int& x)
{
    x=0; int k=1; register char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
}

inline void Insert()
{
    at++;
    edge[at].pre=ptr[fx];
    edge[at].to=tx;
    ptr[fx]=at;
}

inline void DFS(int now,int fa)
{
    dis[now][0]=nodev[fa]; l[now][0]=fa;
    for (int i=1;i<=20;i++)
    {
        l[now][i]=l[l[now][i-1]][i-1];
        dis[now][i]=dis[now][i-1]+dis[l[now][i-1]][i-1];
    }
    
    for (int prex=ptr[now];prex;prex=edge[prex].pre) DFS(edge[prex].to,now);
}

int main()
{
    readx(nodenum); readx(s);
    for (int i=1;i<=nodenum;i++) readx(nodev[i]);
    for (int i=1;i<nodenum;i++)
    {
        readx(fx); readx(tx); 
        Insert();
    }
    DFS(1,0);
    
    for (int i=1;i<=nodenum;i++)
    {
        register int sum=s,pos=i;
        sum-=nodev[i];
        
        if (sum<=0)
        {
            if (!sum) ans++;
            continue;
        }
        
        for (int i=18;i>=0;i--)
        {
            if (dis[pos][i]<=sum)
            {
                sum-=dis[pos][i];
                pos=l[pos][i];
            }
        }
        if (!sum) ans++;
    }
    
    printf("%d\n",ans);
    return 0;
}