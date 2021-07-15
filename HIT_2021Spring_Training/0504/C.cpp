#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
typedef long long ll;
using namespace std;


const ll mod = 1000000007LL;
ll fac[400010];

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
	for (;p;p>>=1,an=an*an%mod) if (p&1) ret=ret*an%mod;
	return ret;
}

ll C(ll n, ll m)
{
	return fac[n]*fastpow(fac[m], mod-2)%mod*fastpow(fac[n-m], mod-2)%mod;
}

void Solve()
{
	ll X_1, X_2, Y_1, Y_2;
	
	readx(X_1); readx(X_2); readx(Y_1); readx(Y_2);
	
	ll ans1 = C(X_1+Y_1, X_1) * C(X_2+Y_2, X_2) % mod;
	ll ans2 = C(X_1+Y_2, X_1) * C(X_2+Y_1, X_2) % mod;
	
	printf("%lld\n", (ans1-ans2+2*mod)%mod);
}

int main()
{
	fac[0]=fac[1]=1;
	for (int i=2;i<=400000;i++) fac[i]=fac[i-1]*i%mod;
	int T; readx(T);
	while (T--)
	{
		Solve();
	}
}