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

ll n, m, a[110], p[110];


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
	for (;p;p>>=1, an=an*an%mod) if (p&1) ret=ret*an%mod;
	return ret;
}

ll gcd(ll a, ll b)
{
	if (!b) return a;
	return gcd(b, a%b);
}

ll exgcd(ll a, ll b, ll &x, ll &y)
{
	if (!b) { x=1; y=0; }
	else
	{
		exgcd(b, a%b, y, x);
		y-=x*(a/b);
	}
	
}

void Solve()
{
	readx(n); readx(m);
	for (int i=1;i<=m;i++) readx(p[i]);
	for (int i=1;i<=m;i++) readx(a[i]);
	
	ll A=a[1], P=p[1], x=0, y=0, G, tmp;
	for (int i=2;i<=m;i++)
	{
		exgcd(P, p[i], x, y); G=gcd(p[i], P);
		tmp = ((A-a[i])%p[i]+p[i])%p[i];
		
		if (tmp%G) 
		{
			printf("0\n");
			return;
		}
		
		x = x*(tmp/G)%p[i];
		A = A-x*P;
		
		P = P/G*p[i];
		A = (A%P+P)%P;
	}
	
	// 只需要解 x = A  (mod P)
	ll ans = 0;
	if (!A) 
	{
		ans = n/P;
	}
	else
	{
		ans = n/P + ( (n%P) >= A);
	}
	printf("%lld\n", ans);
	return;	
}

void Clear()
{
	memset(a,0,sizeof(a));
	memset(p,0,sizeof(p));
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		Solve();
		Clear();
	}
	
	return 0;
}