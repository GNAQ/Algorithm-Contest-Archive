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

void readmod(ll &x)
{
	x=0; ll k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=(x*10+ch-'0')%mod; ch=getchar(); }
	x = (x*k%mod+mod)%mod; 
}

ll fastpow(ll an,ll p)
{
	ll ret=1;
	for (;p;p>>=1,an=an*an%mod) if (p&1) ret=ret*an%mod;
	return ret;
}

ll quad_res_ntt(ll y, ll k) // Calc y^{1/k} mod 998244353
{
	ll q = 0, x = 0;
	// BSGS find q
	int stp = ceil(sqrt(mod));
	map<ll, int> mp;
	ll v = 0;
	
	for (int i=0; 1LL*i*stp<=mod; i++)
	{
		v = y * fastpow(fastpow(3, i*stp), mod-2) % mod;
		mp[v] = i * stp;
	}
	
	v = 1;
	for (int i=0;i<stp;i++)
	{
		if (mp.find(v) != mp.end())
			q = mp[v] + i;
		v = v * 3 % mod;
	}
	
	// calc ans
	q/=k;
	x = fastpow(3, q);
	return min(x, mod - x);
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

// N doesn't need to be 2^w
void Drivative(ll *y, ll *targ, ll nn)
{
	for (int i=1;i<nn;i++)
		targ[i-1] = i*y[i]%mod;
	targ[nn-1] = 0;
}

// N doesn't need to be 2^w
void Intergrate(ll *y, ll *targ, ll nn)
{
	for (int i=nn-1;i>=0;i--)
		targ[i+1] = y[i]*fastpow((i+1), mod-2)%mod;
	targ[0] = 0;
}

// N doesn't need to be 2^w
ll Tinv[400010];
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

// N need to be 2^w
// need [2] extra vector to store mid-states
ll iA[400010], dA[400010];
void PolyLn(ll *y, ll *targ, ll nn)
{
	for (int i=0;i<(nn<<1);i++)
		iA[i]=dA[i]=0;
	Drivative(y, dA, nn);
	PolyInv(y, iA, Tinv, nn);
	// NOTICE: dA of 2^nn * iA of 2^nn -> 2^(nn+1)
	NTT::NTT(dA, nn<<1, 1);
	NTT::NTT(iA, nn<<1, 1);
	for (int i=0;i<(nn<<1);i++) dA[i]=dA[i]*iA[i]%mod;
	NTT::NTT(dA, nn<<1, -1);
	Intergrate(dA, targ, nn);
}

// N need to be 2^w
// base = 1       : f(0) = 0
// base = g(0)    : solve PolyRt/PolyPow
ll lnA[400010];
void PolyExp(ll *y, ll *targ, ll nn, ll base)
{
	if (nn == 1)
	{
		targ[0] = base;
		return;
	}
	PolyExp(y, targ, nn/2, base);
	
	PolyLn(targ, lnA, nn);
	lnA[0] = ((y[0]+1-lnA[0])%mod+mod)%mod;
	for (int i=1;i<nn;i++) lnA[i]=((y[i]-lnA[i])%mod+mod)%mod;
	
	NTT::NTT(lnA, (nn<<1), 1); NTT::NTT(targ, (nn<<1), 1);
	for (int i=0;i<(nn<<1);i++) targ[i]=targ[i]*lnA[i]%mod;
	NTT::NTT(targ, (nn<<1), -1);
	
	for (int i=nn;i<(nn<<1);i++) 
		targ[i]=lnA[i]=0;
}

// Calc power_root(f, k)
// CAN'T specify whether sol exists
// N doesn't need to be 2^w
ll lnB[400010];
void PolyRt(ll *y, ll *targ, ll k, ll nn)
{
	int len = 1;
	while (len<nn) len<<=1;
	ll iK = fastpow(k, mod-2);
	
	PolyLn(y, lnB, len);
	for (int i=0;i<len;i++)
		lnB[i] = iK * lnB[i] % mod;
	
	if (y[0]!=1)
		PolyExp(lnB, targ, len, quad_res_ntt(y[0], k));
	else
		PolyExp(lnB, targ, len, 1);
	for (int i=nn;i<len;i++) targ[i] = 0;
}

// Calc f^k 
// N doesn't need to be 2^w
void PolyPow(ll *y, ll *targ, ll k, ll nn)
{
	// can only solve f(0)=1
	int len = 1;
	while (len<nn) len<<=1;
	
	PolyLn(y, lnB, len);
	for (int i=0;i<len;i++)
		lnB[i] = k * lnB[i] % mod;
	PolyExp(lnB, targ, len, 1);
	for (int i=nn;i<len;i++) targ[i]=0;
}

// solve f(x) via array x, y and return f(v)
// f(x) = sum(i){ y_i * prod(j!=i){ (v - x[j]) / (x[i] - x[j]) } }
ll Lagrange_Itp(ll *x, ll *y, ll len, ll v)
{
	ll ret = 0;
	for (int i=1;i<=len;i++)
	{
		ll s1 = 1, s2 = 1;
		for (int j=1;j<=len;j++) if (j!=i)
		{
			s1 = s1 * ((v - x[j]) % mod + mod) % mod;
			s2 = s2 * ((x[i] - x[j]) % mod + mod) % mod;
		}
		ret = (ret + (y[i] * s1 % mod * fastpow(s2, mod-2) % mod)) % mod;
	}
	return ret;
}


int main()
{
	
}