#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
typedef long long ll;
using namespace std;


template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

ll fastpow(ll an, ll p, ll mod)
{
	ll ret = 1;
	for (;p;p>>=1,an=an*an%mod) if (p&1) ret=ret*an%mod;
	return ret;
}

ll x0, x, a, b, m;

int main()
{
	readx(a); readx(b); readx(m); readx(x0); readx(x);
	ll lam = 1 + (a-1) * (x-x0) % m * fastpow((a-1)*x0+b, m-2, m) % m;
	lam = (lam % m + 2 * m) % m;
	
	if (lam == 1) 
	{
		puts("Yes");
		return 0;
	} 
	
	ll ok = a;
	do
	{
		if (ok==lam)
		{
			puts("Yes");
			return 0;
		}
		ok = ok * a % m;
	} while (ok!=a);
	
	puts("No");
	return 0;
}