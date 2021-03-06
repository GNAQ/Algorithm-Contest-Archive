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
#define mo 31011
#define ll long long
using namespace std;

struct ed { int fr,to,w; }edge[100010]={0};
struct gr { int w,cnt; } gro[100010]={0};
struct blocks { int lx,rx,num; } blk[100010]={0};
int nodenum,edgenum,mstnum=0,blkm=0,nblk,ans=1,ansx;
int fa[100010]={0};

inline void readx(int& x)
{
    x=0; int k=1; register char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

inline int findx(int e) { if (fa[e]!=e) return findx(fa[e]); return fa[e]; }

inline void dfs(int npos,int used)
{
    if (npos==blk[nblk].rx+1)
    {
        if (used==blk[nblk].num) ansx++;
        return;
    }
    int u=findx(edge[npos].fr),v=findx(edge[npos].to);
    if (u!=v)
    {
        fa[u]=v;
        dfs(npos+1,used+1);
        fa[u]=u; fa[v]=v;
    }
    dfs(npos+1,used);
}

int main()
{
    readx(nodenum); readx(edgenum);
    for (int i=1;i<=edgenum;i++) { readx(edge[i].fr); readx(edge[i].to); readx(edge[i].w); }
    for (int i=1;i<=nodenum;i++) fa[i]=i;
    sort(edge+1,edge+edgenum+1,[](ed a,ed b){return a.w<b.w;});
    
    for (int i=1;i<=edgenum;i++)
    {
        if (edge[i].w!=edge[i-1].w) { blk[blkm].rx=i-1; blk[++blkm].lx=i; }
        if (findx(edge[i].fr)!=findx(edge[i].to))
        {
            fa[findx(edge[i].fr)]=findx(edge[i].to); mstnum++;
            blk[blkm].num++;
        }
    }
    if (mstnum<nodenum-1) { printf("0\n"); return 0; }
    
    blk[blkm].rx=edgenum;
    for (int i=1;i<=nodenum;i++) fa[i]=i;
    
    for (int i=1;i<=blkm;i++)
    {
        nblk=i; ansx=0;
        dfs(blk[i].lx,0); ans=(ans*ansx)%mo;
        for (int j=blk[i].lx;j<=blk[i].rx;j++) if (findx(edge[j].fr)!=findx(edge[j].to)) 
            fa[findx(edge[j].fr)]=findx(edge[j].to);
    }
    
    printf("%d\n",ans);
    return 0;
}
