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

const ll mod = 1e9+7;


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

int main()
{
	int T; readx(T);
	
	while (T--)
	{
		ll n, k;
		readx(n); 
		n %= mod;
		
		ll ans = 0, tans = 0;
		ans = 1;
		ans *= n  * (n+1) % mod * fastpow(2, mod-2) % mod;
		ans %= mod;
		ans *= n * (n+1) % mod * (2 * n + 1) % mod * fastpow(6, mod-2) % mod;
		ans %= mod;
		tans+=ans; ans = 0;
		
		ans = (n-1) * (n-1) % mod * (n+2) % mod * (n+2) % mod;
		ans = (ans * fastpow(4, mod-2)) % mod;
		tans+=ans; ans=0;
		
		ans = n * (n-1) % mod * (n+1) % mod * (n+2) % mod * (2*n+1) % mod;
		ans = (ans * fastpow(12, mod-2)) % mod;
		tans +=ans; ans=0;
		
		ans = (n-1) * (n+2) % mod * fastpow(2, mod-2) % mod;
		tans -=ans;
		
		cout << (tans%mod+mod) % mod << endl;
		
		ll ans2 = n * n % mod;
		ans2 *= n  * (n+1) % mod * fastpow(2, mod-2) % mod;
		ans2 %= mod;
		ans2 *= n * (n+1) % mod * (2 * n + 1) % mod * fastpow(6, mod-2) % mod;
		ans2 %= mod;
		cout << ans2 << endl;
	}
	
	
}