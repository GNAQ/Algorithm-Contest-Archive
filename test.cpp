#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<vector>
#include<array>
#define ll long long
using namespace std;

struct SegTree
{
    int l,r,mid,val,tag;
}SGT[400010]={0};
int _l,_r,_v,_p;

int n,W,H;
vector< array<int,4> >vec;
int xi[20010],yi[20010],xl,yl;

struct _Node { int pos,val,up; };
vector< _Node > node[20010];

void readx(int& x)
{
    x=0; int k=1; char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

void BuildTree(int lxx,int rxx,int inx)
{
    SGT[inx].l=lxx; SGT[inx].r=rxx;
    if (lxx==rxx) return;
    SGT[inx].mid=(lxx+rxx)>>1;
    BuildTree(lxx,SGT[inx].mid,inx<<1);
    BuildTree(SGT[inx].mid+1,rxx,inx<<1|1);
}
void pushdown(int inx)
{
    SGT[inx<<1].val+=SGT[inx].tag;
    SGT[inx<<1|1].val+=SGT[inx].tag;
    SGT[inx<<1].tag+=SGT[inx].tag;
    SGT[inx<<1|1].tag+=SGT[inx].tag;
    SGT[inx].tag=0;
}
void upd(int inx)
{
    if (SGT[inx].l>=_l && SGT[inx].r<=_r)
    {
        SGT[inx].val+=_v;
        SGT[inx].tag+=_v;
        return;
    }
    if (SGT[inx].tag) pushdown(inx);
    if (_l<=SGT[inx].mid) upd(inx<<1);
    if (_r>SGT[inx].mid) upd(inx<<1|1);
    SGT[inx].val=max(SGT[inx<<1].val,SGT[inx<<1|1].val);
}

void _init()
{
    sort(xi+1,xi+2*n+1); sort(yi+1,yi+2*n+1);
    xl=unique(xi+1,xi+2*n+1)-xi-1;
    yl=unique(yi+1,yi+2*n+1)-yi-1;
    
    int cx,cy,cu;
    for (auto i:vec)
    {
        cx=lower_bound(xi+1,xi+xl+1,i[0])-xi;
        cy=lower_bound(yi+1,yi+yl+1,i[1])-yi;
        cu=lower_bound(yi+1,yi+yl+1,i[2])-yi;
        node[cx].push_back({cy,i[3],cu});
    }
    for (int i=1;i<=xl;i++) 
        sort(node[i].begin(),node[i].end(),[](_Node a,_Node b){ if (a.pos==b.pos) return a.val>b.val; return a.pos<b.pos; } );
}

int main()
{
    int _T; readx(_T);
    while (_T--)
    {
    int cac1;
    readx(n); readx(W); readx(H);
    for (int i=1;i<=n;i++)
    {
        readx(xi[i]); readx(yi[i]); readx(cac1);
        xi[i+n]=xi[i]+W;
        yi[i+n]=yi[i]+H-1;
        vec.push_back({xi[i],yi[i],yi[i]+H-1,cac1});
        vec.push_back({xi[i+n],yi[i],yi[i]+H-1,-cac1});
    }
    _init(); BuildTree(1,yl,1);
    
    auto ans=0;
    for (int i=1;i<=xl;i++)
    {
        for (auto x:node[i])
        {
            _l=x.pos; _r=x.up; _v=x.val;
            upd(1);
        }
        ans=max(ans,SGT[1].val);
    }
    cout<<ans<<endl;
    }
    return 0;
}