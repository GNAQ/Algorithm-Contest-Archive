// luogu-judger-enable-o2
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<iterator>
#include<cmath>
#include<string>
#include<queue>
#include<vector>
#include<map>
#include<set>
#define ll long long
using namespace std;

struct Segment_tree
{
    ll l,r,val;
}SGT[800010]={0};
ll lx,rx;
ll valu,lastans,mo;
char chs;

ll n,m,len,nowp;

inline void readx(ll& x)
{
    x=0; ll k=1; register char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

inline void BuildTree(int lxx,int rxx,int inx)
{
    SGT[inx].l=lxx; SGT[inx].r=rxx; SGT[inx].val=-2*1e14;
    if (lxx==rxx) return;
    int mid=(lxx+rxx)>>1;
    BuildTree(lxx,mid,inx<<1);
    BuildTree(mid+1,rxx,inx<<1|1);
}

inline void updatex(int inx)
{
    if (SGT[inx].l==SGT[inx].r) { SGT[inx].val=valu; return; }
    int mid=(SGT[inx].l+SGT[inx].r)>>1;
    if (lx<=mid) updatex(inx<<1);
    else updatex(inx<<1|1);
    SGT[inx].val=max(SGT[inx<<1].val,SGT[inx<<1|1].val);
}

inline ll queryx(int inx)
{
    if (SGT[inx].l>=lx && SGT[inx].r<=rx) return SGT[inx].val;
    int mid=(SGT[inx].r+SGT[inx].l)>>1;
    ll ret=-2*1e17;
    if (lx<=mid) ret=max(ret,queryx(inx<<1));
    if (rx>mid) ret=max(ret,queryx(inx<<1|1));
    return ret;
}

int main()
{
    cin>>n>>mo;
    BuildTree(1,n,1);
    for (int i=1;i<=n;i++)
    {
        cin>>chs;
        if (chs=='Q')
        {
            cin>>lx;
            if (!lx) 
            {
                printf("%lld\n",lastans=0);
                continue;
            }
            rx=nowp; lx=nowp-lx+1;
            printf("%lld\n",lastans=queryx(1));
        }
        else
        {
            cin>>valu;
            valu=(valu+lastans)%mo;
            lx=rx=++nowp;
            updatex(1);
        }
        chs=0;
    }
    return 0;
}
