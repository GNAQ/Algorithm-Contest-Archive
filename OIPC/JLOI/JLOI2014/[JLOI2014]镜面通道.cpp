// luogu-judger-enable-o2
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<iterator>
#include<vector>
#include<queue>
#include<map>
#include<set>
#define ll long long
#define eps 1e-8
using namespace std;

struct ed
{
    int pre,to,capx;
}edge[360010]={0};
int n,m,at=1,ptr[1010]={0},tt=1002,ss;

queue<int> que;
int cur[1010]={0},level[1010]={0};

struct _square { int x[4],y[4]; }S[310];
struct _circle { int x,y,r; }C[310];
int Cr=0,Sr=0;

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
inline char BFS()
{
    int cac=0;
    memset(level,0,sizeof level);
    que.push(ss); level[ss]=1;
    while (!que.empty())
    {
        cac=que.front(); que.pop();
        for (int prex=ptr[cac];prex;prex=edge[prex].pre) if ((!level[edge[prex].to]) && edge[prex].capx)
        {
            level[edge[prex].to]=level[cac]+1;
            que.push(edge[prex].to);
        }
    }
    if (!level[tt]) return false;
    memcpy(cur,ptr,sizeof ptr);
    return true;
}
inline int DFS(int now,int minf)
{
    if ((!minf) || now==tt) return minf;
    int sumf=0,needf;
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

inline double dist(int _x1,int _y1,int _x2,int _y2) { return sqrt((_x1-_x2)*(_x1-_x2)+(_y1-_y2)*(_y1-_y2)); }
inline bool Judge1(_circle a,_circle b) { return dist(a.x,a.y,b.x,b.y)<=(double)(a.r+b.r); }
inline bool Judge2(_circle a,_square b)
{
    for (int i=0;i<=3;i++) if (dist(a.x,a.y,b.x[i],b.y[i])<=(double)a.r) return true;
    if (a.x>=b.x[0] && a.x<=b.x[3] && a.y+a.r<=b.y[3] && a.y+a.r>=b.y[0]) return true;
    if (a.x>=b.x[0] && a.x<=b.x[3] && a.y-a.r<=b.y[3] && a.y-a.r>=b.y[0]) return true;
    if (a.y>=b.y[0] && a.y<=b.y[3] && a.x+a.r>=b.x[0] && a.x+a.r<=b.x[3]) return true;
    if (a.y>=b.y[0] && a.y<=b.y[3] && a.x-a.r>=b.x[0] && a.x-a.r<=b.x[3]) return true;
    return false;
}
inline bool Judge3(_square a,_square b)
{
    for (int i=0;i<=3;i++)
    {
        int _x=a.x[i],_y=a.y[i];
        if ( _x>=b.x[0] && _x<=b.x[3] && _y>=b.y[0] && _y<=b.y[3] ) return true;
    }
    return false;
}

int main()
{
    int typ,c_x,c_y;
    readx(c_x); readx(c_y); readx(n);
    for (int i=1;i<=n;i++)
    {
        readx(typ);
        if (typ==1) { Cr++; readx(C[Cr].x); readx(C[Cr].y); readx(C[Cr].r); }
        else
        {
            Sr++;
            readx(S[Sr].x[0]); readx(S[Sr].y[0]); readx(S[Sr].x[3]); readx(S[Sr].y[3]);
            S[Sr].x[1]=S[Sr].x[0]; S[Sr].y[1]=S[Sr].y[3];
            S[Sr].x[2]=S[Sr].x[3]; S[Sr].y[2]=S[Sr].y[0];
        }
    }
    
    for (int i=1;i<=Cr;i++)
    {
        for (int j=i+1;j<=Cr;j++) if (Judge1(C[i],C[j]))
            { Insert(Cr+i,j,2*1e9); Insert(Cr+j,i,2*1e9); }
            
        for (int j=1;j<=Sr;j++) if (Judge2(C[i],S[j]))
            { Insert(Cr+i,2*Cr+j,2*1e9); Insert(2*Cr+Sr+j,i,2*1e9); }
            
        if (C[i].y<=C[i].r) Insert(ss,i,2*1e9);
        if (C[i].y+C[i].r>=c_y) Insert(Cr+i,tt,2*1e9);
    }
    for (int i=1;i<=Sr;i++)
    {
        for (int j=i+1;j<=Sr;j++) if (Judge3(S[i],S[j]))
            { Insert(2*Cr+Sr+i,2*Cr+j,2*1e9); Insert(2*Cr+Sr+j,2*Cr+i,2*1e9); }
            
        if (S[i].y[0]<=0) Insert(ss,2*Cr+i,2*1e9);
        if (S[i].y[3]>=c_y) Insert(2*Cr+Sr+i,tt,2*1e9);
    }
    for (int i=1;i<=Cr;i++) Insert(i,i+Cr,1);
    for (int i=1;i<=Sr;i++) Insert(2*Cr+i,2*Cr+Sr+i,1);
    
    int ans=0;
    while (BFS()) ans+=DFS(ss,2*1e9);
    printf("%d\n",ans);
    return 0;
}