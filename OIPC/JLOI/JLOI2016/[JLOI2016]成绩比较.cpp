// luogu-judger-enable-o2
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#define ll long long
using namespace std;

const ll mod=1000000007;
ll C[110][110]={0},dp[110][110]={0},g[110]={0};
ll n,m,K,U[110]={0},rk[110]={0};

inline void readx(ll& x)
{
    x=0; ll k=1; register char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

inline ll mmul(ll __a,ll __b) { return (__a*__b)%mod; }
inline ll fastpow(ll an,ll p)
{
    ll ret=1;
    for (;p;p>>=1,an=(an*an)%mod) if (p&1) ret=(ret*an)%mod;
    return ret;
}

inline void _init()
{
    C[0][0]=1;
    for (int i=1;i<=105;i++)
    {
        C[i][0]=1;
        for (int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    }
}

inline ll Lagrange_Itp(ll U,ll R)
{
    memset(g,0,sizeof g);
    for (int i=1;i<105;i++)
        for (int j=1;j<=i;j++) g[i]=(g[i]+ mmul(fastpow(j,n-R),fastpow(i-j,R-1)) )%mod;
    
    ll ret=0;
    for (int i=1;i<105;i++)
    {
        int s1=1,s2=1;
        for (int j=1;j<105;j++) if (i!=j) { s1=mmul(s1,U-j); s2=mmul(s2,i-j); }
        ret=(ret+ mmul(mmul(g[i],s1),fastpow(s2,mod-2)) )%mod;
    }
    return (ret%mod+mod)%mod;
}

int main()
{
    _init();
    readx(n); readx(m); readx(K);
    for (int i=1;i<=m;i++) readx(U[i]);
    for (int i=1;i<=m;i++) readx(rk[i]);
    
    dp[0][n-1]=1;
    for (int i=1;i<=m;i++)
        for (int j=K;j<n;j++)
            for (int k=j;k<n;k++) if (k-j<rk[i])
                dp[i][j]=(dp[i][j]+ mmul(dp[i-1][k],mmul(C[k][k-j],C[n-1-k][rk[i]-1-k+j])) )%mod;
    
    for (int i=1;i<=m;i++) dp[m][K]=mmul(dp[m][K],Lagrange_Itp(U[i],rk[i]));
    printf("%lld\n",(dp[m][K]%mod+mod)%mod);
    return 0;
}