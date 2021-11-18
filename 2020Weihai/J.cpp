#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll n, ai[100010];

ll lb[100]; // 2^60 > 1e18
ll freed, avail;

const ll mod = 1e9+7;
ll totans;

ll fac[100010], ifac[100010];

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
	ll ret = 1;
	for (;p;p>>=1, an=an*an%mod) if (p&1) ret=ret*an%mod;
	return ret;
}

void InsLB(ll x)
{
	int ok = 0;
	for (int i=60;i>=0;i--) if (x&(1LL<<i))
	{
		if (lb[i]==-1)
		{
			lb[i] = x;
			ok = 1;
			break;
		}
		x = x ^ lb[i];
	}
	if (!ok) freed++;
	else avail++;
}

ll Solve(ll v)
{
	for (int i = 60; i>=0; i--)
	{
		if (v & (1LL<<i))
		{
			if (lb[i]==-1)
				return 0;
			v = v ^ lb[i];
		}
	}
	if (v) return 0;
	return fastpow(2, freed);
}

ll C(ll cn, ll cm)
{
	return 1LL * fac[cn] * ifac[cm] % mod * ifac[cn-cm] % mod;
}

int main()
{
	map<ll, int> mpx;
	memset(lb, -1, sizeof(lb));
	fac[0] = 1;
	for (int i=1;i<=100000;i++)
		fac[i] = 1LL * fac[i-1] * i % mod;
	ifac[100000] = fastpow(fac[100000], mod - 2);
	for (int i=100000;i>=1;i--)
		ifac[i-1] = 1LL * ifac[i] * i % mod;
	
	readx(n);
	ll totxor = 0;
	for (int i=1;i<=n;i++)
	{
		readx(ai[i]);
		totxor ^= ai[i];
		mpx[ai[i]]++;
	}
	
	ll prexor = totxor;
	ll sufxor = 0;
	auto iter = mpx.rbegin();
	for (; iter != mpx.rend(); iter++)
	{
		if (iter->second % 2) prexor ^= iter->first;
		
		// case 1: all black piles have same value of ai[i];
		for (int i = 1; i <= iter->second; i++)
		{
			ll SGb = iter->first - (i + 1) % 2;
			ll SGw1 = prexor;
			if ((iter->second - i)%2 == 1) SGw1 ^= iter->first;
			
			ll SGw2 = SGb ^ SGw1;
			
			if (sufxor == SGw2) 
				totans = (totans + C(iter->second, i) % mod) % mod;
		}
		
		// case 2: have other black values > iter[first]
		for (int i = 1; i <= iter->second; i++)
		{
			ll SGb = iter->first - i % 2;
			ll SGw1 = prexor;
			if ((iter->second - i)%2 == 1) SGw1 ^= iter->first;
			
			ll SGw2 = SGb ^ SGw1;
			
			ll tmp = Solve(SGw2);
			
			if (sufxor == SGw2) tmp = (tmp-1+mod)%mod;
			totans = (totans + tmp * C(iter->second, i) % mod) % mod;
		}
		
		for (int i = 1; i <= iter->second; i++)
			InsLB(iter->first);
		if (iter->second % 2)
			sufxor ^= iter->first;
	}
	
	if (!totxor) totans = (totans + 1) % mod;
	cout << totans << endl;
}