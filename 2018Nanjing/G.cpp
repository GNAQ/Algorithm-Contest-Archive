#include <bits/stdc++.h>
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
	for (;p;p>>=1,an=an*an%mod) if (p&1) ret = ret * an % mod;
	return ret;
}

void Solve()
{
	ll n;
	ll inv24 = fastpow(24, mod-2);
	readx(n);
	printf("%lld\n", (n+3)*(n+2)%mod*(n+1)%mod*n%mod*inv24%mod);
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		Solve();
	}
	
	
}