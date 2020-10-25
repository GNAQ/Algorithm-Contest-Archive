#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<map>
typedef long long ll;
using namespace std;

ll ans1,ans2;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

ll fac(ll x)
{
	ll ret=1;
	for (ll i=1;i<=x;i++) ret*=i;
	return ret;
}

int main()
{
	ll n; readx(n); ll n2=n>>1;
	
	if (n==2) printf("1\n");
	else
		printf("%lld\n", fac(n/2-1) * (fac(n) / (n2*fac(n2)) ) / 2 );
	return 0;
}