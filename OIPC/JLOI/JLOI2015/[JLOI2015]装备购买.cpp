// luogu-judger-enable-o2
#include<cstdio>
#include<string>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<iostream>
#include<queue>
#include<vector>
#include<map>
#include<set>
#include<cstdlib>
#define ll long long
#define MOD 1000000007
using namespace std;

int n,m;
struct _mats
{
    ll a[510];
    int w;
    bool operator < (const _mats& a) const { return w<a.w; }
}mat[510];
int p[510]={0},ans1=0,ans2=0;

inline void readx(int& x)
{
    x=0; int k=1; register char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

inline ll fastpow(ll an,ll p,ll mo)
{
    ll ret=1;
    for (;p;p>>=1,an=(an*an)%mo) if (p&1) ret=(ret*an)%mo;
    return ret;
}

inline void Gauss_Elimination_of_Liner_Base()
{
    ll baze;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
        {
            if (!mat[i].a[j]) continue;
            if (!p[j])
            {
                p[j]=i;
                ans1++; ans2+=mat[i].w;
                break;
            }
            else
            {
                baze=(mat[i].a[j]*fastpow(mat[p[j]].a[j],MOD-2,MOD))%MOD;
                for (int k=1;k<=m;k++) mat[i].a[k]=(mat[i].a[k]-(baze*mat[p[j]].a[k])%MOD+MOD)%MOD;
            }
        }
}

int main()
{
    readx(n); readx(m); register int cac;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++) { readx(cac); mat[i].a[j]=(double)cac; }
    for (int i=1;i<=n;i++) readx(mat[i].w);
    sort(mat+1,mat+n+1);
    Gauss_Elimination_of_Liner_Base();
    printf("%d %d\n",ans1,ans2);
    return 0;
}