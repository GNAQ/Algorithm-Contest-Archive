#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
typedef long long ll;
using namespace std;

const double PI=3.14159265358;
struct Complex
{
	double r,i;
	Complex(double inr=0, double ini=0) { r=inr; i=ini; }
	Complex operator + (const Complex& B) { return Complex(r+B.r, i+B.i); }
	Complex operator - (const Complex& B) { return Complex(r-B.r, i-B.i); }
	Complex operator * (const Complex& B) { return Complex(r*B.r-i*B.i, i*B.r+r*B.i); }
};

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

namespace FFT
{
	int pre_len=0,revt,rev[300010];
	template<typename poly_arr>
	void BtFl(poly_arr *y, int len)
	{
		if (len!=pre_len)
		{
			pre_len=len; revt=0; int tmp=2;
			while (tmp<len) { tmp<<=1; revt++; }
			for (int i=0;i<len;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<revt);
		}
		for (int i=0;i<len;i++) if (i<rev[i]) swap(y[i],y[rev[i]]);
	}
	
	void FFT(Complex *y, int len, int mode)
	{
		BtFl(y,len);
		
		for (int i=1;i<len;i<<=1)
		{
			const Complex wn( cos(PI/i), mode*sin(PI/i) );
			for (int j=0;j<len;j+=(i<<1)) // Each Process Start Point
			{
				Complex w(1,0);
				for (int k=0;k<i;k++,w=w*wn) // Step size
				{
					Complex t1=y[j+k], t2=w*y[i+j+k];
					y[j+k]=t1+t2;
					y[i+j+k]=t1-t2;
				}
			}
		}
		if (mode==-1) for (int i=0;i<len;i++) y[i].r/=len;
	}
}

Complex F[300010],G[300010];
int n,m;

int main()
{
	readx(n); readx(m); int tmp;
	for (int i=0;i<=n;i++) 
		{ readx(tmp); F[i].r=1.0*tmp; }
	for (int i=0;i<=m;i++) 
		{ readx(tmp); G[i].r=1.0*tmp; }
	
	int len=1;
	while (len<=(n+m)) len<<=1;
	FFT::FFT(F,len,1); FFT::FFT(G,len,1);
	for (int i=0;i<len;i++) F[i]=F[i]*G[i];
	FFT::FFT(F,len,-1);
	
	for (int i=0;i<=n+m;i++) printf("%d%c", (ll)(F[i].r+0.03), " \n"[i==n+m]);
}