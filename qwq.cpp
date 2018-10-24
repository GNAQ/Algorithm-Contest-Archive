#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<vector>
#define ll long long
using namespace std;

const long long mod=1000000007;
ll ans=0;
ll n,m,k,fac[1000010],ifac[1000010];

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
	ll ret=1;
	for (;p;p>>=1,an=(an*an)%mod) if (p&1) ret=(ret*an)%mod;
	return ret;
}

void Init_C()
{
	fac[0]=1; ifac[0]=1;
	for (int i=1;i<=1000000;i++) fac[i]=(fac[i-1]*i)%mod;
	ifac[1000000]=fastpow(fac[1000000],mod-2);
	for (int i=999999;i;i--) ifac[i]=(ifac[i+1]*(i+1))%mod;
}

ll C(ll _n,ll _m)
{
	return ((fac[_n]*ifac[_n-_m])%mod*ifac[_m])%mod;
}

int main()
{
	Init_C();
	readx(n); readx(m); readx(k);
	for (int i=0;i<=m;i++)
	{
		ll rest=m-i,tmp=fastpow(2,rest)-1;
		tmp=fastpow(tmp,n); tmp*=C(m,i);
		
		if (i%2) ans=(ans-tmp+mod)%mod;
		else ans=(ans+tmp)%mod;
	}
	ans=fastpow(ans,k);
	cout<<ans<<endl;
}
