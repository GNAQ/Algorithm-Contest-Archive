// luogu-judger-enable-o2
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<queue>
#define ll long long
using namespace std;

const double PI=3.14159265358979323846;

struct Complex
{
    double r,i;
    Complex(double _r=0,double _i=0) { r=_r; i=_i; }
    Complex operator + (Complex b) { return Complex(r+b.r,i+b.i); }
    Complex operator - (Complex b) { return Complex(r-b.r,i-b.i); }
    Complex operator * (Complex b) { return Complex(r*b.r-i*b.i,r*b.i+i*b.r); }
};

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
    int rev[3000010],revt,flag;
    
    inline void BtFl(Complex y[],int len)
    {
        if (!flag)
        {
            flag=1; revt--;
            for (int i=0;i<len;i++) rev[i]=rev[i>>1]>>1|((i&1)<<revt);
        }
        for (int i=0;i<len;i++) if (i<rev[i]) swap(y[i],y[rev[i]]);
    }
    
    inline void FFT(Complex y[],int len,int dd)
    {
        BtFl(y,len);
        for (int i=1;i<len;i<<=1)
        {
            Complex wn( cos(PI/i), dd*sin(PI/i) );
            for (int j=0;j<len;j+=(i<<1))
            {
                Complex w(1,0);
                for (int k=0;k<i;k++,w=w*wn)
                {
                    Complex t1=y[j+k],t2=w*y[i+j+k];
                    y[j+k]=t1+t2;
                    y[i+j+k]=t1-t2;
                }
            }
        }
    }
};

Complex A[3000010],B[3000010];
int n,m,len;

int main()
{
    readx(n); readx(m); int cac=0; len=1;
    for (int i=0;i<=n;i++) 
    {
        readx(cac); A[i].r=(double)cac;
    }
    for (int i=0;i<=m;i++)
    {
        readx(cac); B[i].r=(double)cac;
    }
    while (len<n+m+1)
    {
        len<<=1; FFT::revt++;
    }
    
    FFT::FFT(A,len,1); FFT::FFT(B,len,1);
    for (int i=0;i<len;i++) A[i]=A[i]*B[i];
    FFT::FFT(A,len,-1);
    
    for (int i=0;i<=m+n;i++) printf("%d%c",(int)(A[i].r/len+0.5)," \n"[i==n+m]);
}
