// luogu-judger-enable-o2
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<vector>
#include<queue>
#include<map>
#include<set>
#define ll long long
#define LCH llt[_x].ch[0]
#define RCH llt[_x].ch[1]
using namespace std;

struct Leftlist_Tree{ ll MT,AT,ch[2],val,dist; }llt[300010];
ll n,m,R[300010]={0};

struct ed { int pre,to; }edge[600010]={0};
int at=0,ptr[300010]={0};

struct _Node { ll h,typ,val,dep; }node[300010]={0};
ll S[300010]={0},ans1[300010],ans2[300010];

inline void readx(ll& x)
{
    x=0; ll k=1; register char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

inline void Insert(int fx,int tx)
{
    at++;
    edge[at].pre=ptr[fx];
    edge[at].to=tx;
    ptr[fx]=at;
}

inline void Change(int _x,ll mu,ll ad)
{
    if (!_x) return;
    llt[_x].val=(llt[_x].val*mu)+ad;
    llt[_x].MT*=mu; llt[_x].AT=(llt[_x].AT*mu)+ad;
}

inline void Pushdown(int _x)
{
    Change(LCH,llt[_x].MT,llt[_x].AT);
    Change(RCH,llt[_x].MT,llt[_x].AT);
    llt[_x].MT=1; llt[_x].AT=0;
}

inline int _Merge(int _x,int _y)
{
    if ((!_x) || (!_y)) return _x+_y;
    if (llt[_x].val>llt[_y].val) swap(_x,_y);
    Pushdown(_x); Pushdown(_y);
    
    RCH=_Merge(RCH,_y);
    
    if (llt[RCH].dist>llt[LCH].dist) swap(LCH,RCH);
    llt[_x].dist=llt[RCH].dist+1;
    return _x;
}

inline void DFS(int now,int fa)
{
    node[now].dep=node[fa].dep+1;
    for (int prex=ptr[now];prex;prex=edge[prex].pre)
    {
        DFS(edge[prex].to,now);
        R[now]=_Merge(R[now],R[edge[prex].to]);
    }
    while (R[now] && llt[R[now]].val<node[now].h)
    {
        Pushdown(R[now]);
        ans1[now]++;
        ans2[R[now]]=node[S[R[now]]].dep-node[now].dep;
        R[now]=_Merge(llt[R[now]].ch[0],llt[R[now]].ch[1]);
    }
    if (node[now].typ) Change(R[now],node[now].val,0);
    else Change(R[now],1,node[now].val);
}

int main()
{
    llt[0].dist=-1; ll cac=0;
    readx(n); readx(m);
    for (int i=1;i<=n;i++) readx(node[i].h);
    for (int i=2;i<=n;i++)
    {
        readx(cac); Insert(cac,i);
        readx(node[i].typ); readx(node[i].val);
    }
    for (int i=1;i<=m;i++)
    {
        readx(llt[i].val); readx(S[i]); llt[i].MT=1;
        R[S[i]]=_Merge(R[S[i]],i);
    }
    
    DFS(1,0);
    
    while (R[1])
    {
        Pushdown(R[1]);
        ans2[R[1]]=node[S[R[1]]].dep;
        R[1]=_Merge(llt[R[1]].ch[0],llt[R[1]].ch[1]);
    }
    
    for (int i=1;i<=n;i++) printf("%lld\n",ans1[i]);
    for (int i=1;i<=m;i++) printf("%lld\n",ans2[i]);
    return 0;
}
