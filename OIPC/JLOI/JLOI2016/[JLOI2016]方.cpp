// luogu-judger-enable-o2
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<iterator>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<set>
#define ll long long
#define mod 100000007
using namespace std;

struct Point
{
    ll x,y;
    Point(){}
    Point(ll _x,ll _y) { x=_x; y=_y; }
    bool operator == (const Point& a) const { return (x==a.x)&&(y==a.y); }
    bool operator < (const Point& a) const { if (x==a.x) return y<a.y; return x<a.x; }
};
ll n,m,K;
Point pt[2010]; set<Point> ss;

ll ans=0,t2=0,t3=0,t4=0;

inline void readx(ll& x)
{
    x=0; ll k=1; register char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

inline bool inmap(ll _x,ll _y) { return ((_x>=0)&(_y>=0)&(_x<=n)&(_y<=m)); }

inline ll calc_lr(ll l,ll r,ll h)
{
    ll z=min(l+r,h);
    if (!z) return 0;
    ll ret=(1LL*z*(z+3))/2LL;
    if (z>l) ret-=(1LL*(z-l)*(z-l+1))/2LL;
    if (z>r) ret-=(1LL*(z-r)*(z-r+1))/2LL;
    return ret;
}
inline ll calc_1(Point& p)
{
    int l=p.x, r=n-p.x, u=m-p.y, d=p.y;
    ll ret=min(l,u)+min(l,d)+min(r,d)+min(r,u); ret=-ret;
    ret+=calc_lr(l,r,u)+calc_lr(l,r,d)+calc_lr(u,d,r)+calc_lr(u,d,l);
    return ret%mod;
}
inline void calc_234(Point a,Point b)
{
    if ((!inmap(a.x,a.y)) || (!inmap(b.x,b.y))) return;
    t2++;
    ll tmp=ss.count(a)+ss.count(b);
    if (tmp>0) t3++;
    if (tmp>1) { t3++; t4++; }
}


int main()
{
    readx(n); readx(m); readx(K);
    for (int i=1;i<=K;i++) { readx(pt[i].x); readx(pt[i].y); }
    for (int i=1;i<=K;i++) ss.insert(pt[i]);
    
    ll upat=min(n,m);
    Point pp1,pp2; ll dx,dy;
    
    for (int i=1;i<=upat;i++) ans=(ans+i*((n-i+1)*(m-i+1))%mod)%mod; //0
    for (int i=1;i<=K;i++) ans-=calc_1(pt[i]);                       //1
    for (int i=1;i<=K;i++)
    {
        pp1=pt[i];
        for (int j=i+1;j<=K;j++)
        {
            pp2=pt[j];
            dx=pp1.x-pp2.x; dy=pp1.y-pp2.y;
            calc_234(Point(pp1.x+dy,pp1.y-dx),Point(pp2.x+dy,pp2.y-dx));
            calc_234(Point(pp1.x-dy,pp1.y+dx),Point(pp2.x-dy,pp2.y+dx));
            if((abs(dx)+abs(dy))&1) continue;
            ll _x=(dx-dy)>>1,_y=(dx+dy)>>1;
            calc_234(Point(pp1.x-_x,pp1.y-_y),Point(pp2.x+_x,pp2.y+_y));
        }
    }
    ans=(ans+t2-(t3/3)+(t4/6))%mod;
    ans=(ans+mod)%mod;
    printf("%lld\n",ans);
}