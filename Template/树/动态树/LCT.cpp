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
#define LCH tree[pos].ch[0]
#define RCH tree[pos].ch[1]
using namespace std;

struct splay_tree { int fa,ch[2],val,rev; } tree[300010]={0};
int troo,tsiz=0,n,m;
int opt,cachex,cachey;
int seq[300010]={0};

inline void readx(int& x)
{
    x=0; int k=1; register char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

inline void updata(int pos) { tree[pos].val=tree[LCH].val^tree[RCH].val^seq[pos]; }
inline void PutRev(int pos)
{
    swap(LCH,RCH);
    tree[LCH].rev^=1; 
	tree[RCH].rev^=1;
}
inline void pushdown(int pos)
{
    if (!tree[pos].rev) return;
    if (LCH) tree[LCH].rev^=1; 
    if (RCH) tree[RCH].rev^=1;
    swap(LCH,RCH); tree[pos].rev^=1;
}
inline bool NaNroot(int pos) { return (tree[tree[pos].fa].ch[0]==pos || tree[tree[pos].fa].ch[1]==pos); }
inline void Push_All(int pos)
{
    if (NaNroot(pos)) Push_All(tree[pos].fa);
    pushdown(pos);
}

inline void rotatex(int pos)
{
    int f=tree[pos].fa,g=tree[f].fa,flag=(tree[f].ch[1]==pos);
    
    if (NaNroot(f)) tree[g].ch[(tree[g].ch[1]==f)]=pos;
    if (tree[pos].ch[!flag]) tree[tree[pos].ch[!flag]].fa=f;
    tree[f].ch[flag]=tree[pos].ch[!flag]; tree[f].fa=pos;
    tree[pos].ch[!flag]=f; tree[pos].fa=g;
    
    updata(f); updata(pos);
}
inline void splay(int pos)
{
    Push_All(pos);
    for (;NaNroot(pos);rotatex(pos))
    {
        if (NaNroot(tree[pos].fa))
        {
            int g=tree[tree[pos].fa].fa;
            if ((tree[g].ch[1]==tree[pos].fa)==(tree[tree[pos].fa].ch[1]==pos)) rotatex(tree[pos].fa);
            else rotatex(pos);
        }
    }
}

inline void Access(int pos)
{
    for (int ch=0;pos;pos=tree[ch=pos].fa) 
        { splay(pos); RCH=ch; updata(pos); }
}
inline void Makeroot(int pos)
{
    Access(pos);
	splay(pos); PutRev(pos);
}
inline int Findroot(int pos)
{
    Access(pos); splay(pos);
    while (LCH) { pushdown(pos); pos=LCH; }
    splay(pos); return pos;
}
inline void Split(int x,int y)
{
    Makeroot(x);
	Access(y); splay(y);
}
inline int Link(int x,int y)
{
    Makeroot(x); 
    if (Findroot(y)==x) return -1;
    tree[x].fa=y; return 1;
}
inline int Cut(int x,int y)
{
    Makeroot(x);
    if (Findroot(y)==x && tree[y].fa==x && (!tree[y].ch[0]))
        { tree[y].fa=tree[x].ch[1]=0; updata(x); return 1; }
    return -1;
}

int main()
{
    readx(n); readx(m);
    for (int i=1;i<=n;i++) readx(seq[i]);
    for (int i=1;i<=m;i++)
    {
        readx(opt); readx(cachex); readx(cachey);
        if (opt==0)
        {
            Split(cachex,cachey);
            printf("%d\n",tree[cachey].val);
        }
        else if (opt==1) Link(cachex,cachey);
        else if (opt==2) Cut(cachex,cachey);
        else { splay(cachex); seq[cachex]=cachey; updata(cachex); }
    }
    return 0;
}