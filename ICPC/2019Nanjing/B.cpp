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

const ll mod = 1000000007LL;
int ifac[2000010],fac[2000010];

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

ll C(ll n, ll m)
{
	return 1LL*fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}

int main()
{
	ifac[1]=1; fac[0]=1;
	for (int i=1;i<=2000000;i++) 
		fac[i]=1LL*fac[i-1]*i%mod;
	ifac[2000000] = fastpow(fac[2000000], mod-2);
	for (int i=1999999;i>1;i--) ifac[i] = 1LL*ifac[i+1]*(i+1)%mod;
	
	int T; readx(T);
	while (T--)
	{
		int n,m;
		readx(n); readx(m);
		if (n==1 && m==1)
		{
			printf("1\n");
		}
		else if (n==1 || m==1)
		{
			printf("2\n");
		}
		else
		{
			printf("%lld\n", 4LL*C(n+m-2, n-1)%mod);
		}
	}
	return 0;
}