#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<iterator>
#include<vector>
#include<queue>
#include<map>
#include<set>
#define ll long long 
using namespace std;

struct Complex
{
    double r,i;
    Complex(double _r=0,double _i=0) { r=_r; i=_i; }
    Complex operator + (Complex a) { return Complex(r+a.r,i+a.i); }
    Complex operator - (Complex a) { return Complex(r-a.r,i-a.i); }
    Complex operator * (Complex a) { return Complex(r*a.r-i*a.i,r*a.i+i*a.r); }
};
const double PI=3.14159265358979323846;

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
    int revt,revf,rev[3000010];
    
    void BtFl(Complex y[],int len)
    {
        if (!revf)
        {
            revf=1;
            for (int i=0;i<len;i++) rev[i]=(rev[i>>1]>>1|((i&1)<<revt));
        }
        for (int i=0;i<len;i++) if (i<rev[i]) swap(y[i],y[rev[i]]);
    }

    void FFT(Complex y[],int len,int dd)
    {
        BtFl(y,len);
        for (int i=1;i<len;i<<=1)
        {
            Complex wn( cos(PI/i) , dd*sin(PI/i) );
            for (int j=0;j<len;j+=(1<<i))
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


int main()
{
    
    
    
}
