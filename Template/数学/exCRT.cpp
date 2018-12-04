#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#define ll long long
using namespace std;

ll a[100010],p[100010],n;

template<typename int_t>
void readx(int_t& x)
{
    x=0; int k=1; char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

ll mul(ll an,ll p,ll mod)
{
    ll ret=0;
    for (;p;p>>=1,an=(an+an)%mod) if (p&1) ret=(ret+an)%mod;
    return ret;
}

void exgcd(ll a,ll b,ll& xx,ll& yy)
{
    if (!b) { xx=1; yy=0; }
    else
    {
        exgcd(b,a%b,yy,xx);
        yy-=xx*(a/b);
    }
}

ll gcd(ll a1,ll a2)
{
    if (!a2) return a1;
    return gcd(a2,a1%a2);
}

int main()
{
    readx(n); 
    for (int i=1;i<=n;i++) { readx(p[i]); readx(a[i]); }
    
    ll A=a[1],P=p[1],x=0,y=0,G,tmp;
    
    for (int i=2;i<=n;i++)
    {
        exgcd(P,p[i],x,y); G=gcd(P,p[i]); 
        tmp=((A-a[i])%p[i]+p[i])%p[i];
        x=mul( x , tmp/G  , p[i]);
        
        A=A-x*P;
        P=P/G*p[i];
        
        A=(A%P+P)%P;
    }
    
    printf("%lld\n",A);
    return 0;
}
