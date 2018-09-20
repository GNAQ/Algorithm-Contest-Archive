// luogu-judger-enable-o2
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<cmath>
#include<iostream>
#define ll long long
using namespace std;
struct circ { int x,y,r; }cir[200010];
struct _Nodes
{
    int x,cod,typ;
    _Nodes(){}
    _Nodes(int inx,int icod,int ityp) : x(inx), cod(icod), typ(ityp){}
}node[400010];
int n,ctr,cntX; int sta[200010];
set<_Nodes> ss;

inline void readx(int& x)
{
    x=0; int k=1; register char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

inline double gety(const _Nodes& a) { return cir[a.cod].y+a.typ*sqrt((double)cir[a.cod].r*cir[a.cod].r-(double)(cir[a.cod].x-cntX)*(cir[a.cod].x-cntX)); }
inline char operator < (const _Nodes& a,const _Nodes& b) { double _a=gety(a),_b=gety(b); return (_a!=_b)? _a<_b : a.typ<b.typ; }

inline void QuickSort(const int& l,const int& r)
{
    int i=l,j=r; _Nodes mid=node[(l+r)>>1];
    while (i<=j)
    {
        while (node[i].x<mid.x) i++;
        while (node[j].x>mid.x) j--;
        if (i<=j)
        {
            swap(node[i],node[j]);
            i++; j--;
        }
    }
    if (l<j) QuickSort(l,j);
    if (i<r) QuickSort(i,r);
}

int main()
{
    readx(n);
    for (int i=1;i<=n;i++) { readx(cir[i].x); readx(cir[i].y); readx(cir[i].r); }
    for (int i=1;i<=n;i++)
    {
        node[++ctr]=_Nodes(cir[i].x-cir[i].r,i,1);
        node[++ctr]=_Nodes(cir[i].x+cir[i].r,i,-1);
    }
    QuickSort(1,ctr);
    
    set<_Nodes>::iterator itr;
    register ll cac=0;
    for (int i=1;i<=ctr;i++)
    {
        cntX=node[i].x; cac=node[i].cod;
        if (node[i].typ==1)
        {
            itr=ss.upper_bound(_Nodes(0,cac,-1));
            
            if (itr==ss.end()) sta[cac]=1;
            else
            {
                if ((*itr).typ==1) sta[cac]=-sta[(*itr).cod];
                else sta[cac]=sta[(*itr).cod];
            }
            ss.insert(_Nodes(0,cac,1)); ss.insert(_Nodes(0,cac,-1));
        }
        else
        {
            ss.erase(_Nodes(0,cac,1));
            ss.erase(_Nodes(0,cac,-1));
        }
    }
    ll ans=0;
    for (int i=1;i<=n;i++) ans+=1LL*cir[i].r*cir[i].r*sta[i];
    printf("%lld\n",ans);
    return 0;
}