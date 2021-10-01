#include<bits/stdc++.h>
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

ll fastpow(ll an, ll p)
{
	ll ret=1;
	for (;p;p>>=1,an=an*an%mod) if (p&1) ret=ret*an%mod;
	return ret;
}

namespace NTT
{
	const ll G=3, iG=fastpow(3,mod-2);
	int rev[4600010],revt,pre_len=-1;
	
	template<typename poly_arr>
	void BtFl(poly_arr *y, int len)
	{
		if (len!=pre_len)
		{
			pre_len=len; revt=0; int tmp=2;
			while (tmp<len) { tmp<<=1; revt++; }
			for (int i=0;i<len;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<revt);
		}
		for (int i=0;i<len;i++) if (i<rev[i]) swap(y[i], y[rev[i]]);
	}
	
	void NTT(ll *y, ll len,int mode)
	{
		BtFl(y, len);
		for (int i=1;i<len;i<<=1)
		{
			const ll wn=fastpow((mode==1)? G : iG, (mod-1)/(i<<1));
			for (int j=0;j<len;j+=(i<<1))
			{
				ll w=1;
				for (int k=0;k<i;k++,w=w*wn%mod)
				{
					ll t1=y[j+k], t2=w*y[i+j+k]%mod;
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
}

const int MAX_LIM = 1000000;
ll F[4600010], G[4600010];
ll ai[1000010], n;
ll fac[1000010];

int main()
{
	readx(n); fac[0]=1; ll ans = 1;
	for (int i=1;i<=n;i++)
	{
		fac[i]=fac[i-1]*i%mod;
		readx(ai[i]);
		F[ai[i]]++;
		G[MAX_LIM - ai[i]]++;
		ans = (ans * (ai[i]+1)) % mod;
	}
	
	ll tmp = fastpow(fac[n], mod - 2);
	for (int i=n;i>=1;i--)
	{
		ans = (ans * tmp) % mod;
		tmp = (tmp * i) % mod;
	}
	
	ll lim = 1;
	while (lim <= 2*MAX_LIM) lim<<=1LL;
	NTT::NTT(F, lim, 1); NTT::NTT(G, lim, 1);
	for (int i=0;i<lim;i++) F[i]=(F[i]*G[i])%mod;
	NTT::NTT(F, lim, -1);
	
	for (int i=MAX_LIM+1; i<=MAX_LIM*2; i++)
		ans = (ans * fastpow(i-MAX_LIM, F[i])) % mod;
	
	printf("%lld\n", ans);
}