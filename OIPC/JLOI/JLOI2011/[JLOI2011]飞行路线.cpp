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
#include<set>
#include<map>
#define ll long long
#define PAUSE system("pause");
using namespace std;

struct ed { int pre,to,w; }edge[2500010]={0};
int nodenum,edgenum,at=0,ptr[200010]={0},fx,tx,wx,ss,tt,K;

int dis[200010]={0},cac1;
bool vis[200010]={0};
struct node_s
{
    int node,dis;
    bool operator < (const node_s& a) const
        { return dis>a.dis; }
};
priority_queue<node_s> que;

inline void readx(int& x)
{
    x=0; int k=1; register char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

inline void Insert(int FX,int TX,int WX)
{
    at++;
    edge[at].pre=ptr[FX];
    edge[at].to=TX;
    edge[at].w=WX;
    ptr[FX]=at;
}

inline int Dijkstra()
{
    memset(dis,0x3f,sizeof dis); dis[ss]=0;
    node_s cac1,cac2;
    cac1.node=ss; cac1.dis=0; que.push(cac1);
    
    while (!que.empty())
    {
        cac1=que.top(); que.pop(); 
        if (vis[cac1.node]) continue;
        vis[cac1.node]=true;
        for (int prex=ptr[cac1.node];prex;prex=edge[prex].pre) 
            if (dis[edge[prex].to]>dis[cac1.node]+edge[prex].w)
            {
                dis[edge[prex].to]=dis[cac1.node]+edge[prex].w;
                cac2.node=edge[prex].to; cac2.dis=dis[edge[prex].to];
                que.push(cac2);
            }
    }
    return dis[nodenum*K+tt];
}

int main()
{
    readx(nodenum); readx(edgenum); readx(K); readx(ss); readx(tt);
    for (int i=1;i<=edgenum;i++)
    {
        readx(fx); readx(tx); readx(wx);
        Insert(fx,tx,wx); Insert(tx,fx,wx);
        for (int j=1;j<=K;j++)
        {
            Insert(fx+(j-1)*nodenum,tx+j*nodenum,0);
            Insert(tx+(j-1)*nodenum,fx+j*nodenum,0);
            Insert(fx+j*nodenum,tx+j*nodenum,wx);
            Insert(tx+j*nodenum,fx+j*nodenum,wx);
        }
    }
    for (int i=0;i<K;i++) Insert(tt+i*nodenum,tt+(i+1)*nodenum,0);
    printf("%d\n",Dijkstra());
}