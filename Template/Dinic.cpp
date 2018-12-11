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

int n,m;
struct ed
{
    int pre,to,capx;
}edge[200010];
int at=1,ptr[100010];
int ss,tt;

template<typename int_t>
void readx(int_t& x)
{
    x=0; int_t k=1; char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

void Is(int fx,int tx,int cx)
{
    edge[++at].pre=ptr[fx];
    edge[at].to=tx;
    edge[at].capx=cx;
    ptr[fx]=at;
    edge[++at].pre=ptr[tx];
    edge[at].to=fx;
    ptr[tx]=at;
}

int lvl[100010],cac1,cur[100010];
queue<int> que;
int BFS()
{
    memset(lvl,0,sizeof lvl); lvl[ss]=1; que.push(ss);
    while (!que.empty())
    {
        cac1=que.front(); que.pop();
        for (int e=ptr[cac1];e;e=edge[e].pre) if (!lvl[edge[e].to] && edge[e].capx)
        {
            lvl[edge[e].to]=lvl[cac1]+1;
            que.push(edge[e].to);
        }
    }
    if (!lvl[tt]) return false;
    memcpy(cur,ptr,sizeof cur);
    return true;
}

int DFS(int now,int minf)
{
    if (!minf || now==tt) return minf;
    int needf,sumf=0;
    for (int e=cur[now];e;e=edge[e].pre) if (lvl[edge[e].to]==lvl[now]+1)
    {
        cur[now]=e;
        if (needf=DFS(edge[e].to,min(minf,edge[e].capx)))
        {
            sumf+=needf; minf-=needf;
            edge[e].capx-=needf; edge[e^1].capx+=needf;
            if (!minf) break;
        }
    }
    return sumf;
}

int main()
{
    readx(n); readx(m); readx(ss); readx(tt); int fx,tx,cx;
    for (int i=1;i<=m;i++)
    {
        readx(fx); readx(tx); readx(cx);
        Is(fx,tx,cx);
    }
    
    int ans=0;
    while (BFS()) ans+=DFS(ss,2*1e9);
    cout<<ans<<endl;
}
