#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<iterator>
#include<queue>
#include<vector>
using namespace std;

struct ed { int pre,to; } edge[1000010]={0};
struct tr { int dep,fa; } tree[ 500010]={0};
int l[500010][19]={0};
int nodenum,at=0,pointer[500010]={0},fx,tx,rootx,opt;
int ux,vx;

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
    edge[at].pre=pointer[fx];
    edge[at].to=tx;
    pointer[fx]=at;
    at++;
    edge[at].pre=pointer[tx];
    edge[at].to=fx;
    pointer[tx]=at;
}

inline void Build(int nownode)
{
    l[nownode][0]=tree[nownode].fa;
    for (int i=1;i<=18;i++) l[nownode][i]=l[l[nownode][i-1]][i-1];
    
    for (int prex=pointer[nownode];prex;prex=edge[prex].pre) if (edge[prex].to!=tree[nownode].fa)
    {
        tree[edge[prex].to].dep=tree[nownode].dep+1;
        tree[edge[prex].to].fa=nownode;
        Build(edge[prex].to);
    }
}

inline int LCA(int u,int v)
{
    if (tree[u].dep<tree[v].dep) swap(u,v);
    for (int i=18;i>=0;i--) if (tree[l[u][i]].dep>=tree[v].dep) u=l[u][i];
    if (u==v) return u;
    for (int i=18;i>=0;i--) if (l[u][i]!=l[v][i])
    {
        u=l[u][i]; v=l[v][i];
    }
    return tree[u].fa;
}

int main()
{
    readx(nodenum); readx(opt); readx(rootx);
    for (int i=1;i<nodenum;i++)
    {
        readx(fx); readx(tx); Insert();
    }
    tree[rootx].fa=0; tree[rootx].dep=1;
    Build(rootx);
    
    for (int i=1;i<=opt;i++)
    {
        readx(ux); readx(vx);
        printf("%d\n",LCA(ux,vx));
    }
    return 0;
}
