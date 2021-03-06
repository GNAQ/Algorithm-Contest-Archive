// luogu-judger-enable-o2
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#define ll long long
#define inline __attribute((always_inline))
using namespace std;

const ll mod=1000000007;
ll n,m,ans;
ll fac[3000010]={0};

inline void readx(ll& x)
{
    x=0; ll k=1; register char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

inline ll fastpow(ll an,ll p)
{
    ll ret=1;
    for (;p;p>>=1,an=(an*an)%mod) if (p&1) ret=(ret*an)%mod;
    return ret;
}

inline ll C(int N,int M)
{
    if (M<0 || M>N) return 0;
    return (fac[N]*fastpow((fac[M]*fac[N-M])%mod,mod-2))%mod;
}

//A: y=x+1
//B: y=x-m-2

inline void _init()
{
    fac[0]=1;
    for (int i=1;i<=3000000;i++) fac[i]=(fac[i-1]*(ll)i)%mod;
}

inline void Change(ll& _x,ll& _y,ll mode)
{
    swap(_x,_y);
    if (!mode) { _x--; _y++; }
    else { _x+=m+2; _y-=(m+2); }
}

int main()
{
    readx(n); readx(m); _init();
    ans=C(2*n+m+1,n);
    
    ll _x=n+m+1,_y=n,_mode=0;
    while (1)
    {
        Change(_x,_y,_mode);
        if (_x<0 || _y<0) break;
        if (!_mode) ans=(ans - C(_x+_y,_x))%mod;
        else ans=(ans + C(_x+_y,_x))%mod;
        _mode^=1;
    }
    _x=n+m+1,_y=n,_mode=1;
    while (1)
    {
        Change(_x,_y,_mode);
        if (_x<0 || _y<0) break;
        if (!_mode) ans=(ans + C(_x+_y,_x))%mod;
        else ans=(ans - C(_x+_y,_x))%mod;
        _mode^=1;
    }
    ans=(ans%mod+mod)%mod;
    printf("%lld\n",ans);
    return 0;
}