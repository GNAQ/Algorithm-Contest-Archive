#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<map>
#include<set>
#include<queue>
#include<vector>
#define ll long long
using namespace std;

template<typename int_t>
void readx(int_t& x)
{
    x=0; int_t k=1; char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

namespace FFT
{
    const double PI=3.14159265358979323846;
    struct Complex
    {
        double r,i;
        Complex(double ir=0,double ii=0) { r=ir; i=ii; }
        Complex operator + (Complex B) { return Complex(r+B.r,i+B.i); }
        Complex operator - (Complex B) { return Complex(r-B.r,i-B.i); }
        Complex operator * (Complex B) { return Complex(r*B.r-i*B.i,r*B.i+i*B.r); }
    };

    ll revf,revt,rev[1000010];

    template<typename poly_arr>
    void BtFl(poly_arr y[],ll len)
    {
        if (revf!=len)
        {
            revf=len; revt=-1; ll tmp=1;
            while (tmp<len) { tmp<<=1; revt++; }
            for (int i=0;i<len;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<revt);
        }
        for (int i=0;i<len;i++) if (i<rev[i]) swap(y[i],y[rev[i]]);
    }

    void FFT(Complex y[],ll len,ll dd)
    {
        BtFl(y,len);
        for (int i=1;i<len;i<<=1)
        {
            Complex wn( cos(PI/i) , dd*sin(PI/i) );
            for (int j=0;j<len;j+=(i<<1))
            {
                Complex w(1,0);
                for (int k=0;k<i;k++,w=w*wn)
                {
                    Complex t1=y[j+k],t2=w*y[i+j+k];
                    y[j+k]=(t1+t2);
                    y[i+j+k]=(t1-t2);
                }
            }
        }
        if (dd==-1) for (int i=0;i<len;i++) y[i].r/=len;
    }
}

FFT::Complex xi[1000010],yi[1000010];
ll n,ans=2*1e16,m,Ai[1000010],Bi[1000010];

int main()
{
    readx(n); readx(m);
    for (int i=1;i<=n;i++) readx(Ai[i]);
    for (int i=1;i<=n;i++) readx(Bi[i]);

    for (int i=1;i<=n;i++) xi[i].r=xi[n+i].r=Ai[i];
    for (int i=1;i<=n;i++) yi[i].r=Bi[n-i+1];

    ll len=1;
    while (len<(n*3)) len<<=1;
    FFT::FFT(xi,len,1); FFT::FFT(yi,len,1);
    for (int i=0;i<len;i++) xi[i]=xi[i]*yi[i];
    FFT::FFT(xi,len,-1);

    ll sum=0,sum2=0;
    for (int i=1;i<=n;i++) sum+=Ai[i]-Bi[i];
    for (int i=1;i<=n;i++) sum2+=Ai[i]*Ai[i]+Bi[i]*Bi[i];

    for (int i=1;i<=n;i++)
        for (int j=-m;j<=m;j++) ans=min(ans,sum2 + 2LL*sum*j + j*j*n -2LL*(ll)(xi[i+n].r+0.5));
    
    printf("%lld\n",ans);
}
