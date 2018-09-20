#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<iterator>
using namespace std;

struct ed
{
    int pre,to;
}edge[600010]={0};
int nodenum,fx,tx,at=1,pointer[300010]={0};
bool vis[300010]={0};

struct tr
{
    int depth,father;
}tree[300010]={0};
int l[300010][22]={0},u,v,uvlca;

int spr[300010]={0},opt[300010]={0},ans=0;

inline void readx(int& x)
{
    x=0; int k=1; register char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

inline void Insert()
{
    edge[at].pre=pointer[fx];
    edge[at].to=tx;
    pointer[fx]=at;
    at++;
    edge[at].pre=pointer[tx];
    edge[at].to=fx;
    pointer[tx]=at;
    at++;
}

inline void BuildTree(int nownode)
{
    l[nownode][0]=tree[nownode].father;
    for (int i=1;i<=21;i++) l[nownode][i]=l[l[nownode][i-1]][i-1];
    
    vis[nownode]=1;
    int prex=pointer[nownode];
    while (prex)
    {
        if (!vis[edge[prex].to])
        {
            tree[edge[prex].to].depth=tree[nownode].depth+1;
            tree[edge[prex].to].father=nownode;
            BuildTree(edge[prex].to);
        }
        prex=edge[prex].pre;
    }
}

inline int LCA(int u,int v)
{
    for (int i=21;i>=0;i--) if (tree[l[u][i]].depth>=tree[v].depth) u=l[u][i];
    if (u==v) return u;
    for (int i=21;i>=0;i--) if (l[u][i]!=l[v][i])
    {
        v=l[v][i]; u=l[u][i];
    }
    return tree[u].father;
}

inline void process(int nownode)
{
    vis[nownode]=1;
    int prex=pointer[nownode];
    while (prex)
    {
        if (!vis[edge[prex].to]) 
        {
            process(edge[prex].to);
            spr[nownode]+=spr[edge[prex].to];
        }
        prex=edge[prex].pre;
    }
}

int main()
{
    readx(nodenum);
    for (int i=1;i<=nodenum;i++) readx(opt[i]);
    for (int i=1;i<nodenum;i++)
    {
        readx(fx); readx(tx);
        Insert();
    }
    
    tree[1].depth=1;
    BuildTree(1);
    
    for (int i=1;i<nodenum;i++)
    {
        u=opt[i]; v=opt[i+1];
        
        if (tree[u].depth<tree[v].depth) 
        {
            swap(u,v);
            uvlca=LCA(u,v);
            swap(u,v);
        }
        else uvlca=LCA(u,v);
        
        spr[u]+=1;	spr[tree[v].father]+=1;
        spr[uvlca]-=1; spr[tree[uvlca].father]-=1;
    }

    memset(vis,0,sizeof(vis));
    process(1);
    
    for (int i=1;i<=nodenum;i++) printf("%d\n",spr[i]);
    return 0;
}