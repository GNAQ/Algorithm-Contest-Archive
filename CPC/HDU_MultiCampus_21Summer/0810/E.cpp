#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll mod = 1e9+7;

ll fac[2000010];

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
	if (_m>_n || _m<0) return 0;
	return fac[_n]*fastpow(fac[_m],mod-2)%mod*fastpow(fac[_n-_m],mod-2)%mod;
}

ll Lucas(ll _n,ll _m)
{
	if (_m>_n || _m<0) return 0;
	if (!_m) return 1;
	return C(_n%mod,_m%mod)*Lucas(_n/mod,_m/mod)%mod;
}

void Solve()
{
	ll n, m; readx(n); readx(m);
	
	ll ans = 0;
	ans = (( Lucas(n+m, m) - Lucas(m-1, m-(n+1)) )%mod + 2*mod) % mod;
	cout << ans << endl;
}

void Clear()
{
	
}

int main()
{
	Init_C(2000007);
	int T; readx(T);
	while (T--)
	{
		Solve();
		Clear();
	}
	
}