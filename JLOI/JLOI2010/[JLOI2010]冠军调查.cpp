// luogu-judger-enable-o2
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cstdlib>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<map>
#include<set>
#include<queue>
#include<vector>
#define ll long long
using namespace std;

struct ed
{
    int pre,to,capx;
}edge[500010]={0};
int n,m,at=1,ptr[500]={0},ss,tt;

int level[500]={0},cur[500]={0};
queue<int> que;

inline void readx(int& x)
{
    x=0; int k=1; register char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

inline void Insert(int fx,int tx,int cx)
{
    at++;
    edge[at].pre=ptr[fx];
    edge[at].to=tx;
    edge[at].capx=cx;
    ptr[fx]=at;
    at++;
    edge[at].pre=ptr[tx];
    edge[at].to=fx;
    ptr[tx]=at;
}

inline int BFS()
{
    register int cac;
    for (int i=ss;i<=tt;i++) cur[i]=ptr[i];
    memset(level,0,sizeof level);
    level[ss]=1; que.push(ss);
    while (!que.empty())
    {
        cac=que.front(); que.pop();
        for (int prex=ptr[cac];prex;prex=edge[prex].pre)
            if ((!level[edge[prex].to]) && edge[prex].capx)
            {
                level[edge[prex].to]=level[cac]+1;
                que.push(edge[prex].to);
            }
    }
    return level[tt];
}	
inline int DFS(int now,int minf)
{
    if ((!minf) || now==tt) return minf;
    int sumf=0,needf=0;
    for (int prex=cur[now];prex;prex=edge[prex].pre)
    {
        cur[now]=prex;
        if (level[edge[prex].to]==level[now]+1)
            if (needf=DFS(edge[prex].to,min(minf,edge[prex].capx)))
            {
                sumf+=needf; minf-=needf;
                edge[prex].capx-=needf; edge[prex^1].capx+=needf;
                if (!minf) break;
            }
    }
    return sumf;
}

int main()
{
    readx(n); readx(m); tt=n+2; register int fx,tx,cx;
    for (int i=1;i<=n;i++)
    {
        readx(cx);
        if (cx) Insert(i,tt,1);
        else Insert(ss,i,1);
    }
    for (int i=1;i<=m;i++)
    {
        readx(fx); readx(tx);
        Insert(fx,tx,1); Insert(tx,fx,1);
    }
    int ansf=0;
    while (BFS()) ansf+=DFS(ss,2*1e9);
    printf("%d\n",ansf);
}