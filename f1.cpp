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
	
	ll rev[4000010], revt, revf;
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


int main()
{
	
	
}