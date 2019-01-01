#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<queue>
#include<iterator>
#include<map>
#include<set>
#define ll long long
using namespace std;

ll n,m,mod;
ll fac[1000010];

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

ll fastpow(ll an,ll p)
{
	ll ret=1; an%=mod;
	for (;p;p>>=1,an=an*an%mod) if (p&1) ret=ret*an%mod;
	return ret;
}

void Init_C(ll lim)
{
	fac[0]=1;
	for (int i=1;i<=lim;i++) fac[i]=(fac[i-1]*i)%mod;
}

ll C(ll _n,ll _m)
{
	if (_m>_n) return 0;
	return fac[_n]*fastpow(fac[_m],mod-2)%mod*fastpow(fac[_n-_m],mod-2)%mod;
}

ll Lucas(ll _n,ll _m)
{
	if (!_m) return 1;
	return C(_n%mod,_m%mod)*Lucas(_n/mod,_m/mod)%mod;
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		ll n,m; readx(n); readx(m); readx(mod);
		Init_C(mod);
		printf("%lld\n",Lucas(m+n,m));
	}
}
