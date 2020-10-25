#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<iterator>
#include<queue>
#include<vector>
#include<map>
#include<set>
using namespace std;
typedef long long ll;
typedef ostream_iterator<int> os_iter_int;

const ll mod=998244353;

template<typename inp_t>
void readx(inp_t& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

ll fastpow(ll an,ll p)
{
	ll ret=1;
	for (;p;p>>=1,an=an*an%mod) if (p&1) ret=ret*an%mod;
	return ret;
}

namespace FFT
{
	const ll G=3;
	const ll iG=fastpow(3,mod-2);
	
	int rev[2000010],revf,revt;
	void BtFl(ll* y,int len)
	{
		if (len!=revf)
		{
			revt=-1; revf=len; ll tmp=1;
			while (tmp<len) { tmp<<=1; revt++; }
			for (int i=0;i<len;i++) rev[i]=(rev[i>>1]>>1)|(i&1)<<revt;
		}
		for (int i=0;i<len;i++) if (i<rev[i]) swap(y[i],y[rev[i]]);
	}
	void NTT(ll* y,int len,int mode)
	{
		BtFl(y,len);
		for (int i=1;i<len;i<<=1)
		{
			const ll wn=fastpow((mode==1?G:iG),(mod-1)/(i<<1));
			for (int j=0;j<len;j+=(i<<1))
			{
				ll w=1;
				for (int k=0;k<i;k++,w=w*wn%mod)
				{
					ll t1=y[j+k],t2=y[i+j+k]*w%mod;
					y[j+k]=(t1+t2)%mod;
					y[i+j+k]=(t1-t2+mod)%mod;
				}
			}
		}
		if (mode==-1)
		{
			const ll inv=fastpow(len,mod-2);
			for (int i=0;i<len;i++) y[i]=y[i]*inv%mod;
		}
	}
};

void PolyInv(ll* A,ll* B,ll* C,ll _n)
{
	if (_n==1) { B[0]=fastpow(A[0],mod-2); return; }
	PolyInv(A,B,C,(_n+1)>>1);
	
	ll len=1; while (len<(_n<<1)) len<<=1;
	for (int i=0;i<len;i++) C[i]=A[i];
	for (int i=_n;i<len;i++) C[i]=0;
	
	FFT::NTT(C,len,1); FFT::NTT(B,len,1);
	for (int i=0;i<len;i++) B[i]=(2-C[i]*B[i]%mod+mod)%mod*B[i]%mod;
	FFT::NTT(B,len,-1);
	
	for (int i=_n;i<len;i++) B[i]=0;
}

ll pa[2000010],pb[2000010],pc[2000010],n;

int main()
{
	readx(n);
	for (int i=0;i<n;i++) readx(pa[i]);
	PolyInv(pa,pb,pc,n);
	for (int i=0;i<n;i++) printf("%lld%c",pb[i]," \n"[i==n-1]);
}	
