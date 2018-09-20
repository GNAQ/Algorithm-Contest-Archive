#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#define ll long long
using namespace std;
 
struct Seg_tree { int mid,l,r,val,siz; }SGT[400010]={0};
int lx,rx,_pos;
int seq[200010]={0},n,m;
 
inline void readx(int& x)
{
    x=0; int k=1; register char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}
 
inline void BuildTree(int _l,int _r,int inx)
{
    SGT[inx].l=_l; SGT[inx].r=_r;
    if (_l==_r) { SGT[inx].val=seq[_l]; SGT[inx].siz=1; return; }
    SGT[inx].mid=(_l+_r)>>1;
    BuildTree(_l,SGT[inx].mid,inx<<1);
    BuildTree(SGT[inx].mid+1,_r,inx<<1|1);
    SGT[inx].siz=(SGT[inx<<1].siz+SGT[inx<<1|1].siz);
    SGT[inx].val=max(SGT[inx<<1].val,SGT[inx<<1|1].val);
}
inline int QueryPos(int inx)
{
    if (SGT[inx].l==SGT[inx].r) return SGT[inx].l;
    if (SGT[inx].val==SGT[inx<<1].val) return QueryPos(inx<<1);
    else return QueryPos(inx<<1|1);
}
inline int QuerySize(int inx)
{
    if (SGT[inx].l>=lx && SGT[inx].r<=rx) return SGT[inx].siz;
    int ret=0;
    if (lx<=SGT[inx].mid) ret+=QuerySize(inx<<1);
    if (rx>SGT[inx].mid) ret+=QuerySize(inx<<1|1);
    return ret;
}
inline void update(int inx)
{
    if (SGT[inx].l==SGT[inx].r) { SGT[inx].siz=0; SGT[inx].val=-2*1e9; return; }
    if (_pos<=SGT[inx].mid) update(inx<<1);
    else update(inx<<1|1);
    SGT[inx].siz=SGT[inx<<1].siz+SGT[inx<<1|1].siz;
    SGT[inx].val=max(SGT[inx<<1].val,SGT[inx<<1|1].val);
}
 
int main()
{
    readx(n); readx(m);
    for (int i=n;i;i--) readx(seq[i]);
    for (int i=n+2;i<=m+n+1;i++) readx(seq[i]);
    BuildTree(1,n+m+1,1); _pos=n+1; update(1);
     
    ll _ans=0; int _mid=n+1;
    for (int i=1;i<=m+n;i++)
    {
        _pos=QueryPos(1);
        lx=min(_pos,_mid); rx=max(_pos,_mid);
        _ans+=QuerySize(1)-1; update(1); 
        seq[_pos]=-2*1e9; _mid=_pos;
    }
    printf("%lld\n",_ans);
    return 0;
}