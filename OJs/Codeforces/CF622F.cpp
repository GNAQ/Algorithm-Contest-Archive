#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
using namespace std;
typedef long long ll;

const ll mod=1000000007LL;

ll ml[1000010],mr[1000010],fac[1000010],k,n;

template<typename int_p>
void readx(int_p& x)
{
	x=0; char ch=0; int_p k=1;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

ll fastpow(ll an,ll p)
{
	ll ret=1;
	for (;p;p>>=1,an=an*an%mod) if (p&1) ret=ret*an%mod;
	return ret;
}

ll odd_or_even(ll num)
{
	if (num%2) return mod-1;
	else return 1;
}

void init()
{
	ml[0]=ml[k+3]=mr[0]=mr[k+3]=1;
	
	for (int i=1;i<=k+2;i++)
		ml[i]=ml[i-1]*(n-i)%mod;
	for (int i=k+2;i>=1;i--)
		mr[i]=mr[i+1]*(n-i)%mod;
	
	fac[0]=1;
	for (int i=1;i<=k+5;i++)
		fac[i]=fac[i-1]*i%mod;
}

int main()
{
	readx(n); readx(k);
	init();
	
	ll ans=0,yi=0;
	
	for (int i=1;i<=k+2;i++)
	{
		yi=(yi+fastpow(i,k))%mod;
		// yi * a / b
		ll a = (ml[i-1] * mr[i+1] % mod + mod ) % mod;
		ll b = fac[i-1] * fac[k+2-i] % mod * odd_or_even(k+2-i) % mod; 
		
		ans = ( ans + (yi * a % mod) * fastpow(b,mod-2) % mod ) % mod;
	}
	
	printf("%lld\n",ans);
	return 0;
}