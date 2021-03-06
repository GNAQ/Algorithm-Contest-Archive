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
#include<cstdlib>
#include<map>
#include<set>
#define ll long long
#define ull unsigned long long
using namespace std;

const ll mod=7528443412579576937;
ll N,B,D;

inline ull MUL(ll x,ll y)
{
    ll tmp=(x*y-(ll)((long double)x/mod*y+1.0e-8)*mod);
    return tmp<0 ? tmp+mod : tmp;
}

struct _Mat
{
    ull e[3][3];
    _Mat() { memset(e,0,sizeof(e)); }
    _Mat operator * (_Mat b)
    {
        _Mat c;
        for (int i=1;i<=2;i++)
            for (int j=1;j<=2;j++)
                for (int k=1;k<=2;k++) c.e[i][j]=(c.e[i][j]+MUL(e[i][k],b.e[k][j]))%mod;
        return c;
    }
};

inline void readx(ll& x)
{
    x=0; ll k=1; register char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

inline _Mat fastpow(_Mat an,ll p)
{
    _Mat ret; ret.e[1][1]=ret.e[2][2]=1;
    for (;p;p>>=1,an=an*an) if (p&1) ret=ret*an;
    return ret;
}

int main()
{
    readx(B); readx(D); readx(N);
    if (!N) { printf("1\n"); return 0; }
    _Mat qwq;
    qwq.e[1][1]=B; qwq.e[1][2]=(D-B*B)/4;
    qwq.e[2][1]=1; qwq.e[2][2]=0;
    qwq=fastpow(qwq,N-1);
    ull ans=MUL(B,qwq.e[1][1])+MUL(2LL,qwq.e[1][2]); if (ans>mod) ans-=mod;
    if (!(N&1)) if (B*B!=D) ans-=1;
    printf("%lld\n",ans);
    return 0;
}