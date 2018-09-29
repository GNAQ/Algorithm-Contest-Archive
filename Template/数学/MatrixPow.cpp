#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<algorithm>
#include<iterator>
#define mo 1000000007
#define ll long long
using namespace std;

struct mat { ll e[110][110]; };
ll n,kx;


inline void readx(ll& x)
{
	x=0; ll k=1; register char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

inline mat mul(mat a,mat b)
{
	mat c={0};
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			for (int k=1;k<=n;k++)
				c.e[i][j]=(c.e[i][j]+(a.e[i][k]*b.e[k][j])%mo)%mo;
	return c;
}
inline mat fastpow(mat a,ll p)
{
	mat ret=a;
	for (;p;p>>=1,a=mul(a,a)) if (p&1) ret=mul(ret,a);
	return ret;
}

int main()
{
	readx(n); readx(kx); mat baze={0};
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			readx(baze.e[i][j]);
	baze=fastpow(baze,kx-1);
	
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++) printf("%lld ",baze.e[i][j]);
		printf("\n");
	}
	return 0;
}
