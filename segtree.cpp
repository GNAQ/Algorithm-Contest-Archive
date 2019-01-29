#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<queue>
#include<cstdlib>
#include<vector>
#include<map>
#include<set>
typedef long long ll;
using namespace std;

int n,m,seq[100010],;
struct Operate { int id,typ,l,r; } op[100010];

template<typename int_t>
void readx(int_t& x)
{
    x=0; int_t k=1; char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

namespace SGT
{
    #define LCH (inx<<1)
    #define RCH (inx<<1|1)
    
    struct Seg_Tree
    {
        int l,r,mid,val,tag;
    }tree[4000010];
    int lx,rx,_pos,_val,_typ;
    
    void Pushdown(int inx)
    {
        int tmp=tree[inx].tag; tree[inx].tag=0;
        tree[LCH].tag=tree[RCH].tag=tmp;
        if (tmp==1)
            tree[LCH].val=tree[RCH].val=0;
        else
        {
            tree[LCH].val=(tree[LCH].r-tree[LCH].l+1);
            tree[RCH].val=(tree[RCH].r-tree[RCH].l+1);
        }
    }
    
    void BuildTree(int inx,int lxx,int rxx,int* seq)
    {
        tree[inx].l=lxx; tree[inx].r=rxx; tree[inx].mid=(lxx+rxx)>>1;
        if (lxx==rxx)
        {
            tree[inx].val=seq[lxx];
            return;
        }
        BuildTree(LCH,lxx,tree[inx].mid,seq);
        BuildTree(RCH,tree[inx].mid+1,rxx,seq);
        tree[inx].val=(tree[LCH].val+tree[RCH].val);
    }
    
    void Upd(int inx)
    {
        if (tree[inx].l>=lx && tree[inx].r<=rx)
        {
            tree[inx].tag=_typ;
            if (_typ==1) tree[inx].val=0;
            else tree[inx].val=(tree[inx].r-tree[inx].l+1);
            return;
        }
        if (tree[inx].tag) Pushdown(inx);
        if (lx<=tree[inx].mid) Upd(LCH);
        if (rx>tree[inx].mid) Upd(RCH);
        tree[inx].val=(tree[LCH].val+tree[RCH].val);
    }
    
    int Qry(int inx)
    {
        if (tree[inx].l>=lx && tree[inx].r<=rx) return tree[inx].val;
        if(tree[inx].tag) Pushdown(inx);
        int ret=0;
        if (lx<=tree[inx].mid) ret+=Qry(LCH);
        if (rx>tree[inx].mid) ret+=Qry(RCH);
        tree[inx].val=(tree[LCH].val+tree[RCH].val);
        return ret;
    }
    
    #undef LCH
    #undef RCH
};

void Solve(int lb,int rb)
{
    int mid,ret;
    while (lb<=rb)
    {
        mid=(lb+rb)>>1;
        
        for (int i=1;i<=n;i++) 
        
        if () { ret=mid; lb=mid+1; }
        else rb=mid-1; 
    }
}

int main()
{
    readx(n); readx(m);
    for (int i=1;i<=n;i++) readx(seq[i]);
    for (int i=1;i<=m;i++)
    {
        readx(op[i].typ); 
        readx(op[i].l); readx(op[i].r);
    }
    
    Solve();
}