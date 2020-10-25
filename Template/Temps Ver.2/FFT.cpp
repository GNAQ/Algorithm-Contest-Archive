#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<queue>
#include<vector>
#include<map>
#include<set>
using namespace std;
typedef long long ll;
typedef ostream_iterator<int> os_iter_int;

const double PI=3.14159265358979323846;
struct Complex
{
	double r,i;
	Complex(double inr=0,double ini=0) { r=inr; i=ini; }
	Complex operator + (const Complex& B) { return Complex(r+B.r,i+B.i); }
	Complex operator - (const Complex& B) { return Complex(r-B.r,i-B.i); }
	Complex operator * (const Complex& B) { return Complex(r*B.r-i*B.i,r*B.i+i*B.r); }
};

int n,m; 
Complex F[3000010],G[3000010];

template<typename inp_t>
void readx(inp_t& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

namespace FFT
{
	int revf,revt,rev[3000010];
	
	template<typename poly_arr>
	void BtFl(poly_arr* y,int len)
	{
		if (len!=revf)
		{
			revf=len; revt=-1; ll tmp=1;
			while (tmp<len) { tmp<<=1; revt++; }
			for (int i=0;i<len;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<revt);
		}
		for (int i=0;i<len;i++) if (i<rev[i]) swap(y[i],y[rev[i]]);
	}
	
	void FFT(Complex* y,int len,int mode)
	{
		BtFl(y,len);
		for (int i=1;i<len;i<<=1)
		{
			const Complex wn( cos(PI/i), mode*sin(PI/i) );
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
		if (mode==-1) for (int i=0;i<len;i++) y[i].r/=len;
	}
};

int main()
{
	readx(n); readx(m); int tmp;
	for (int i=0;i<=n;i++) 
		{ readx(tmp); F[i].r=1.0*tmp; }
	for (int i=0;i<=m;i++)
		{ readx(tmp); G[i].r=1.0*tmp; }
	
	ll len=1;
	while (len<=(n+m)) len<<=1;
	FFT::FFT(F,len,1); FFT::FFT(G,len,1);
	for (int i=0;i<len;i++) F[i]=F[i]*G[i];
	FFT::FFT(F,len,-1);
	
	for (int i=0;i<=n+m;i++) printf("%lld%c",(ll)(F[i].r+0.03)," \n"[i==n+m]);
}