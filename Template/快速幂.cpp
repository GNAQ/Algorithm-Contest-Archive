#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#define ll long long
using namespace std;

ll a,b,c,d;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

ll fastpow(ll an,ll pn,ll MOD)
{
	ll ret=1; an%=MOD;
	for (;pn;pn>>=1,an=(an*an)%MOD) if (pn&1) ret=(ret*an)%MOD;
	return ret%MOD;
}


int main()
{
	readx(a); readx(b); readx(c);
	d=fastpow(a,b,c);
	printf("%lld^%lld mod %lld=%lld\n",a,b,c,d);
}
