#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll mod=998244353;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
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

namespace NTT
{
	const ll G = 3;
	const ll iG = fastpow(3, mod - 2);
	
	ll rev[400010], revt, revf;
	void BtFl(ll *y, ll len)
	{
		if (revf != len)
		{
			revf = len; revt = -1; ll tmp = 1;
			while (tmp < len) { tmp<<=1; revt++; }
			for (int i=0;i<len;i++) rev[i]=(rev[i>>1]>>1) | ((i&1)<<revt);
		}
		for (int i=0;i<len;i++)
			if (rev[i]>i) swap(y[i], y[rev[i]]);
	}
	
	void NTT(ll *y, ll len, int mode)
	{
		BtFl(y, len);
		for (int i=1;i<len;i<<=1)
		{
			const ll wn = fastpow((mode==1)? G:iG, (mod-1) / (i<<1));
			for (int j=0;j<len;j+=i<<1)
			{
				ll w = 1;
				for (int k=0;k<i;k++, w=w*wn%mod)
				{
					ll t1 = y[j+k], t2 = y[i+j+k]*w%mod;
					y[j+k] = (t1+t2)%mod;
					y[i+j+k] = (t1-t2+mod)%mod;
				}
			}
		}
		if (mode == -1)
		{
			const ll inv = fastpow(len, mod-2);
			for (int i=0;i<len;i++) y[i]=y[i]*inv%mod;
		}
	}
}

ll A[400010], B[400010], TMP[400010];

void PolyInv(ll *A, ll *B, ll *TMP, ll nn)
{
	if (nn == 1)
	{ B[0] = fastpow(A[0], mod-2); return; }
	PolyInv(A, B, TMP, (nn+1)/2);
	
	ll len = 1;
	while (len<(nn*2)) len<<=1;
	for (int i=0;i<nn;i++) TMP[i]=A[i];
	for (int i=nn;i<len;i++) TMP[i]=0;
	
	NTT::NTT(TMP, len, 1); NTT::NTT(B, len, 1);
	for (int i=0;i<len;i++) 
		B[i] = ( (2 - TMP[i]*B[i] %mod+mod) % mod) * B[i] % mod;
	NTT::NTT(B, len, -1);
	
	for (int i=nn;i<len;i++) B[i]=0;
}

int Drivative(ll *y, ll n)
{
	for (int i=1;i<n;i++)
		y[i-1] = i*y[i]%mod;
}

int Intergrate(ll *y, ll n)
{
	for (int i=n-1;i>=0;i--)
		y[i+1]=y[i]*fastpow((i-1), mod-2);
}

void PolyExp()
{
	
}

int main()
{
	int n;
	readx(n);
	for (int i=0;i<n;i++) 
		readx(A[i]);
	
	PolyInv(A, B, TMP, n);
	
	for (int i=0;i<n;i++)
		printf("%lld%c", B[i], " \n"[i==n-1]);
	
	
	return 0;
}