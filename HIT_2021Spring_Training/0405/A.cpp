#pragma G++ optimize("O3")
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<vector>
typedef long long ll;
using namespace std;

const int mod = 1e9+9;
int a, b, n, k;
int s[100010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int fastpow(int an, int p)
{
	int ret = 1;
	for (;p;p>>=1, an=1LL*an*an%mod) if (p&1) ret=1LL*ret*an%mod;
	return ret;
}

int main()
{
	readx(n); readx(a); readx(b); readx(k);
	char ch = '\n';
	while (ch=='\n' || ch==' ') ch=getchar();
	for (int i=1;i<=k;i++)
	{
		s[i-1] = (ch=='+')? 1 : -1;
		ch=getchar();
	}
	
	int ans1 = 0, ans2 = 0, pwa, pwb;
	for (int i=0;i<k;i++)
	{
		ans1 = (ans1 + 1LL * fastpow(a, n-i) * fastpow(b, i) % mod * 1LL * s[i] % mod) % mod;
		ans1 = (ans1 + mod) % mod;
	}
	
	pwa = fastpow(fastpow(a, k), mod-2);
	pwb = fastpow(b, k);
	int mu = 1LL*pwa*pwb%mod, rnd = (n+1)/k;
	
	if (mu == 1)
	{
		ans2 = 1LL*ans1*rnd%mod;
	}
	else
	{
		ans2 = 1LL * ans1 * ((1LL * fastpow(mu, rnd) - 1 + mod) % mod) % mod 
				* 1LL * fastpow(mu-1, mod-2) % mod;
	}
	
	ans2 = (ans2%mod+mod)%mod;
	printf("%d\n", ans2);
	return 0;
}